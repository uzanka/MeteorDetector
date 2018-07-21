/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "video/ImageHolder.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
ImageHolder::ImageHolder()
  : frame_no_(0),
    frame_msec_(0),
    src_width_(0),
    src_height_(0),
    width_(0),
    height_(0) {
}

////////////////////////////////////////////////////////////////////////////////
ImageHolder::ImageHolder(Poco::SharedPtr<cv::VideoCapture> capture)
  : frame_no_(0),
    frame_msec_(0),
    src_width_(0),
    src_height_(0),
    width_(0),
    height_(0) {
  // 1フレーム取得する.
  frame_no_ = static_cast<int64_t>(capture->get(cv::CAP_PROP_POS_FRAMES));
  frame_msec_ = capture->get(cv::CAP_PROP_POS_MSEC);
  src_width_ = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_WIDTH));
  src_height_ = static_cast<int>(capture->get(cv::CAP_PROP_FRAME_HEIGHT));
  width_ = src_width_;
  height_ = src_height_;
  *capture >> original_;
}

////////////////////////////////////////////////////////////////////////////////
ImageHolder::ImageHolder(const std::string filename)
  : frame_no_(0),
    frame_msec_(0),
    src_width_(0),
    src_height_(0),
    width_(0),
    height_(0) {
  // 1フレーム取得する.
  original_ = cv::imread(filename);
}

////////////////////////////////////////////////////////////////////////////////
ImageHolder::~ImageHolder() {
}

////////////////////////////////////////////////////////////////////////////////
bool ImageHolder::Empty() const {
  return original_.empty();
}

}}  // uzanka::meteordetector
