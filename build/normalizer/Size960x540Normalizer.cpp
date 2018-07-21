/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Size960x540Normalizer.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
Size960x540Normalizer::Size960x540Normalizer() {
  GetProperty(Name(), 960, 540);
  gray_ = true;
  masking_ = { 710,   0, 960,  35,
                 0, 510, 280, 540 };
}

////////////////////////////////////////////////////////////////////////////////
Size960x540Normalizer::~Size960x540Normalizer() {
}

////////////////////////////////////////////////////////////////////////////////
Normalizer::Ptr Size960x540Normalizer::Creator() {
  return new Size960x540Normalizer;
}

////////////////////////////////////////////////////////////////////////////////
std::string Size960x540Normalizer::Name() {
  return "Size960x540Normalizer";
}

}}  // uzanka::meteordetector
