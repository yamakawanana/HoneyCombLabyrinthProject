#pragma once
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// ResultLevelEventInterfaceクラス
/// </summary>
class ResultLevelEventInterface : public MenuControllerEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~ResultLevelEventInterface() {
    DEBUG_PRINT(ResultLevelEventInterfaceのデストラクタ);
  }

};
