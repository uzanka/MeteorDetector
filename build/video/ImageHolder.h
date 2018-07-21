/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>  // videoio
#include <opencv2/highgui.hpp>  // highgui
#include "Define.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief 画像保持クラス
 */
class ImageHolder {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<ImageHolder> Ptr;

  /*!
   * @brief 本クラスのリスト
   */
  typedef std::vector<ImageHolder::Ptr> Vector;

  /*!
   * @brief 本クラスのリスト
   */
  typedef std::list<ImageHolder::Ptr> List;

  /*!
   * @brief コンストラクタ
   */
  ImageHolder();

  /*!
   * @brief コンストラクタ
   * @param[in] capture  動画
   *
   * 指定された動画のフレームを読み込む.
   */
  ImageHolder(Poco::SharedPtr<cv::VideoCapture> capture);

  /*!
   * @brief コンストラクタ
   * @param[in] filename 画像ファイル名
   *
   * 指定された画像を読み込む.
   */
  ImageHolder(const std::string filename);

  /*!
   * @brief デストラクタ
   */
  virtual ~ImageHolder();

  /*!
   * @brief フレームが存在しないか確認する.
   * @retval true  フレームが存在しない
   * @retval false フレームが存在する
   *
   * フレームを保持していなければ true を返す.
   */
  bool Empty() const;

public:
  cv::Mat     original_;    //!< フレーム(元画像)
  cv::Mat     frame_;       //!< フレーム(正規化画像)
  int64_t     frame_no_;    //!< フレーム番号
  double      frame_msec_;  //!< フレームミリ秒
  int         src_width_;   //!< 元画像の幅
  int         src_height_;  //!< 元画像の高さ
  int         width_;       //!< 正規化後の幅
  int         height_;      //!< 正規化後の高さ
};

}}  // uzanka::meteordetector
