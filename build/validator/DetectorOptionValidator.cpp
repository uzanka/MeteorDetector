/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "validator/DetectorOptionValidator.h"
#include "detector/DetectorFactory.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
DetectorOptionValidator::DetectorOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
DetectorOptionValidator::~DetectorOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
void DetectorOptionValidator::validate(const Poco::Util::Option& option, const std::string& value) {
  std::string message;
  try {
    if (DetectorFactory::GetInstance().Exists(value)) {
      return;
    }
    message = Poco::format("Specified detector is not exist. (name=%s)", value);
  } catch (Poco::Exception& exc) {
    message = Poco::format("Failed to parse detector. (exc=%s)", exc.displayText());
  }

  std::cout << message << std::endl;
  throw Poco::Util::OptionException(message);
}

}}  // uzanka::meteordetector
