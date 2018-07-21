/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "normalizer/Normalizer.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 正規化エンジン生成クラス
 */
class NormalizerFactory {
public:
  /*!
   * @brief 正規化エンジン生成クラスのインスタンスを取得する.
   * @return 正規化エンジン生成クラスのインスタンス
   *
   * 正規化エンジン生成クラスのインスタンスを返す.
   */
  static NormalizerFactory& GetInstance();

  /*!
   * @brief コンストラクタ
   */
  NormalizerFactory();

  /*!
   * @brief デストラクタ
   */
  virtual ~NormalizerFactory();

  /*!
   * @brief 正規化エンジンのクラスを生成するメソッド
   * @return 正規化エンジンのベースクラスのポインタ
   *
   * 自クラスのインスタンスを生成して返す処理を実装するメソッドである.
   */
  typedef Normalizer::Ptr (*NormalizerCreateMethod)(void);

  /*!
   * @brief 正規化エンジンを登録する.
   * @param[in]  normalizer_name 正規化エンジンの名前
   * @param[in]  method          正規化エンジンを生成するメソッド
   *
   * 指定した正規化エンジンを登録する.
   */
  void Add(const std::string& normalizer_name, NormalizerCreateMethod method);

  /*!
   * @brief 正規化エンジンが存在するか確認する.
   * @param[in] normalizer_name 正規化エンジンの名前
   * @retval true  存在する
   * @retval false 存在しない
   *
   * 正規化エンジンが存在するか確認する.
   */
  bool Exists(const std::string& normalizer_name);

  /*!
   * @brief 正規化エンジンを生成する.
   * @param[in] normalizer_name 正規化エンジンの名前
   * @return 正規化エンジン
   * @retval nullptr以外 成功
   * @retval nullptr     失敗
   *
   * 指定した名前の正規化エンジンを生成する.
   */
  Normalizer::Ptr Create(const std::string& normalizer_name);

  /*!
   * @brief 一覧を表示する.
   *
   * 保持している正規化エンジンの一覧を標準出力に出力する.
   */
  void Display();

protected:
  typedef std::map<std::string, NormalizerCreateMethod> NormalizerMap;  //!< 正規化エンジンのマップの型
  NormalizerMap normalizers_;  //!< 正規化エンジンのマップ
};

}}  // uzanka::meteordetector
