/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef DEFINE_INCLUDED
#define DEFINE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "Poco/Poco.h"
#include "Poco/Format.h"
#include "Poco/String.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include "Poco/Exception.h"

namespace uzanka {
namespace meteordetector {

const std::string kApplicationName = "MeteorDetector";

}}  // uzanka::meteordetector

using namespace uzanka::meteordetector;

#endif  // DEFINE_INCLUDED
