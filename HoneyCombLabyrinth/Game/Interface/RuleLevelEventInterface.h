#pragma once
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// RuleLevelEventInterfaceクラス
/// </summary>
class RuleLevelEventInterface : public MenuControllerEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~RuleLevelEventInterface() {
    DEBUG_PRINT(RuleLevelEventInterfaceのデストラクタ);
  }

};
