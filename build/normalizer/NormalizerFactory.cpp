/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/SingletonHolder.h"
#include "NormalizerFactory.h"
#include "Size960x540Normalizer.h"
#include "Size640x360Normalizer.h"  // youtube default display size.
// TODO: ここに正規化エンジンを追加する.

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
NormalizerFactory& NormalizerFactory::GetInstance() {
  static Poco::SingletonHolder<NormalizerFactory> instance_;
  return *(instance_.get());
}

////////////////////////////////////////////////////////////////////////////////
NormalizerFactory::NormalizerFactory() {
  // 使用できる正規化エンジンを登録する.
  Add(Size960x540Normalizer::Name(), &Size960x540Normalizer::Creator);
  Add(Size640x360Normalizer::Name(), &Size640x360Normalizer::Creator);
  // TODO: ここに正規化エンジンを追加する.
}

////////////////////////////////////////////////////////////////////////////////
NormalizerFactory::~NormalizerFactory() {
  normalizers_.clear();
}

////////////////////////////////////////////////////////////////////////////////
void NormalizerFactory::Add(const std::string& normalizer_name, NormalizerCreateMethod method) {
  normalizers_.insert(std::make_pair(normalizer_name, method));
}

////////////////////////////////////////////////////////////////////////////////
bool NormalizerFactory::Exists(const std::string& normalizer_name) {
  NormalizerMap::iterator itr = normalizers_.find(normalizer_name);
  if (itr == normalizers_.end()) {
    return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////
Normalizer::Ptr NormalizerFactory::Create(const std::string& normalizer_name) {
  NormalizerMap::iterator itr = normalizers_.find(normalizer_name);
  if (itr == normalizers_.end()) {
    std::cout << Poco::format("Failed to create normalizer. (name=%s)", normalizer_name) << std::endl;
    return nullptr;
  }
  return itr->second();
}

////////////////////////////////////////////////////////////////////////////////
void NormalizerFactory::Display() {
  std::cout << "Normalizer:" << std::endl;
  for (auto& normalizer : normalizers_) {
    std::string message = Poco::format("  %s", normalizer.first);
    std::cout << message << std::endl;
  }
}

}}  // uzanka::meteordetector
