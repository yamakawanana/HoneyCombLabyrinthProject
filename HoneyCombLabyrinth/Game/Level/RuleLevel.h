﻿#pragma once
#include <array>
#include "DxLib.h"
#include "System/Level/Level.h"
#include "System/LogConsole.h"
#include "System/Controller/MenuController.h"
#include "Game/Interface/RuleLevelEventInterface.h"

/// <summary>
/// RuleLevelクラス
/// </summary>
class RuleLevel : public Level, public RuleLevelEventInterface {
public:

  /// <summary>
  /// ルール説明ののグラフィックハンドルの配列の要素数を定数kRuleElementNumberに格納する
  /// </summary>
  static const int kRuleElementNumber = 4;

  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// 破棄フェーズ
    /// </summary>
    kDelete,
  };


  /// <summary>
  //フェーズの種類の列挙型PhaseType型を定義する
  /// <summary>
  enum PhaseType {
    /// <summary>
    /// 1ページ目
    /// </summary>
    kFirst,

    /// <summary>
    /// 2ページ目
    /// </summary>
    kSecond,

    /// <summary>
    /// 3ページ目
    /// </summary>
    kThird,

    /// <summary>
    /// 4ページ目
    /// </summary>
    kFourth,

    /// <summary>
    /// レベルのフェードアウト
    /// </summary>
    kFadeOut,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  RuleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  RuleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~RuleLevel();

  /// <summary>
  /// 決定ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDecide();

  /// <summary>
  /// 終了ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushFinish();

  /// <summary>
  /// ポーズボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushPause();

  /// <summary>
  /// BackSpaceボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushBackSpace();

  /// <summary>
  /// SetRuleGrHandle関数の宣言
  /// </summary>
  /// <param = "rule_handle">Ruleのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetRuleGrHandle(std::array<int, kRuleElementNumber> rule_handle);

  /// <summary>
  /// GetRuleGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>Ruleのグラフィックハンドル</returns>
  int GetRuleGrHandle(int element_num);

  /// <summary>
  /// SetTriangleGrHandle関数の宣言
  /// </summary>
  /// <param = "triangle_handle">三角形の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTriangleGrHandle(int triangle_handle);

  /// <summary>
  /// GetTriangleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>三角形の画像のグラフィックハンドル</returns>
  int GetTriangleGrHandle();

  /// <summary>
  /// SetBgmHandle関数の宣言
  /// </summary>
  /// <param = "bgm_handle">BGMのサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetBgmHandle(int bgm_handle);

  /// <summary>
  /// GetBgmHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BGMのサウンドハンドル</returns>
  int GetBgmHandle();

  /// <summary>
  /// SetNextPageSoundHandle関数の宣言
  /// </summary>
  /// <param = "next_page_handle">ルール説明の次のページに遷移する時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetNextPageSoundHandle(int next_page_handle);

  /// <summary>
  /// GetNextPageSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ルール説明の次のページに遷移する時のサウンドハンドル</returns>
  int GetNextPageSoundHandle();

  /// <summary>
  /// SetNextLevelSoundHandle関数の宣言
  /// </summary>
  /// <param = "next_level_handle">次のレベルに遷移する時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetNextLevelSoundHandle(int next_level_handle);

  /// <summary>
  /// GetNextLevelSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>次のレベルに遷移する時のサウンドハンドル</returns>
  int GetNextLevelSoundHandle();

  /// <summary>
  /// SetWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetWidth(int size_x);

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// SetHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHeight(int size_y);

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// SetHalfWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetHalfWidth(float size_half_x);

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// SetHalfHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHalfHeight(float size_half_y);

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut();

protected:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool InitializeUpdate(float time) override;

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool ProcessingUpdate(float time) override;

  /// <summary>
  /// 毎フレームの描画処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void ProcessingRender() override;

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time) override;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 終了の有無
  /// </summary>
  bool is_finish_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// メニューコントローラ
  /// </summary>
  MenuController* menu_controller_;

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// フェーズの種類
  /// </summary>
  PhaseType phase_type_;

  /// <summary>
  /// Ruleのグラフィックハンドル
  /// </summary>
  std::array<int, kRuleElementNumber> rule_handle_;

  /// <summary>
  /// 三角形の画像のグラフィックハンドル
  /// </summary>
  int triangle_handle_;

  /// <summary>
  /// 画像の幅
  /// </summary>
  int width_;

  /// <summary>
  /// 画像の高さ
  /// </summary>
  int height_;

  /// <summary>
  /// 画像の幅の半分
  /// </summary>
  float half_width_;

  /// <summary>
  /// 画像の高さの半分
  /// </summary>
  float half_height_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// ルール説明の次のページに遷移する時のサウンドハンドル
  /// </summary>
  int next_page_handle_;

  /// <summary>
  /// 次のレベルに遷移する時のサウンドハンドル
  /// </summary>
  int next_level_handle_;
};