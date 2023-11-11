#pragma once
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// Characterクラスの前方宣言
/// </summary>
class Character;

/// <summary>
/// CharacterEventInterfaceクラス
/// </summary>
class CharacterEventInterface{
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~CharacterEventInterface() {
    DEBUG_PRINT(CharacterEventInterfaceのデストラクタ);
  }

  /// <summary>
  /// 死んだ時のイベント(引数のキャラをタスクマネージャーから降ろす)
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void UnloadCharacter(Character& character) = 0;

};
