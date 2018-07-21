/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "Detector.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 解析エンジン生成クラス
 */
class DetectorFactory {
public:
  /*!
   * @brief 解析エンジン生成クラスのインスタンスを取得する.
   * @return 解析エンジン生成クラスのインスタンス
   *
   * 解析エンジン生成クラスのインスタンスを返す.
   */
  static DetectorFactory& GetInstance();

  /*!
   * @brief コンストラクタ
   */
  DetectorFactory();

  /*!
   * @brief デストラクタ
   */
  virtual ~DetectorFactory();

  /*!
   * @brief 解析エンジンのクラスを生成するメソッド
   * @return 解析エンジンのベースクラスのポインタ
   *
   * 自クラスのインスタンスを生成して返す処理を実装するメソッドである.
   */
  typedef Detector::Ptr (*DetectorCreateMethod)(void);

  /*!
   * @brief 解析エンジンを登録する.
   * @param[in] detector_name 解析エンジンの名前
   * @param[in] method        解析エンジンを生成するメソッド
   *
   * 指定した解析エンジンを登録する.
   */
  void Add(const std::string& detector_name, DetectorCreateMethod method);

  /*!
   * @brief 解析エンジンが存在するか確認する.
   * @param[in] detector_name 解析エンジンの名前
   * @retval true  存在する
   * @retval false 存在しない
   *
   * 解析エンジンが存在するか確認する.
   */
  bool Exists(const std::string& detector_name);

  /*!
   * @brief 解析エンジンを生成する.
   * @param[in] detector_name 解析エンジンの名前
   * @return 解析エンジン
   * @retval nullptr以外 成功
   * @retval nullptr     失敗
   *
   * 指定した名前の解析エンジンを生成する.
   */
  Detector::Ptr Create(const std::string& detector_name);

  /*!
   * @brief 一覧を表示する.
   *
   * 保持している解析エンジンの一覧を標準出力に出力する.
   */
  void Display();

protected:
  typedef std::map<std::string, DetectorCreateMethod> DetectorMap;  //!< 解析エンジンのマップの型
  DetectorMap detectors_;  //!< 解析エンジンのマップ
};

}}  // uzanka::meteordetector
