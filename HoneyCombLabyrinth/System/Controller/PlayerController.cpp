#include <iostream>
#include <DxLib.h>
#include <time.h>
#include <windows.h>
#include "System/Controller/PlayerController.h"
#include "System/Task/Task.h"
#include "System/LogConsole.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// int型配列key_codesの要素数を定数kElementNumberに格納する
  /// </summary>
  static const int kElementNumber = 2;

  /// <summary>
  /// 猶予時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.15f;

  /// <summary>
  /// ２つのキーの同時押し時の猶予時間を定数kTwoKeyLimitTimeに格納する
  /// </summary>
  static const float kTwoKeyLimitTime = 0.1f;

  /// <summary>
  //待ち時間を定数kWaitTimeに格納
  /// <summary>
  static const float kWaitTime = 1.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
PlayerController::PlayerController(TaskId task_id, CharacterControllerEventInterface& character_interface, Character& character)
  : Task(task_id)
  , key_type_(kNone)
  , character_event_interface_(character_interface)
  , pushed_{ false }
  , pushed_right_up_{ false }
  , pushed_right_down_{ false }
  , pushed_left_up_{ false }
  , pushed_left_down_{ false }
  , pushed_right_{ false }
  , pushed_left_{ false }
  , character_(character)
  , accumulation_time_(0.0f)
  , right_accumulation_time_(0)
  , left_accumulation_time_(0)
  , two_key_accumulation_time_(false)
  , change_amount_(0)
  , long_pushed_(false)
{
  DEBUG_PRINT(PlayerControllerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
PlayerController::~PlayerController() {
  DEBUG_PRINT(PlayerControllerのデストラクタ);
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void PlayerController::UpdateFrame(float time) {
  if (character_.GetPhaseType() == Character::kPlaying) {
    //DEBUG_PRINT(PlayerControllerの毎フレーム更新処理);

  //いずれかのキーが押されたかの有無
  //bool any_key_pushed = false;

  //accumulation_time_ = accumulation_time_ + time;
  //DEBUG_PRINT_VAR(accumulation_time_);
  //DEBUG_PRINT_VAR(two_key_accumulation_time_);

    if (IsPushedRightUpKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kRightUp);
      long_pushed_ = false;
      accumulation_time_ = 0.0f;
      //any_key_pushed = true;
      two_key_accumulation_time_ = 0.0f;
      DEBUG_PRINT(右上キーが押された);
    }
    if (IsPushedRightDownKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kRightDown);
      long_pushed_ = false;
      accumulation_time_ = 0.0f;
      two_key_accumulation_time_ = 0.0f;
      //any_key_pushed = true;
      DEBUG_PRINT(右下キーが押された);
    }
    if (IsPushedLeftUpKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kLeftUp);
      long_pushed_ = false;
      accumulation_time_ = 0.0f;
      two_key_accumulation_time_ = 0.0f;
      //any_key_pushed = true;
      DEBUG_PRINT(左上キーが押された);
    }
    if (IsPushedLeftDownKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kLeftDown);
      long_pushed_ = false;
      accumulation_time_ = 0.0f;
      two_key_accumulation_time_ = 0.0f;
      DEBUG_PRINT(左下キーが押された);
    }
    else if (IsPushedRightKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kRight);
      long_pushed_ = false;
      accumulation_time_ = 0.0f;
      two_key_accumulation_time_ = 0.0f;
      //any_key_pushed = true;
      pushed_right_ = false;
      DEBUG_PRINT(右キーが押された);
    }
    else if (IsPushedLeftKey(time) && long_pushed_ == true) {
      character_event_interface_.OnPushDirectionKey(character_, Field::kLeft);
      long_pushed_ = false;
      //any_key_pushed = true;
      accumulation_time_ = 0.0f;
      two_key_accumulation_time_ = 0.0f;

      DEBUG_PRINT(左キーが押された);
    }

    //if (!any_key_pushed) {
    //  accumulation_time_ = 0.0f;
    //}
  }
}

///// <summary>
///// IsPushedUpKey関数の定義
///// </summary>
///// <param name>なし</param>
///// <returns>上キーを押されている：true、上キーを押されていない：false</returns>
//bool PlayerController::IsPushedUpKey() {
//  return IsPushedKey(KEY_INPUT_UP, pushed_[static_cast<int>(kUpKey)]);
//}
//
///// <summary>
///// IsPushedDownKey関数の定義
///// </summary>
///// <param name>なし</param>
///// <returns>下キーを押されている：true、下キーを押されていない：false</returns>
//bool PlayerController::IsPushedDownKey() {
//  return IsPushedKey(KEY_INPUT_DOWN, pushed_[static_cast<int>(kDownKey)]);
//}

