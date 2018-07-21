/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/Util/LayeredConfiguration.h"
#include "Define.h"

namespace uzanka {
namespace meteordetector {

////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief プロパティクラス
 *
 * プロパティファイルからプロパティを読み込む.
 */
class Property {
public:
  /*!
   * @brief プロパティクラスのインスタンスを取得する.
   * @return プロパティクラスのインスタンス
   *
   * プロパティクラスのインスタンスを返す.
   */
  static Property& GetInstance();

  /*!
   * @brief コンストラクタ
   */
  Property();

  /*!
   * @brief デストラクタ
   */
  virtual ~Property();

  /*!
   * @brief プロパティを設定する.
   * @param[in] config       TheApplicationに設定したプロパティ情報
   * @param[in] command_path コマンドパス
   *
   * プロパティ情報を設定する.
   */
  void SetConfig(Poco::Util::LayeredConfiguration* config, const std::string& command_path);

  /*!
   * @brief 文字列プロパティを取得する.
   * @param[in] key           キー名
   * @param[in] default_value デフォルト値
   * @return 取得値
   *
   * プロパティファイルから文字列プロパティを取得する.
   * 取得できない場合は, デフォルト値を返す.
   */
  std::string GetString(const std::string& key, const std::string& default_value);

  /*!
   * @brief 数値プロパティを取得する.
   * @param[in] key           キー名
   * @param[in] default_value デフォルト値
   * @return 取得値
   *
   * プロパティファイルから数値プロパティを取得する.
   * 取得できない場合は, デフォルト値を返す.
   */
  int GetInt(const std::string& key, const int default_value);

  // application
  /*!
  * @brief データパスを取得する.
  * @return データパス
  *
  * データパスを取得する.
  */
  std::string GetDataPath();

  // normalizer
  /*!
   * @brief デフォルトの正規化エンジン名を取得する.
   * @return 正規化エンジン名
   *
   * デフォルトの正規化エンジン名を取得する.
   */
  std::string GetDefaultNormalizer();

  // detector
  /*!
   * @brief デフォルトの解析エンジン名を取得する.
   * @return 解析エンジン名
   *
   * デフォルトの解析エンジン名を取得する.
   */
  std::string GetDefaultDetector();

  /*!
   * @brief 解析スレッド数を取得する.
   * @return 解析スレッド数
   *
   * 解析スレッド数を取得する.
   */
  int GetMaxDetectorThread();

  // exporter
  /*!
   * @brief エクスポートCSVファイル名を取得する.
   * @param[in] video_name 動画名
   * @return CSVファイル名
   *
   * エクスポートCSVファイル名を取得する.
   */
  std::string GetDefaultExporter(const std::string& video_name);

private:
  Poco::Util::LayeredConfiguration* config_;
  std::string                       base_path_;  //!< ベースパス
};

}}  // uzanka::meteordetector
