#pragma once
#include "System/Interface/CharacterControllerEventInterface.h"
#include "System/Character.h"

class EnemyController {

public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param name = "event_interface">キャラクターコントローラのイベントインターフェースの参照</param>
  /// <param name = "character">キャラクターの参照</param>
  /// <returns>なし</returns>
  EnemyController(CharacterControllerEventInterface& controller_event_interface, Character& character);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~EnemyController();

  /// <summary>
  /// 右上に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>上に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkRightUp();

  /// <summary>
  /// 右下に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>下に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkRightDown();

  /// <summary>
  /// 左上に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>上に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkLeftUp();

  /// <summary>
  /// 左下に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>下に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkLeftDown();

  /// <summary>
  /// 右に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>右に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkRight();

  /// <summary>
  /// 左に移動する
  /// </summary>
  /// <param>なし</param>
  /// <returns>左に移動したらtrue、移動出来なかったらfalse</returns>
  bool WalkLeft();

  /// <summary>
  /// ハチがアヒルかクマにぶつかった時の処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void HitCharacter();

private:

  /// <summary>
  /// キャラクターコントローラのイベントインターフェース
  /// </summary>
  CharacterControllerEventInterface& event_interface_;

  /// <summary>
  /// キャラクター
  /// </summary>
  Character& character_;
};
