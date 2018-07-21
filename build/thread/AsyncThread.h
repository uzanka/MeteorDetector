/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/Runnable.h"
#include "Define.h"
#include "video/VideoLoader.h"
#include "detector/Detector.h"
#include "exporter/Exporter.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief 処理スレッド
 *
 * 解析を実行するスレッドになる.
 */
class AsyncThread : public Poco::Runnable {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<AsyncThread> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] loader   動画ローダ
   * @param[in] detector 解析エンジン
   * @param[in] exporter データベース出力クラス
   */
  AsyncThread(VideoLoader::Ptr loader, Detector::Ptr detector, Exporter::Ptr exporter);

  /*!
   * @brief デストラクタ
   */
  virtual ~AsyncThread();

  /*!
   * @brief 処理スレッドを実行する.
   *
   * 解析エンジンを生成する.
   * フレームが終了するまで以下の処理を繰り返す.
   * - VideoLoader::GetFrame() を呼び出し, Detector::RequiredFrameCount() 数のフレームを取得する.
   * - Detector::Run() を呼び出し, フレームを解析する.
   * - 結果が有効であれば, Exporter::Run() を呼び出し, データベースに登録する.
   */
  virtual void run();

protected:
  VideoLoader::Ptr loader_;    //!< 動画ローダ
  Detector::Ptr    detector_;  //!< 解析エンジン
  Exporter::Ptr    exporter_;  //!< データベース出力クラス
};

}}  // uzanka::meteordetector
