/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/File.h"
#include "Poco/Util/HelpFormatter.h"
#include "TheApplication.h"
#include "MeteorDetector.h"
#include "ShutdownHelper.h"
#include "validator/FileOptionValidator.h"
#include "validator/NormalizerOptionValidator.h"
#include "validator/DetectorOptionValidator.h"
#include "Property.h"

POCO_APP_MAIN(uzanka::meteordetector::TheApplication)

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
TheApplication& TheApplication::GetInstance() {
  return static_cast<TheApplication&>(instance());
}

////////////////////////////////////////////////////////////////////////////////
TheApplication::TheApplication()
  : command_id_(COMMAND_ID_RUN) {
}

////////////////////////////////////////////////////////////////////////////////
TheApplication::~TheApplication() {
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::initialize(Poco::Util::Application& self) {
  // "config/MeteorDetector.properties"
  std::string name = Poco::Path(commandPath()).getBaseName();
#ifdef _DEBUG
  // デバッグモードでビルドしている場合は末尾の"d"を削除する.
  if (name[name.length() - 1] == 'd') {
    name = name.substr(0, name.length() - 1);
  }
#endif
  try {
    std::string config_path = Poco::Path(commandPath()).parent().parent().pushDirectory("config").setBaseName(name).setExtension("properties").toString();
    if (Poco::File(config_path).exists()) {
      loadConfiguration(config_path);
    }
  } catch (Poco::Exception& exc) {
    std::cout << Poco::format("Property file not found. (exc=%s)", std::string(exc.what())) << std::endl;
  }

  // TODO: ここで初期化する.
  Poco::Util::Application::initialize(self);
  Property::GetInstance().SetConfig(&config(), commandPath());

  normalizer_name_ = Property::GetInstance().GetDefaultNormalizer();
  detector_name_ = Property::GetInstance().GetDefaultDetector();
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::uninitialize() {
  // TODO: ここで解放する.
  Property::GetInstance().SetConfig(nullptr, commandPath());
  Poco::Util::Application::uninitialize();
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::reinitialize(Poco::Util::Application& self) {
  // TODO: ここで再初期化する.
  Poco::Util::Application::reinitialize(self);
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::defineOptions(Poco::Util::OptionSet& options) {
  Poco::Util::Application::defineOptions(options);

  options.addOption(
    Poco::Util::Option("help", "h", "Display help information on command line arguments.")
      .required(false)
      .repeatable(false));

  options.addOption(
    Poco::Util::Option("property", "p", "Display properties.")
    .required(false)
    .repeatable(false));

  options.addOption(
    Poco::Util::Option("target", "t", "Target video path. (Required option)")
      .argument("<video_path>", true)
      .required(true)
      .repeatable(false)
      .validator(new FileOptionValidator));

  options.addOption(
    Poco::Util::Option("normalizer", "n", "Input video normalizer engine name.")
      .argument("<normalizer_name>", true)
      .required(false)
      .repeatable(false)
      .validator(new NormalizerOptionValidator));

  options.addOption(
    Poco::Util::Option("detector", "d", "Detector engine name.")
      .argument("<detector_name>", true)
      .required(false)
      .repeatable(false)
      .validator(new DetectorOptionValidator));
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::handleOption(const std::string& name, const std::string& value) {
  try {
    Poco::Util::Application::handleOption(name, value);
  } catch (Poco::Exception& exc) {
    std::cout << Poco::format("Failed to handle option. (exc=%s)", exc.displayText()) << std::endl;
    command_id_ = COMMAND_ID_ABORT;
    stopOptionsProcessing();
    return;
  }

  if (name == "help") {
    command_id_ = COMMAND_ID_USAGE;
    stopOptionsProcessing();
    return;
  } else if (name == "property") {
    command_id_ = COMMAND_ID_PROPERTY;
    stopOptionsProcessing();
    return;
  } else if (name == "target") {
    video_path_ = value;
  } else if (name == "normalizer") {
    normalizer_name_ = value;
  } else if (name == "detector") {
    detector_name_ = value;
  }
}

////////////////////////////////////////////////////////////////////////////////
int TheApplication::main(const Poco::Util::Application::ArgVec& args) {
#ifdef _WIN32
  SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
#endif

  switch (command_id_) {
  case COMMAND_ID_USAGE: {
      displayHelp();
      return Poco::Util::Application::EXIT_USAGE;
    }
  case COMMAND_ID_PROPERTY: {
      displayProperty("");
      return Poco::Util::Application::EXIT_OK;
    }
  case COMMAND_ID_RUN: {
      MeteorDetector meteor_detector(video_path_, normalizer_name_, detector_name_);
      if (!meteor_detector.Run()) {
        return Poco::Util::Application::EXIT_SOFTWARE;
      }
      return Poco::Util::Application::EXIT_OK;
    }
  case COMMAND_ID_ABORT:
  default: {
      return Poco::Util::Application::EXIT_SOFTWARE;
    }
  }
}

#ifdef _WIN32
////////////////////////////////////////////////////////////////////////////////
BOOL TheApplication::ConsoleCtrlHandler(DWORD ctrl_type) {
  switch (ctrl_type) {
  case CTRL_C_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_BREAK_EVENT: {
      std::cout << "Detect CTRL+C event." << std::endl;
      ShutdownHelper::GetInstance().SetShutdown();
      return TRUE;
    }
  default: {
      return FALSE;
    }
  }
}
#endif  // _WIN32

////////////////////////////////////////////////////////////////////////////////
void TheApplication::displayHelp() {
  Poco::Util::HelpFormatter helpFormatter(options());
  helpFormatter.setCommand(commandName());
  helpFormatter.setUsage("OPTIONS");
  helpFormatter.setHeader(Poco::format("%s: Detect meteors in video.", kApplicationName));
  helpFormatter.format(std::cout);
}

////////////////////////////////////////////////////////////////////////////////
void TheApplication::displayProperty(const std::string& base) {
  Poco::Util::AbstractConfiguration::Keys keys;
  config().keys(base, keys);
  if (keys.empty()) {
    if (config().hasProperty(base)) {
      std::string message = Poco::format("%s = %s", base, config().getString(base));
      std::cout << message << std::endl;
    }
  } else {
    Poco::Util::AbstractConfiguration::Keys::const_iterator it = keys.begin();
    for (; it != keys.end(); ++it) {
      std::string full_key = base;
      if (!full_key.empty()) {
        full_key += '.';
      }
      full_key.append(*it);
      displayProperty(full_key);
    }
  }
}

}}  // uzanka::meteordetector
