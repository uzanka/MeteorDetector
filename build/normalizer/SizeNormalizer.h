/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "normalizer/Normalizer.h"
#include "video/ImageHolder.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief サイズを変更しマスキングする正規化エンジンのクラス
 */
class SizeNormalizer : public Normalizer {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<SizeNormalizer> Ptr;

  /*!
   * @brief コンストラクタ
   */
  SizeNormalizer();

  /*!
   * @brief デストラクタ
   */
  virtual ~SizeNormalizer();

  /*
   * @brief 自クラスを生成する.
   *
   * 自クラスを生成して返す.
   */
  //static Normalizer::Ptr Creator();

  /*!
   * @brief 自クラスの名前を取得する.
   *
   * 自クラスの名前を返す.
   */
  static std::string Name();

  /*!
   * @brief フレームを正規化する.
   * @param[in]  frame  フレーム
   *
   * 何もしない.
   */
  virtual void Run(ImageHolder::Ptr frame);

protected:
  /*!
   * @brief プロパティ情報を読み込む.
   * @param[in] name   正規化エンジン名
   * @param[in] width  幅
   * @param[in] heigth 高さ
   *
   * normalizer.正規化エンジン名.masking を読み込む.
   * カンマで区切られた数字を4ポイント毎にrectangle情報と考えてメンバ変数に格納する.
   */
  void GetProperty(const std::string& name, const int width, const int heigth);

protected:
  int              width_;    //!< 正規化する幅
  int              height_;   //!< 正規化する高さ
  bool             gray_;     //!< 白黒画像にする
  std::vector<int> masking_;  //!< マスキング情報(4ポイント毎にrectangleを表す)
};

}}  // uzanka::meteordetector
