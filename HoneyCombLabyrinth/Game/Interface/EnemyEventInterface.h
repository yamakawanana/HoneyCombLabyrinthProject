#pragma once
#include "Game/Field.h"

/// <summary>
/// 敵ベースクラスの前方宣言
/// </summary>
class EnemyBase;

/// <summary>
/// 敵イベントのインターフェース
/// </summary>
class EnemyEventInterface {

public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~EnemyEventInterface() {}

  /// <summary>
  /// 移動範囲をチェックする
  /// </summary>
  /// <param name = "enemy">敵キャラクターベースクラスの参照</param>
  /// <returns>なし</returns>
  virtual void CheckWalkDistance(EnemyBase& enemy) = 0;

};
