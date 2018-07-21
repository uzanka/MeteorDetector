/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "exporter/Exporter.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
Exporter::Exporter(const std::string& filename)
  : filename_(filename) {
  stream_ = new Poco::FileOutputStream(filename);
  if (!stream_->good()) {
    throw Poco::ApplicationException(Poco::format("Failed to open database. (filename=%s)", filename));
  }
  std::cout << Poco::format("Exporter: %s", filename) << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
Exporter::~Exporter() {
  if (!stream_.isNull()) {
    stream_->close();
    stream_ = nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////
bool Exporter::Run(const ResultData& result) {
  Poco::Mutex::ScopedLock lock(lock_);
  std::string body = Poco::format("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    result.result_[0],
    result.result_[1],
    result.result_[2],
    result.result_[3],
    result.result_[4],
    result.result_[5],
    result.result_[6],
    result.result_[7],
    result.result_[8],
    result.result_[9]);
  std::string text = Poco::format("%Ld,%f,%d,%s,\"%s\"",
    result.frame_no_,
    result.frame_msec_,
    result.mark_,
    body,
    result.message_);
  *stream_ << text << std::endl;
  return true;
}

}}  // uzanka::meteordetector
