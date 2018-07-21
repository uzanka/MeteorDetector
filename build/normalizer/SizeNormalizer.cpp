/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>  // videoio
#include <opencv2/highgui.hpp>  // highgui
#include <opencv2/imgproc/imgproc.hpp>
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/Var.h"
#include "normalizer/SizeNormalizer.h"
#include "Property.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
SizeNormalizer::SizeNormalizer()
  : width_(0),
    height_(0),
    gray_(false) {
}

////////////////////////////////////////////////////////////////////////////////
SizeNormalizer::~SizeNormalizer() {
}

////////////////////////////////////////////////////////////////////////////////
//Normalizer::Ptr SizeNormalizer::Creator() {
//  return new SizeNormalizer;
//}

////////////////////////////////////////////////////////////////////////////////
std::string SizeNormalizer::Name() {
  return "SizeNormalizer";
}

////////////////////////////////////////////////////////////////////////////////
void SizeNormalizer::Run(ImageHolder::Ptr frame) {
  // リサイズする.
  if ((frame->src_width_ != width_) || (frame->src_height_ != height_)) {
    cv::resize(frame->original_, frame->frame_, cv::Size(), ((double)width_ / frame->src_width_), ((double)height_ / frame->src_height_));
    frame->width_ = frame->frame_.cols;
    frame->height_ = frame->frame_.rows;
  } else {
    Normalizer::Run(frame);
  }

  // delete time counter area
  for (std::size_t i = 0; i < masking_.size(); i += 4) {
    cv::rectangle(frame->frame_, 
      cv::Point(masking_[i + 0], masking_[i + 1]),
      cv::Point(masking_[i + 2], masking_[i + 3]),
      cv::Scalar(0, 0, 0), -1);
  }

  if (gray_) {
    cv::cvtColor(frame->frame_, frame->frame_, CV_RGB2GRAY);
  }
}

////////////////////////////////////////////////////////////////////////////////
void SizeNormalizer::GetProperty(const std::string& name, const int width, const int height) {
  width_ = width;
  height_ = height;

  try {
    std::string value = Property::GetInstance().GetString(Poco::format("normalizer.%s.masking", name), "");
    Poco::StringTokenizer tokenizer(value, ",", Poco::StringTokenizer::TOK_TRIM);
    if (tokenizer.count() >= 4) {
      for (std::size_t i = 0; i < tokenizer.count(); i += 4) {
        masking_.push_back(Poco::Dynamic::Var(tokenizer[i + 0]).convert<int>());
        masking_.push_back(Poco::Dynamic::Var(tokenizer[i + 1]).convert<int>());
        masking_.push_back(Poco::Dynamic::Var(tokenizer[i + 2]).convert<int>());
        masking_.push_back(Poco::Dynamic::Var(tokenizer[i + 3]).convert<int>());
      }
    }

    gray_ = Property::GetInstance().GetInt(Poco::format("normalizer.%s.gray", name), Property::GetInstance().GetInt("normalizer.gray", false)) != 0;
  } catch (Poco::Exception& exc) {
    std::cout << Poco::format("Failed to get property. (exc=%s)", exc.displayText()) << std::endl;
    masking_.clear();
  }
}

}}  // uzanka::meteordetector
