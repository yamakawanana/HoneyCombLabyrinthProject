#include <iostream>
#include "Game/GameMode.h"
#include "System/LogConsole.h"
#include "Game/GameModeEventInterface.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameMode::GameMode(TaskId task_id, GameModeEventInterface& event_interface)
  : Task(task_id)
  , event_interface_(event_interface)
  , game_clear_(false)
{
  DEBUG_PRINT(GameModeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameMode::~GameMode() {
  DEBUG_PRINT(GameModeのデストラクタ);
}

/// <summary>
/// SetIsGameClear関数の定義
/// </summary>
/// <param="game_clear">ゲームクリアかの有無</param>
/// <returns>なし</returns>
void GameMode::SetIsGameClear(bool game_clear) {
  game_clear_ = game_clear;
}

/// <summary>
/// GetIsGameClear関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ゲームクリアかの有無</returns>
bool GameMode::GetIsGameClear() {
  return game_clear_;
}