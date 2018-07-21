/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Define.h"
#include "video/ImageHolder.h"
#include "video/VideoLoader.h"
#include "exporter/ResultData.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief 解析エンジンのベースクラス
 *
 * 複数の処理スレッドに対して解析エンジンのインスタンスは1個だけ生成する.
 * メンバ変数等を利用する場合は, 排他制御を行うこと.
 */
class Detector {
public:
  /*!
   * @brief 本クラスを共有するポインタ
   */
  typedef Poco::SharedPtr<Detector> Ptr;

  /*!
   * @brief コンストラクタ
   */
  Detector();

  /*!
   * @brief デストラクタ
   */
  virtual ~Detector();

  /*
   * @brief 自クラスを生成する.
   *
   * 自クラスを生成して返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  //static Detector::Ptr Creator();

  /*
   * @brief 自クラスの名前を取得する.
   *
   * 自クラスの名前を返す.
   *
   * @note 本クラスを継承するクラスは, 自クラスを生成するメソッドを提供する.
   */
  //static std::string Name();

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
  virtual bool Run(ImageHolder::Vector& frame, ResultData& result) = 0;

  /*!
   * @brief 前処理を行う.
   * @param[in] loader    動画ローダ
   * @param[in] data_path 個別データパス
   * @return 処理結果
   * @retval true  成功
   * @retval false 失敗
   *
   * 前処理を行う.
   * 前処理を行いたい解析エンジンは本メソッドを実装する.
   */
  virtual bool PreProcess(VideoLoader::Ptr loader, const std::string& data_path);

  /*!
   * @brief 後処理を行う.
   * @param[in] loader 動画ローダ
   * @return 処理結果
   * @retval true  成功
   * @retval false 失敗
   *
   * 後処理を行う.
   * 後処理を行いたい解析エンジンは本メソッドを実装する.
   */
  virtual void PostProcess(VideoLoader::Ptr loader);

protected:
  std::string data_path_;  //!< 個別データパス
};

}}  // uzanka::meteordetector
