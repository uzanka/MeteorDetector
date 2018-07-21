/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/FileStream.h"
#include "Define.h"
#include "exporter/ResultData.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief データベース出力エンジンのベースクラス
 */
class Exporter {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<Exporter> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] filename 出力ファイル名
   */
  Exporter(const std::string& filename);

  /*!
   * @brief デストラクタ
   */
  virtual ~Exporter();

  /*!
   * @brief 解析結果をデータベース出力する.
   * @param[in] result 解析結果
   *
   * 解析結果をデータベース出力する.
   */
  bool Run(const ResultData& result);

private:
  Poco::Mutex                              lock_;      //!< 排他制御
  std::string                              filename_;  //!< 出力ファイル名
  Poco::SharedPtr<Poco::FileOutputStream > stream_;    //!< ファイル出力先
};

}}  // uzanka::meteordetector
