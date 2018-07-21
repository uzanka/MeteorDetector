/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>  // videoio
#include <opencv2/highgui.hpp>  // highgui
#include <opencv2/imgproc/imgproc.hpp>
#include "detector/HoughLinespDetector.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
HoughLinespDetector::HoughLinespDetector() {
}

////////////////////////////////////////////////////////////////////////////////
HoughLinespDetector::~HoughLinespDetector() {
}

////////////////////////////////////////////////////////////////////////////////
Detector::Ptr HoughLinespDetector::Creator() {
  return new HoughLinespDetector;
}

////////////////////////////////////////////////////////////////////////////////
std::string HoughLinespDetector::Name() {
  return "HoughLinespDetector";
}

////////////////////////////////////////////////////////////////////////////////
int HoughLinespDetector::RequiredFrameCount() const {
  return 4;
}

////////////////////////////////////////////////////////////////////////////////
int HoughLinespDetector::RequiredMaxThread() const {
  return 4;
}

////////////////////////////////////////////////////////////////////////////////
bool HoughLinespDetector::Run(ImageHolder::Vector& frame, ResultData& result) {
  bool ret = false;
  double count = 0;

  cv::Mat mask;
  cv::absdiff(frame[2]->frame_, frame[3]->frame_, mask);
  cv::threshold(mask, mask, 20, 255, cv::THRESH_BINARY);
  cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), 1);
  cv::bitwise_not(mask, mask);

  cv::Mat f1, f2;
  cv::bitwise_and(frame[0]->frame_, mask, f1);
  cv::bitwise_and(frame[1]->frame_, mask, f2);

  cv::Mat dst;
  cv::absdiff(f1, f2, dst);
  cv::threshold(dst, dst, 20, 255, cv::THRESH_BINARY);
  cv::dilate(dst, dst, cv::Mat(), cv::Point(-1, -1), 1);
  std::vector<cv::Vec4i> linesp;
  cv::HoughLinesP(dst, linesp, 1, CV_PI / 180.0, 20, 10, 0);
  if (linesp.size() >= 20) {
    linesp.clear();
  }

  if (linesp.size() > 0) {
    ret = true;
    cv::Vec4i pt = linesp.at(0);
    std::string msg = Poco::format("%s : (%d,%d)-(%d,%d)", GetTimeString(frame[0]->frame_msec_), pt[0], pt[1], pt[2], pt[3]);
    result.result_[0] = linesp.size();
    result.result_[1] = sqrt(pow(fabs(pt[0] - pt[2]), 2) + pow(fabs(pt[1] - pt[3]), 2));
    result.message_ = msg;
  }

#ifdef _DEBUG
  std::string imagename = Poco::format("%Ld %s", frame[0]->frame_no_, GetTimeString(frame[0]->frame_msec_));
  DebugView(dst, linesp, imagename);
#endif

  return ret;
}

////////////////////////////////////////////////////////////////////////////////
int HoughLinespDetector::HoughLinesP(ImageHolder::Vector& frame, const int position, const std::string& imagename, bool& skip) {
  cv::Mat dst;
  cv::absdiff(frame[0]->frame_, frame[position]->frame_, dst);
  cv::threshold(dst, dst, 20, 255, cv::THRESH_BINARY);
  cv::dilate(dst, dst, cv::Mat(), cv::Point(-1, -1), 1);
  std::vector<cv::Vec4i> linesp;
  cv::HoughLinesP(dst, linesp, 1, CV_PI / 180.0, 20, 10, 0);
  if (linesp.size() >= 20) {
    linesp.clear();
    skip = true;
  }
#ifdef _DEBUG
  DebugView(dst, linesp, imagename);
#endif
  return (int)linesp.size();
}

////////////////////////////////////////////////////////////////////////////////
void HoughLinespDetector::DebugView(cv::Mat& image, std::vector<cv::Vec4i>& linesp, const std::string& imagename) {
#ifdef _DEBUG
  static Poco::Int64 interval = 0;
  cv::Mat view;
  cv::cvtColor(image, view, CV_GRAY2BGR);

  bool flag = false;
  if (linesp.size() > 0) {
    cv::Vec4i pt = linesp.at(0);
    std::string msg = Poco::format("(%d,%d)-(%d,%d), length=%f", pt[0], pt[1], pt[2], pt[3], sqrt(pow(fabs(pt[0] - pt[2]), 2) + pow(fabs(pt[1] - pt[3]), 2)));
    std::cout << Poco::format("%s: %z = %s", imagename, linesp.size(), msg) << std::endl;
    flag = true;
  } else {
    interval++;
    if (interval % 400 == 0) {
      flag = true;
    }
  }

  if (flag) {
    cv::putText(view, imagename, cv::Point(6, 26), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0));
    cv::putText(view, imagename, cv::Point(4, 24), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0));
    cv::putText(view, imagename, cv::Point(5, 25), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255));
    cv::imshow("view", view);
    cv::waitKey(1);
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
std::string HoughLinespDetector::GetTimeString(const double frame_msec) {
  int64_t value = (int64_t)frame_msec;
  int msec = (int)(value % 1000);
  value /= 1000;
  int second = (int)(value % 60);
  value /= 60;
  int minute = (int)(value % 60);
  value /= 60;
  int hour = (int)(value);
  return Poco::format("%02d:%02d:%02d.%03d", hour, minute, second, msec);
}

}}  // uzanka::meteordetector
