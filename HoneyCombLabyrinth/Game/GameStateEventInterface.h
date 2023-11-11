#pragma once

/// <summary>
/// GameStateEventInterfaceクラス
/// </summary>
class GameStateEventInterface{
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GameStateEventInterface() {
    //DEBUG_PRINT(GameStateEventInterfaceのデストラクタ);
  }

  /// <summary>
  /// カウントダウンのイベント
  /// </summary>
  /// <param name="remaining_time">残り時間</param>
  /// <returns>なし</returns>
  virtual void CountRemainingTime(int remaining_time) = 0;

  /// <summary>
  /// タイムオーバーのイベント
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void TimeUp() = 0;

};
