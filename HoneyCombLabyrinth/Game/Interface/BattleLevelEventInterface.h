#pragma once
#include "System/Interface/CharacterControllerEventInterface.h"
#include "Game/Interface/EnemyEventInterface.h"
#include "Game/Interface/CharacterEventInterface.h"
#include "System/Interface/MenuControllerEventInterface.h"
#include "Game/GameModeEventInterface.h"
#include "Game/GameStateEventInterface.h"
#include "Game/UiEventInterface.h"

/// <summary>
/// BattleLevelEventInterfaceクラス
/// </summary>
class BattleLevelEventInterface : public CharacterControllerEventInterface,
                                  public EnemyEventInterface,
                                  public MenuControllerEventInterface,
                                  public CharacterEventInterface,
                                  public GameModeEventInterface,
                                  public GameStateEventInterface,
                                  public UiEventInterface
{
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~BattleLevelEventInterface() {
    DEBUG_PRINT(BattleLevelEventInterfaceのデストラクタ);
  }

};
