/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/SingletonHolder.h"
#include "ShutdownHelper.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
ShutdownHelper& ShutdownHelper::GetInstance() {
  static Poco::SingletonHolder<ShutdownHelper> instance_;
  return *(instance_.get());
}

////////////////////////////////////////////////////////////////////////////////
ShutdownHelper::ShutdownHelper()
  : shutdown_(false) {
}

////////////////////////////////////////////////////////////////////////////////
ShutdownHelper::~ShutdownHelper() {
}

////////////////////////////////////////////////////////////////////////////////
bool ShutdownHelper::IsShutdown() {
  Poco::Mutex::ScopedLock lock(lock_);
  return shutdown_;
}

////////////////////////////////////////////////////////////////////////////////
void ShutdownHelper::SetShutdown() {
  Poco::Mutex::ScopedLock lock(lock_);
  shutdown_ = true;
}

}}  // uzanka::meteordetector
