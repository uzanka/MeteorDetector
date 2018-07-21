/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/SharedPtr.h"
#include "Define.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 解析結果を保持するクラス
 *
 * 解析結果を保持する.
 */
class ResultData {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<ResultData> Ptr;

  /*!
   * @brief 解析結果のリスト
   */
  typedef std::list<ResultData::Ptr> List;

  /*!
   * @brief コンストラクタ
   */
  ResultData();

  /*!
   * @brief デストラクタ
   */
  virtual ~ResultData();

public:
  Poco::Int64 frame_no_;    //!< フレーム番号
  double      frame_msec_;  //!< フレームミリ秒
  int         mark_;        //!< マーク(0なら対象外)
  double      result_[10];  //!< 検出情報(実数)
  std::string message_;     //!< 検出情報(文字列)
};

////////////////////////////////////////////////////////////////////////////////
inline ResultData::ResultData()
  : frame_no_(0),
    frame_msec_(0),
    mark_(0),
    message_("") {
  for (int i = 0; i < 10; i++) {
    result_[i] = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////
inline ResultData::~ResultData() {
}

}}  // uzanka::meteordetector
