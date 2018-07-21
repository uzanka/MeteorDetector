/*
 * MeteorDetector
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Define.h"

namespace uzanka {
namespace meteordetector {

/*!
 * @brief アプリケーションクラス
 *
 * アプリケーションの入り口となるメインクラスである.
 */
class TheApplication : public Poco::Util::Application {
public:
  /*!
   * @brief インスタンスを取得する.
   * @return TheApplication のインスタンス
   *
   * Poco::Util::Applucation::instance() を TheApplication のインスタンスとして返す.
   */
  TheApplication& GetInstance();

  /*!
   * @brief コンストラクタ
   */
  TheApplication();

  /*!
   * @brief デストラクタ
   */
  virtual ~TheApplication();

protected:
  /*!
   * @brief アプリケーションを初期化する.
   * @param[in] self アプリケーション
   *
   * アプリケーション初期化時に呼び出される.
   */
  void initialize(Poco::Util::Application& self);

  /*!
   * @brief アプリケーションを解放する.
   *
   * アプリケーション解放時に呼び出される.
   */
  void uninitialize();

  /*!
   * @brief アプリケーションを再初期化する.
   * @param[in] self アプリケーション
   *
   * アプリケーション再初期化時に呼び出される.
   */
  void reinitialize(Poco::Util::Application& self);

  /*!
   * @brief オプション情報を定義する.
   * @param[out] options オプション情報
   *
   * コマンドラインで使用できるオプションを定義する.
   */
  void defineOptions(Poco::Util::OptionSet& options);

  /*!
   * @brief オプションに対する処理をする.
   * @param[in] name オプション名
   * @param[in] value オプション値
   *
   * オプションに対する情報を退避する.
   */
  void handleOption(const std::string& name, const std::string& value);

  /*!
   * @brief メイン関数
   * @param[in] args コマンドライン引数
   * @return コマンド結果コード
   *
   * メイン関数である.
   */
  int main(const Poco::Util::Application::ArgVec& args);

private:
  typedef enum tagCommandId {
    COMMAND_ID_RUN,       //!< 検出を実行する.
    COMMAND_ID_ABORT,     //!< アプリケーションを終了する.
    COMMAND_ID_USAGE,     //!< 使用方法を表示する.
    COMMAND_ID_PROPERTY   //!< プロパティを表示する.
  } CommandId;

#ifdef _WIN32
  /*!
   * @brief コンソール制御のコールバック関数である.
   * @param[in] ctrl_type 制御タイプ
   * @return 処理結果
   *
   * CTRL+C等でプログラム終了を検知する.
   */
  static BOOL ConsoleCtrlHandler(DWORD ctrl_type);
#endif

  /*!
   * @brief ヘルプを表示する.
   *
   * コンソールにヘルプを表示する.
   */
  void displayHelp();

  /*!
   * @brief プロパティを表示する.
   * @param[in] base ベース名
   *
   * コンソールにプロパティを表示する.
   */
  void displayProperty(const std::string& base);

 private:
  int         command_id_;       //!< 実行コマンドID
  std::string video_path_;       //!< 動画パス
  std::string normalizer_name_;  //!< 正規化エンジン名
  std::string detector_name_;    //!< 解析エンジン名
};

}}  // uzanka::meteordetector
