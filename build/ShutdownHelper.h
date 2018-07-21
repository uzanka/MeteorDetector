/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief 緊急停止支援クラス
 *
 * 緊急停止を支援するクラスである.
 */
class ShutdownHelper {
public:
  /*!
   * @brief インスタンスを取得する.
   * @return ShutdownHelper のインスタンス
   *
   * ShutdownHelper のインスタンスを返す.
   */
  static ShutdownHelper& GetInstance();

  /*!
   * @brief コンストラクタ
   */
  ShutdownHelper();

  /*!
   * @brief デストラクタ
   */
  virtual ~ShutdownHelper();

  /*!
   * @brief 緊急停止フラグをチェックする.
   * @retval true  緊急停止
   * @retval false 運転中
   *
   * 緊急停止フラグを返す.
   */
  bool IsShutdown();

  /*!
   * @brief 緊急停止フラグをセットする.
   *
   * 緊急停止フラグをONにする.
   */
  void SetShutdown();

 private:
  Poco::Mutex lock_;      //!< 排他制御
  bool        shutdown_;  //!< 緊急停止フラグ
};

}}  // uzanka::meteordetector
