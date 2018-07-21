/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "normalizer/Normalizer.h"
#include "normalizer/SizeNormalizer.h"
#include "video/ImageHolder.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief サイズを変更しマスキングする正規化エンジンのクラス
 */
class Size960x540Normalizer : public SizeNormalizer {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<Size960x540Normalizer> Ptr;

  /*!
   * @brief コンストラクタ
   */
  Size960x540Normalizer();

  /*!
   * @brief デストラクタ
   */
  virtual ~Size960x540Normalizer();

  /*!
   * @brief 自クラスを生成する.
   *
   * 自クラスを生成して返す.
   */
  static Normalizer::Ptr Creator();

  /*!
   * @brief 自クラスの名前を取得する.
   *
   * 自クラスの名前を返す.
   */
  static std::string Name();
};

}}  // uzanka::meteordetector
