/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/SingletonHolder.h"
#include "detector/DetectorFactory.h"
#include "detector/HoughLinespDetector.h"
// TODO: ここに解析エンジンを追加する.

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
DetectorFactory& DetectorFactory::GetInstance() {
  static Poco::SingletonHolder<DetectorFactory> instance_;
  return *(instance_.get());
}

////////////////////////////////////////////////////////////////////////////////
DetectorFactory::DetectorFactory() {
  // 使用できる解析エンジンを登録する.
  Add(HoughLinespDetector::Name(), &HoughLinespDetector::Creator);
  // TODO: ここに解析エンジンを追加する.
}

////////////////////////////////////////////////////////////////////////////////
DetectorFactory::~DetectorFactory() {
  detectors_.clear();
}

////////////////////////////////////////////////////////////////////////////////
void DetectorFactory::Add(const std::string& detector_name, DetectorCreateMethod method) {
  detectors_.insert(std::make_pair(detector_name, method));
}

////////////////////////////////////////////////////////////////////////////////
bool DetectorFactory::Exists(const std::string& detector_name) {
  DetectorMap::iterator itr = detectors_.find(detector_name);
  if (itr == detectors_.end()) {
    return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////
Detector::Ptr DetectorFactory::Create(const std::string& detector_name) {
  DetectorMap::iterator itr = detectors_.find(detector_name);
  if (itr == detectors_.end()) {
    std::cout << Poco::format("Failed to create detector. (name=%s)", detector_name) << std::endl;
    return nullptr;
  }
  return itr->second();
}

////////////////////////////////////////////////////////////////////////////////
void DetectorFactory::Display() {
  std::cout << "Detector:" << std::endl;
  for (auto& detector : detectors_) {
    std::cout << Poco::format("  %s", detector.first) << std::endl;
  }
}

}}  // uzanka::meteordetector
