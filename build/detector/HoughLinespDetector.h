/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "detector/Detector.h"
#include "video/ImageHolder.h"
#include "video/VideoLoader.h"
#include "exporter/ResultData.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief HougLinesP を使用した解析エンジンクラス
 */
class HoughLinespDetector : public Detector {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<HoughLinespDetector> Ptr;

  /*!
   * @brief コンストラクタ
   */
  HoughLinespDetector();

  /*!
   * @brief デストラクタ
   */
  virtual ~HoughLinespDetector();

  /*!
   * @brief 自クラスを生成する.
   *
   * 自クラスを生成して返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  static Detector::Ptr Creator();

  /*!
   * @brief 自クラスの名前を取得する.
   *
   * 自クラスの名前を返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  static std::string Name();

  /*!
   * @brief 要求フレーム数を取得する.
   * @return 要求フレーム数(1～10)
   *
   * 解析エンジンで必要なフレーム数を返す.
   */
  virtual int RequiredFrameCount() const;

  /*!
   * @brief 要求スレッド数を取得する.
   * @return 要求スレッド数(0, 1～)
   *
   * 解析エンジンで必要なスレッド数を返す.
   * 0を指定した場合, デフォルトのスレッド数で動作する.
   *
   * @note 時系列処理をしたい場合はシングルスレッドで動作するように1を返す.
   */
  virtual int RequiredMaxThread() const;

  /*!
   * @brief フレームを解析する.
   * @param[in]  frame  フレーム
   * @param[out] result 解析結果
   * @return 解析結果
   * @retval true  保存対象にする
   * @retval false 保存対象にしない
   *
   * フレームを解析する.
   */
  virtual bool Run(ImageHolder::Vector& frame, ResultData& result);

private:
  /*!
   * @brief HoughLinesP解析を行う.
   */
  int HoughLinesP(ImageHolder::Vector& frame, const int position, const std::string& imagename, bool& skip);

  /*!
   * @brief HoughLinesP解析の結果を画面表示する.
   */
  void DebugView(cv::Mat& image, std::vector<cv::Vec4i>& linesp, const std::string& imagename);

  /*!
   * @brief ミリ秒を"HH:MM:SS.mmm"形式に変換する.
   * @param[in] frame_mesc ミリ秒
   * @return "HH:MM:SS.mmm"形式文字列
   *
   * ミリ秒を"HH:MM:SS.mmm"形式の文字列に変換する.
   */
  std::string GetTimeString(const double frame_msec);

protected:
  std::string data_path_;  //!< 個別データパス
};

}}  // uzanka::meteordetector
