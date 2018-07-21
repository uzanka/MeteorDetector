/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "AsyncThreadPool.h"
#include "detector/DetectorFactory.h"
#include "Property.h"
#include "TheApplication.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
AsyncThreadPool::AsyncThreadPool(VideoLoader::Ptr loader, Detector::Ptr detector, Exporter::Ptr exporter) {

  // 生成するスレッド数を取得する.
  int count = detector->RequiredMaxThread();
  if (count == 0) {
    count = Property::GetInstance().GetMaxDetectorThread();
  }

  thread_pool_ = new Poco::ThreadPool(count, count);

  for (int i = 0; i < count; i++) {
    AsyncThread::Ptr thread = new AsyncThread(loader, detector, exporter);
    threads_.push_back(thread);
    thread_pool_->start(*thread);
  }
}

////////////////////////////////////////////////////////////////////////////////
AsyncThreadPool::~AsyncThreadPool() {
  if (!thread_pool_.isNull()) {
    thread_pool_->joinAll();
    thread_pool_ = nullptr;
  }
  threads_.clear();
}

////////////////////////////////////////////////////////////////////////////////
bool AsyncThreadPool::Finished() {
  if (!thread_pool_.isNull()) {
    return (thread_pool_->used() == 0);
  }
  return true;
}

}}  // uzanka::meteordetector
