#pragma once
#include "System/Task/Task.h"
#include "Game/GameModeEventInterface.h"

/// <summary>
/// GameModeクラス
/// </summary>
class GameMode : public Task {
public:

  /// <summary>
  /// 制限時間を定数kTimeLimitに格納する
  /// </summary>
  static const int kTimeLimit = 30;

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  GameMode(TaskId task_id, GameModeEventInterface& event_interface);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GameMode();

  /// <summary>
  /// SetIsGameClear関数の宣言
  /// </summary>
  /// <param="game_clear">ゲームクリアかの有無</param>
  /// <returns>なし</returns>
  void SetIsGameClear(bool game_clear);

  /// <summary>
  /// GetIsGameClear関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームクリアかの有無</returns>
  bool GetIsGameClear();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// ゲームモードイベントインターフェース
  /// </summary>
  GameModeEventInterface& event_interface_;

  /// <summary>
  /// ゲームクリアかの有無
  /// </summary>
  bool game_clear_;
};

