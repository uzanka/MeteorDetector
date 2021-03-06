﻿/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/Util/Validator.h"
#include "Poco/Util/OptionException.h"
#include "Define.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief 解析エンジンオプションをチェックするクラス
 *
 * 解析エンジンオプションで指定された名前が正しいかチェックする.
 */
class DetectorOptionValidator : public Poco::Util::Validator {
public:
  /*!
   * @brief コンストラクタ
   */
  DetectorOptionValidator();

  /*!
   * @brief デストラクタ
   */
  virtual ~DetectorOptionValidator();

  /*!
   * @brief バリデータ
   * @param[in] option オプション情報
   * @param[in] value  検査値
   * @exception Poco::OptionException オプションが不正
   *
   * オプションで指定された値が正しいかチェックする.
   * 不正な場合は, Poco::OptionException をスローする.
   */
  virtual void validate(const Poco::Util::Option& option, const std::string& value);
};

}}  // uzanka::meteordetector
