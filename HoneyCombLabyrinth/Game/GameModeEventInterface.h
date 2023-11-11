#pragma once

/// <summary>
/// GameModeEventInterfaceクラス
/// </summary>
class GameModeEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GameModeEventInterface() {
    //DEBUG_PRINT(GameModeEventInterfaceのデストラクタ);
  }

  /// <summary>
  /// ゲームクリア終了のイベント
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void GameClear() = 0;

};
