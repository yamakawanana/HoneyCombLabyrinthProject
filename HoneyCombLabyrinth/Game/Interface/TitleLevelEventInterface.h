#pragma once
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// TitleLevelEventInterfaceクラス
/// </summary>
class TitleLevelEventInterface : public MenuControllerEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~TitleLevelEventInterface() {
    DEBUG_PRINT(TitleLevelEventInterfaceのデストラクタ);
  }

};
