#include "Game/Controller/EnemyController.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name = "event_interface">キャラクターコントローラのイベントインターフェースの参照</param>
/// <param name = "character">キャラクターの参照</param>
/// <returns>なし</returns>
EnemyController::EnemyController(Character& character)
  : character_(character) {
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
EnemyController::~EnemyController() {
}

/// <summary>
/// 右上に移動する
/// </summary>
/// <param>なし</param>
/// <returns>上に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkRightUp() {
  //event_interface_.OnPushDirectionKey(character_, Field::kRightUp);
  return true;
}

/// <summary>
/// 右下に移動する
/// </summary>
/// <param>なし</param>
/// <returns>下に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkRightDown() {
  //event_interface_.OnPushDirectionKey(character_, Field::kRightDown);
  return true;
}

/// <summary>
/// 左上に移動する
/// </summary>
/// <param>なし</param>
/// <returns>上に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkLeftUp() {
  //event_interface_.OnPushDirectionKey(character_, Field::kLeftUp);
  return true;
}

/// <summary>
/// 左下に移動する
/// </summary>
/// <param>なし</param>
/// <returns>下に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkLeftDown() {
  //event_interface_.OnPushDirectionKey(character_, Field::kLeftDown);
  return true;
}

/// <summary>
/// 右に移動する
/// </summary>
/// <param>なし</param>
/// <returns>右に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkRight() {
  //event_interface_.OnPushDirectionKey(character_, Field::kRight);
  return true;
}

/// <summary>
/// 左に移動する
/// </summary>
/// <param>なし</param>
/// <returns>左に移動したらtrue、移動出来なかったらfalse</returns>
bool EnemyController::WalkLeft() {
  //event_interface_.OnPushDirectionKey(character_, Field::kLeft);
  return true;
}

/// <summary>
/// ハチがアヒルかクマにぶつかった時の処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void EnemyController::HitCharacter() {
  //event_interface_.BumpCharacter(character_);
}