/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/ThreadPool.h"
#include "Define.h"
#include "video/VideoLoader.h"
#include "thread/AsyncThread.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief スレッドプール
 *
 * 解析スレッドを管理する.
 */
class AsyncThreadPool {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<AsyncThreadPool> Ptr;

  /*!
   * @brief コンストラクタ
   * @param[in] loader   動画ローダ
   * @param[in] detector 解析エンジン
   * @param[in] exporter データベース出力クラス
   *
   * 処理スレッドを生成する.
   */
  AsyncThreadPool(VideoLoader::Ptr loader, Detector::Ptr detector, Exporter::Ptr exporter);

  /*!
   * @brief デストラクタ
   */
  virtual ~AsyncThreadPool();

  /*!
   * @brief 処理スレッドが完了したか確認する.
   * @retval true  完了した
   * @retval false 完了してない
   *
   * 処理スレッドが完了してれば true を返す.
   */
  bool Finished();

protected:
  Poco::SharedPtr<Poco::ThreadPool> thread_pool_;  //!< スレッドプール
  std::list<AsyncThread::Ptr>       threads_;      //!< 処理スレッド
};

}}  // uzanka::meteordetector
