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
#include "video/ImageHolder.h"
#include "normalizer/Normalizer.h"

namespace uzanka {
namespace meteordetector {

const static int kMaxPreviousFrame = 10;  //!< 取得できる最大フレーム数

/*!
 * @brief 動画ローダクラス
 *
 * 解析する動画を読み込む.
 */
class VideoLoader {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<VideoLoader> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] video_path 動画パス
   * @param[in] normalizer 正規化エンジン
   * @exception Poco::ApplicationException 読み込み失敗
   *
   * 指定された動画をオープンし, 先頭の9フレームを読み込む.
   */
  VideoLoader(const std::string& video_path, Normalizer::Ptr normalizer);

  /*!
   * @brief デストラクタ
   */
  virtual ~VideoLoader();

  /*!
   * @brief フレームを取得する.
   * @param[out] frames 取得したフレーム
   * @param[in]  count  取得するフレーム数(1～10)
   * @return 取得結果
   * @retval true  取得成功
   * @retval false 取得失敗(終了)
   *
   * 今回解析するフレームを過去のフレームを含めて最大10フレームまで取得する.
   * フレームは配列内に逆順に格納し, 配列番号0が最新フレームとなる.
   */
  bool GetFrame(ImageHolder::Vector& frames, const int count = 1);

  /*!
   * @brief 動画名を取得する.
   * @return 動画名
   *
   * 動画名を返す.
   */
  std::string GetName() const;

  /*!
   * @brief フレームの幅を取得する.
   * @return フレームの幅
   *
   * cv::VideoCapture::get(cv::CAP_PROP_FRAME_WIDTH) をフレームの幅として返す.
   */
  int GetFrameWidth() const;

  /*!
   * @brief フレームの高さを取得する.
   * @return フレームの高さ
   *
   * cv::VideoCapture::get(cv::CAP_PROP_FRAME_HEIGHT) をフレームの高さとして返す.
   */
  int GetFrameHeight() const;

  /*!
   * @brief フレーム数を取得する.
   * @return フレーム数
   *
   * cv::VideoCapture::get(cv::CAP_PROP_FRAME_COUNT) をフレーム数として返す.
   */
  Poco::Int64 GetFrames() const;

  /*!
   * @brief 秒間フレーム数を取得する.
   * @return 秒間フレーム数
   *
   * cv::VideoCapture::get(cv::CAP_PROP_FPS) を秒間フレーム数として返す.
   */
  double GetFps() const;

  /*!
   * @brief 動画のプロパティ情報を取得する.
   * @param[in] key プロパティ
   * @return プロパティ情報
   *
   * cv::VideoCapture::get() で取得した値を返す.
   */
  double GetCaptureProperty(const int key) const;

  bool IsOpened();

protected:
  Poco::Mutex                       mutex_;            //!< 排他制御
  std::string                       video_path_;       //!< 動画パス
  Poco::SharedPtr<cv::VideoCapture> video_capture_;    //!< 動画
  ImageHolder::Vector               previous_frames_;  //!< 過去のフレーム(9フレーム)
  Normalizer::Ptr                   normalizer_;
  std::string                       name_;
  int                               width_;
  int                               height_;
  Poco::Int64                       frames_;
  double                            fps_;
};

}}  // uzanka::meteordetector
