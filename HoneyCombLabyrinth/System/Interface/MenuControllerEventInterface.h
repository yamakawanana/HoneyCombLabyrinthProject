#pragma once
#include "System/LogConsole.h"

/// <summary>
/// MenuControllerEventInterfaceクラス
/// </summary>
class MenuControllerEventInterface  {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~MenuControllerEventInterface() {
    DEBUG_PRINT(MenuControllerEventInterfaceのデストラクタ);
  }

  /// <summary>
  /// 決定ボタンの押下が押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void OnPushDecide() = 0;

  /// <summary>
  /// 終了ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void OnPushFinish() = 0;

  /// <summary>
  /// ポーズボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void OnPushPause() = 0;

  /// <summary>
  /// BackSpaceボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void OnPushBackSpace() = 0;
};
