/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/Path.h"
#include "Poco/Format.h"
#include "Poco/String.h"
#include "Poco/Dynamic/Var.h"
#include "video/VideoLoader.h"
#include "TheApplication.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
VideoLoader::VideoLoader(const std::string& video_path, Normalizer::Ptr normalizer)
  : video_path_(video_path),
    normalizer_(normalizer) {

  // 動画をオープンする.
  video_capture_ = new cv::VideoCapture(video_path_.c_str());
  if (!video_capture_->isOpened()) {
    throw Poco::ApplicationException(Poco::format("Failed to open video file. (path=%s)", video_path_));
  }

  Poco::Path file(video_path);
  name_   = file.getFileName();
  width_  = static_cast<int>(video_capture_->get(cv::CAP_PROP_FRAME_WIDTH));
  height_ = static_cast<int>(video_capture_->get(cv::CAP_PROP_FRAME_HEIGHT));
  frames_ = static_cast<int>(video_capture_->get(cv::CAP_PROP_FRAME_COUNT));
  fps_    = video_capture_->get(cv::CAP_PROP_FPS);

  // 先頭9フレームを読み込む.
  for (int i = 1; i < kMaxPreviousFrame; i++) {
    ImageHolder::Ptr frame = new ImageHolder(video_capture_);
    if (frame->original_.empty()) {
      throw Poco::ApplicationException("The number of frames is insufficient.");
    }
    normalizer_->Run(frame);
    previous_frames_.push_back(frame);
  }
}

////////////////////////////////////////////////////////////////////////////////
VideoLoader::~VideoLoader() {
  previous_frames_.clear();
  video_capture_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
bool VideoLoader::GetFrame(ImageHolder::Vector& frames, const int count) {
  Poco::Mutex::ScopedLock lock(mutex_);

  if ((count < 1) || (count > kMaxPreviousFrame)) {
    throw Poco::ApplicationException("Invalid parameter.");
  }

  // 1フレーム読み込む.
  ImageHolder::Ptr frame = new ImageHolder(video_capture_);
  if (frame->Empty()) {
    std::cout << "Video EOF detected." << std::endl;
    return false;
  }

  normalizer_->Run(frame);

  // 新しいフレームを追加する.
  previous_frames_.insert(previous_frames_.begin(), frame);

  // 要求されたフレーム数を返す.
  for (std::size_t i = 0; i < count; i++) {
    frames.push_back(previous_frames_.at(i));
  }

  // 古いフレームを削除する.
  previous_frames_.pop_back();
  return true;
}

////////////////////////////////////////////////////////////////////////////////
std::string VideoLoader::GetName() const {
  return name_;
}

////////////////////////////////////////////////////////////////////////////////
int VideoLoader::GetFrameWidth() const {
  return width_;
}

////////////////////////////////////////////////////////////////////////////////
int VideoLoader::GetFrameHeight() const {
  return height_;
}

////////////////////////////////////////////////////////////////////////////////
Poco::Int64 VideoLoader::GetFrames() const {
  return frames_;
}

////////////////////////////////////////////////////////////////////////////////
double VideoLoader::GetFps() const {
  return fps_;
}

////////////////////////////////////////////////////////////////////////////////
double VideoLoader::GetCaptureProperty(const int key) const {
  return video_capture_->get(key);
}

////////////////////////////////////////////////////////////////////////////////
bool VideoLoader::IsOpened() {
  if (video_capture_.isNull()) {
    return false;
  }
  return video_capture_->isOpened();
}

}}  // uzanka::meteordetector