/// <summary>
/// IsPushedRightUpKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>右上キーを押されている：true、右上キーを押されていない：false</returns>
bool PlayerController::IsPushedRightUpKey(float time) {
  return IsPushedAllKey(KEY_INPUT_UP, KEY_INPUT_RIGHT, pushed_right_up_, time);
}

/// <summary>
/// IsPushedRightDownKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>右下キーを押されている：true、右下キーを押されていない：false</returns>
bool PlayerController::IsPushedRightDownKey(float time) {
  return IsPushedAllKey(KEY_INPUT_DOWN, KEY_INPUT_RIGHT, pushed_right_down_, time);
}

/// <summary>
/// IsPushedLeftUpKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>左上キーを押されている：true、左上キーを押されていない：false</returns>
bool PlayerController::IsPushedLeftUpKey(float time) {
  return IsPushedAllKey(KEY_INPUT_UP, KEY_INPUT_LEFT, pushed_left_up_, time);
}

/// <summary>
/// IsPushedLeftDownKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>左下キーを押されている：true、左下キーを押されていない：false</returns>
bool PlayerController::IsPushedLeftDownKey(float time) {
  return IsPushedAllKey(KEY_INPUT_DOWN, KEY_INPUT_LEFT, pushed_left_down_, time);
}

/// <summary>
/// IsPushedRightKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>右キーを押されている：true、右キーを押されていない：false</returns>
bool PlayerController::IsPushedRightKey(float time) {
  return IsPushedKey(KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_RIGHT, pushed_right_, time);
}

/// <summary>
/// IsPushedLeftKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>左キーを押されている：true、左キーを押されていない：false</returns>
bool PlayerController::IsPushedLeftKey(float time) {
  return IsPushedKey(KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT, pushed_left_, time);
}

/// <summary>
/// IsPushedKey関数の宣言
/// </summary>
/// <param name = "up_key_code">上キーの種類up_key_code</param>
/// <param name = "down_key_code">下キーの種類down_key_code</param>
/// <param name = "key_type">指定されたキーの種類key_type</param>
/// <param name = "pushed">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
/// <returns>指定されたキーを押されている：true、押されていない：false</returns>
bool PlayerController::IsPushedKey(int up_key_code, int down_key_code, int key_code, bool& pushed, float time) {
  //DEBUG_PRINT(IsPushedKey);

  //キーが押されたら、pushedを「押されている状態」とする。同時に上か下のキーも押されていた場合はfalseにする。
  if (CheckHitKey(up_key_code) == 0 && CheckHitKey(down_key_code) == 0 && CheckHitKey(key_code) == 1) {
    pushed = true;
    //右あるいは左のキーのみを押されている時間をカウントする
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kLimitTime) {
      accumulation_time_ = 0.0f;
      long_pushed_ = true;
      return true;
    }
  }
  
  return false;
}

/// <summary>
/// IsPushedAllKey関数の定義
/// </summary>
/// <param name = "first_key_code">キーの種類first_key_code</param>
/// <param name = "second_key_code">キーの種類second_key_code</param>
/// <param name = "all_pushed_">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
/// <returns>指定されたキーを押されている：true、押されていない：false</returns>
bool PlayerController::IsPushedAllKey(int first_key_code, int second_key_code, bool& all_pushed_, float time) {
  //DEBUG_PRINT(IsPushedAllKey);

  //key_typesに格納されたキーの種類を順番に確認し、キーが両方押されていたら、all_keys_pushedをtrueにする
  if (CheckHitKey(first_key_code) != 0 && CheckHitKey(second_key_code) != 0) {
    all_pushed_ = true;
    //右あるいは左のみのキーが押された時にカウントされていたaccumulation_time_はリセットする
    accumulation_time_ = 0.0f;

    //２つのキーが同時押しされている時間をカウントする
    two_key_accumulation_time_ = two_key_accumulation_time_ + time;
    if (two_key_accumulation_time_ >= kTwoKeyLimitTime) {
      two_key_accumulation_time_ = 0.0f;
      long_pushed_ = true;
      return true;
    }
  }

  return false;
}
