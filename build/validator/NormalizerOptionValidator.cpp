/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "validator/NormalizerOptionValidator.h"
#include "normalizer/NormalizerFactory.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
NormalizerOptionValidator::NormalizerOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
NormalizerOptionValidator::~NormalizerOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
void NormalizerOptionValidator::validate(const Poco::Util::Option& option, const std::string& value) {
  std::string message;
  try {
    if (NormalizerFactory::GetInstance().Exists(value)) {
      return;
    }
    message = Poco::format("Specified normalizer is not exist. (name=%s)", value);
  } catch (Poco::Exception& exc) {
    message = Poco::format("Failed to parse normalizer. (exc=%s)", exc.displayText());
  }

  std::cout << message << std::endl;
  throw Poco::Util::OptionException(message);
}

}}  // uzanka::meteordetector
