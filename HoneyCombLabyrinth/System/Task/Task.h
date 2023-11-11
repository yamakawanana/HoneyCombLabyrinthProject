#pragma once
#include <iostream>
#include "DxLib.h"

/// <summary>
/// Taskクラス
/// </summary>
class Task {
public:
  /// <summary>
  //列挙型TaskIdを定義する
  /// <summary>
  enum TaskId {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// ブートレベル
    /// </summary>
    kBootLevelTask,

    /// <summary>
    /// タイトルレベル
    /// </summary>
    kTitleLevelTask,

    /// <summary>
    /// キー割り当て変更画面レベル
    /// </summary>
    kChangeKeyboardMapping,

    /// <summary>
    /// ルール説明画面レベル
    /// </summary>
    kRuleGuide,

    /// <summary>
    /// バトル開始前の会話シーン画面レベル
    /// </summary>
    kScenePreBattle,

    /// <summary>
    /// ルールレベル
    /// </summary>
    kRuleLevelTask,

    /// <summary>
    /// バトルレベル
    /// </summary>
    kBattleLevelTask,

    /// <summary>
    /// ゲームオーバー時の会話シーン画面レベル
    /// </summary>
    kSceneGameOver,

    /// <summary>
    /// ゲームクリア時の会話シーン画面レベル
    /// </summary>
    kSceneGameClear,

    /// <summary>
    /// リザルトレベル
    /// </summary>
    kResultLevelTask,

    /// <summary>
    /// メニューコントローラータスク
    /// </summary>
    kMenuController,

    /// <summary>
    /// フィールドタスク
    /// </summary>
    kField,

    /// <summary>
    /// キャラクタータスク
    /// </summary>
    kCharacter,

    /// <summary>
    /// プレイヤータスク
    /// </summary>
    kPlayer,

    /// <summary>
    /// プレイヤーコントローラータスク
    /// </summary>
    kPlayerController,

    /// <summary>
    /// クマさんタスク
    /// </summary>
    kBear,

    /// <summary>
    /// アイテムタスク
    /// </summary>
    kItem,

    /// <summary>
    /// ゲームモードタスク
    /// </summary>
    kGameMode,

    /// <summary>
    /// ゲームステートタスク
    /// </summary>
    kGameState,

    /// <summary>
    /// スタートUIタスク
    /// </summary>
    kStartUi,

    /// <summary>
    /// フィニッシュUIタスク
    /// </summary>
    kFinishUi,

    /// <summary>
    /// バトル情報UIタスク
    /// </summary>
    kInfoUi,

    /// <summary>
    /// ポーズUIタスク
    /// </summary>
    kPauseUi,

    /// <summary>
    /// 赤いハチタスク
    /// </summary>
    kRedBee,

    /// <summary>
    /// 赤いハチタスクの最大値
    /// </summary>
    kMaxRedBeeNum = kRedBee + 10,

    /// <summary>
    /// 黄色いハチタスク
    /// </summary>
    kYellowBee,

    /// <summary>
    /// 黄色いハチタスクの最大値
    /// </summary>
    kMaxYellowBeeNum = kYellowBee + 10,

    /// <summary>
    /// ゴールの旗タスク
    /// </summary>
    kGoalFlag,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~Task();

  /// <summary>
  /// GetId関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>id_</returns>
  TaskId GetId();

  /// <summary>
  /// SetId関数の宣言
  /// </summary>
  /// <param name = "id">TaskId型のid</param>
  /// <returns>なし</returns>
  void SetId(TaskId id);

  /// <summary>
  /// GetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>task_unload_</returns>
  bool GetTaskUnload();

  /// <summary>
  /// SetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetTaskUnload();

  /// <summary>
  /// ResetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void ResetTaskUnload();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  virtual void UpdateFrame(float time);

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void RenderFrame();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクID
  /// </summary>
  TaskId id_;

  /// </summary>
  //タスクを下ろしたかの有無
  /// </summary>
  bool task_unload_;
};