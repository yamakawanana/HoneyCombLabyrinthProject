#pragma once
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// BootLevelEventInterfaceクラス
/// </summary>
class BootLevelEventInterface : public MenuControllerEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~BootLevelEventInterface() {
    DEBUG_PRINT(BootLevelEventInterfaceのデストラクタ);
  }

};
