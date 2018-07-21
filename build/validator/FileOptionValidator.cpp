/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/File.h"
#include "validator/FileOptionValidator.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
FileOptionValidator::FileOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
FileOptionValidator::~FileOptionValidator() {
}

////////////////////////////////////////////////////////////////////////////////
void FileOptionValidator::validate(const Poco::Util::Option& option, const std::string& value) {
  std::string message;
  try {
    Poco::File file(value);
    if (file.exists() && file.isFile()) {
      return;
    }
    message = Poco::format("Specified file is not exist. (file=%s)", value);
  } catch (Poco::Exception& exc) {
    message = Poco::format("Failed to parse file. (exc=%s)", exc.displayText());
  }

  std::cout << message << std::endl;
  throw Poco::Util::OptionException(message);
}

}}  // uzanka::meteordetector
