/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#include "Poco/SingletonHolder.h"
#include "Poco/Util/MapConfiguration.h"
#include "Poco/Path.h"
#include "Poco/DateTime.h"
#include "Property.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
Property& Property::GetInstance() {
  static Poco::SingletonHolder<Property> instance_;
  return *(instance_.get());
}

////////////////////////////////////////////////////////////////////////////////
Property::Property()
  : config_(nullptr) {
}

////////////////////////////////////////////////////////////////////////////////
Property::~Property() {
  config_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
void Property::SetConfig(Poco::Util::LayeredConfiguration* config, const std::string& command_path) {
  config_ = config;
  base_path_ = Poco::Path(command_path).parent().parent().toString();
  if (base_path_.empty()) {
    base_path_ = Poco::Path(".").absolute().toString();
  }
}

////////////////////////////////////////////////////////////////////////////////
std::string Property::GetString(const std::string& key, const std::string& default_value) {
  if (config_ == nullptr) {
    return default_value;
  }
  return config_->getString(key, default_value);
}

////////////////////////////////////////////////////////////////////////////////
int Property::GetInt(const std::string& key, const int default_value) {
  try {
    if (config_ == nullptr) {
      return default_value;
    }
    return config_->getInt(key, default_value);
  } catch (Poco::Exception& exc) {
    std::cout << Poco::format("Failed to convert property type. (key=%s, exc=%s)", key, exc.displayText()) << std::endl;
    return default_value;
  }
}

////////////////////////////////////////////////////////////////////////////////
std::string Property::GetDataPath() {
  std::string value = GetString("path.data", "");
  if (value.empty()) {
    value = Poco::Path(base_path_).pushDirectory("data").toString();
  }
  return value;
}

////////////////////////////////////////////////////////////////////////////////
std::string Property::GetDefaultNormalizer() {
  return GetString("normalizer.default", "Size960x540Normalizer");
}

////////////////////////////////////////////////////////////////////////////////
std::string Property::GetDefaultDetector() {
  return GetString("detector.default", "HoughLinespDetector");
}

////////////////////////////////////////////////////////////////////////////////
int Property::GetMaxDetectorThread() {
  return GetInt("detector.thread.max", 4);
}

////////////////////////////////////////////////////////////////////////////////
std::string Property::GetDefaultExporter(const std::string& video_name) {
  std::string filename = GetString("exporter.default", "$DATAPATH$$VIDEO$_$TIME$.csv");
  std::string data_path = GetDataPath();
  Poco::DateTime now;
  std::string timename = Poco::format("%04d%02d%02dT%02d%02d%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  filename = Poco::replace(filename, std::string("$DATAPATH$"), data_path);
  filename = Poco::replace(filename, std::string("$VIDEO$"), video_name);
  filename = Poco::replace(filename, std::string("$TIME$"), timename);
  return filename;
}

}}  // uzanka::meteordetector
