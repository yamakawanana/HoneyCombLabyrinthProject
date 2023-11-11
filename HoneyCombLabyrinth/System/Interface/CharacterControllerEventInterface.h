#pragma once
#include "System/LogConsole.h"
#include "System/Character.h"
#include "Game/Field.h"

/// <summary>
/// CharacterControllerEventInterfaceクラス
/// </summary>
class CharacterControllerEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~CharacterControllerEventInterface() {
    DEBUG_PRINT(CharacterControllerEventInterfaceのデストラクタ);
  }

  /// <summary>
  /// 各方向キーが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void OnPushDirectionKey(Character& character, Field::DirectionType direction) = 0;

  /// <summary>
  /// キャラクターがぶつかるイベント
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void BumpCharacter(Character& character) = 0;

};
