/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Timer.h"
#include "Poco/NotificationQueue.h"
#include "Define.h"
#include "normalizer/Normalizer.h"
#include "detector/Detector.h"
#include "exporter/Exporter.h"
#include "video/VideoLoader.h"
#include "thread/AsyncThreadPool.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief 流星解析クラス
 *
 * 動画を読み込み, フレームを解析するためのメインクラスである.
 */
class MeteorDetector {
public:
  /*!
   * @brief コンストラクタ
   * @param[in] video_path      動画パス
   * @param[in] normalizer_name 正規化エンジン名
   * @param[in] detector_name   解析エンジン名
   */
  MeteorDetector(
    const std::string& video_path,
    const std::string& normalizer_name,
    const std::string& detector_name);

  /*!
   * @brief デストラクタ
   */
  virtual ~MeteorDetector();

  bool Run();

  bool Initialize();
  void UnInitialize();
  void OnTimerCallback(Poco::Timer& timer);

private:
  std::string                  video_path_;       //!< 動画パス
  std::string                  normalizer_name_;  //!< 正規化フィルタ名
  std::string                  detector_name_;    //!< 検出フィルタ名
  Normalizer::Ptr              normalizer_;       //!< 正規化フィルタ
  Detector::Ptr                detector_;         //!< 検出フィルタ
  Exporter::Ptr                exporter_;         //!< データベース出力
  VideoLoader::Ptr             video_loader_;     //!< 動画ローダ
  AsyncThreadPool::Ptr         thread_pool_;      //!< スレッドプール
  Poco::SharedPtr<Poco::Timer> timer_;            //!< 終了検出タイマ
  Poco::NotificationQueue      queue_;            //!< 終了待ちキュー
};

}}  // uzanka::meteordetector
