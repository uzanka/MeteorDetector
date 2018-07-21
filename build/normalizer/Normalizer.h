/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "video/ImageHolder.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 正規化エンジンのベースクラス
 */
class Normalizer {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<Normalizer> Ptr;

  /*!
   * @brief コンストラクタ
   */
  Normalizer();

  /*!
   * @brief デストラクタ
   */
  virtual ~Normalizer();

  /*
   * @brief 自クラスを生成する.
   *
   * 自クラスを生成して返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  //static Normalizer::Ptr Creator();

  /*
   * @brief 自クラスの名前を取得する.
   *
   * 自クラスの名前を返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  //static std::string Name();

  /*!
   * @brief フレームを正規化する.
   * @param[in] frame フレーム
   *
   * フレームを正規化する.
   * 画像のリサイズ, モノクロ化, 誤検出防止のマスキング等を行う.
   */
  virtual void Run(ImageHolder::Ptr frame);
};

}}  // uzanka::meteordetector
