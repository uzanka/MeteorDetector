/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "normalizer/Size640x360Normalizer.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
Size640x360Normalizer::Size640x360Normalizer() {
  GetProperty(Name(), 640, 360);
  gray_ = true;
}

////////////////////////////////////////////////////////////////////////////////
Size640x360Normalizer::~Size640x360Normalizer() {
}

////////////////////////////////////////////////////////////////////////////////
Normalizer::Ptr Size640x360Normalizer::Creator() {
  return new Size640x360Normalizer;
}

////////////////////////////////////////////////////////////////////////////////
std::string Size640x360Normalizer::Name() {
  return "Size640x360Normalizer";
}

}}  // uzanka::meteordetector
