/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/DateTime.h"
#include "Poco/Dynamic/Var.h"
#include "MeteorDetector.h"
#include "ShutdownHelper.h"
#include "Property.h"
#include "normalizer/NormalizerFactory.h"
#include "detector/DetectorFactory.h"
#include "exporter/Exporter.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
MeteorDetector::MeteorDetector(
  const std::string& video_path,
  const std::string& normalizer_name,
  const std::string& detector_name)
  : video_path_(video_path),
    normalizer_name_(normalizer_name),
    detector_name_(detector_name) {
}

////////////////////////////////////////////////////////////////////////////////
MeteorDetector::~MeteorDetector() {
}

////////////////////////////////////////////////////////////////////////////////
bool MeteorDetector::Run() {
  Poco::DateTime st;

  if (!Initialize()) {
    UnInitialize();
    return false;
  }

  // 解析の完了を待つ.
  queue_.waitDequeueNotification();

  UnInitialize();

  if (ShutdownHelper::GetInstance().IsShutdown()) {
    return false;
  }

  Poco::DateTime et;
  std::string sts = Poco::format("%04d/%02d/%02dT%02d:%02d:%02d", st.year(), st.month(), st.day(), st.hour(), st.minute(), st.second());
  std::string ets = Poco::format("%04d/%02d/%02dT%02d:%02d:%02d", et.year(), et.month(), et.day(), et.hour(), et.minute(), et.second());
  std::cout << Poco::format("Start: %s", sts) << std::endl;
  std::cout << Poco::format("End  : %s", ets) << std::endl;
  std::cout << Poco::format("Diff : %Ld", Poco::Dynamic::Var(et - st).convert<Poco::Int64>()) << std::endl;
  return true;
}

////////////////////////////////////////////////////////////////////////////////
bool MeteorDetector::Initialize() {
  try {
    normalizer_ = NormalizerFactory::GetInstance().Create(normalizer_name_);
    if (normalizer_.isNull()) {
      std::cout << Poco::format("Normalizer not found. (normalizer=%s)", normalizer_name_) << std::endl;
      return false;
    }
    detector_ = DetectorFactory::GetInstance().Create(detector_name_);
    if (detector_.isNull()) {
      std::cout << Poco::format("Detector not found. (detector=%s)", detector_name_) << std::endl;
      return false;
    }

    video_loader_ = new VideoLoader(video_path_, normalizer_);

    exporter_ = new Exporter(Property::GetInstance().GetDefaultExporter(video_loader_->GetName()));

    // 生成するスレッド数を取得する.
    int count = detector_->RequiredMaxThread();
    if (count == 0) {
      count = Property::GetInstance().GetMaxDetectorThread();
    }

    thread_pool_ = new AsyncThreadPool(video_loader_, detector_, exporter_);

    timer_ = new Poco::Timer(1000, 1000);
    Poco::TimerCallback<MeteorDetector> callback(*this, &MeteorDetector::OnTimerCallback);
    timer_->start(callback);
  } catch (std::exception& exc) {
    std::cout << Poco::format("Failed to initialize MeteorDetector. (exc=%s)", std::string(exc.what())) << std::endl;
    UnInitialize();
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
void MeteorDetector::UnInitialize() {
  timer_ = nullptr;
  thread_pool_ = nullptr;
  normalizer_ = nullptr;
  detector_ = nullptr;
  video_loader_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
void MeteorDetector::OnTimerCallback(Poco::Timer& timer) {
  if (!thread_pool_.isNull()) {
    if (!thread_pool_->Finished()) {
      return;
    }
  }

  // 解析が終了した.
  std::cout << "All threads was finished." << std::endl;
  queue_.wakeUpAll();
}

}}  // uzanka::meteordetector
