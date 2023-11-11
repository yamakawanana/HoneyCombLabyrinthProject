#include <iostream>
#include "DxLib.h"
#include "System/Character.h"
#include "System/LogConsole.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Character::Character(TaskId task_id, TaskManager* task_manager, CharacterEventInterface& event_interface)
  : Task(task_id)
  , task_manager_(task_manager)
  , character_type_(kPlayer)
  , now_phase_(kPreraration)
  , x_coordinate_(0)
  , y_coordinate_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , now_direction_(kNone)
  , display_x_coordinate_(0.0f)
  , display_y_coordinate_(0.0f)
  , is_moving_(false)
  , moving_speed_(0.2f)
  , event_interface_(event_interface)
  , hp_(5)
  , attack_power_(5)
  , defense_power_(5)
  , status_type_(kAlive)
  , hit_x_(0)
  , hit_y_(0)
  , bear_hit_x_(0)
  , bear_hit_y_(0)
  , player_is_dead_(false)
  , bear_is_attacked_(false)
{
  DEBUG_PRINT(Characterのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Character::~Character() {
  DEBUG_PRINT(Characterのデストラクタ);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Character::InitCharacter(int gr_handle) {
  DEBUG_PRINT(Characterクラスの初期化処理);
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Character::UpdateFrame(float time) {
  //DEBUG_PRINT(Characterクラスの毎フレーム更新処理);

  if (now_phase_ != kStop) {

    //表示用のXの位置を取得する
    float x_display_position = GetDisplayXPosition();

    //表示用のYの位置を取得する
    float y_display_position = GetDisplayYPosition();

    //実際のXの到達位置を取得する
    int x_position = GetXPosition() * GetWidth();
    //DEBUG_PRINT_VAR(x_position);

    //実際のYの到達位置を取得する
    int y_position = GetYPosition() * GetHeight();
    //DEBUG_PRINT_VAR(y_position);

    //実際の到達位置と表示用の位置の差を取得する
    float difference_position_x = static_cast<float>(x_position) - x_display_position;
    float difference_position_y = static_cast<float>(y_position) - y_display_position;
    //DEBUG_PRINT_VAR(difference_position_x);
    //DEBUG_PRINT_VAR(difference_position_y);

    //実際の到達位置と表示用の位置の差の絶対値がスピード値の絶対値より大きければ
    if (difference_position_x > moving_speed_) {
      //表示用の位置にスピード値を1ずつ足す
      x_display_position += moving_speed_;
      //DEBUG_PRINT_VAR(x_display_position);
    }
    else if (difference_position_x < -moving_speed_) {
      //表示用の位置からスピード値を1ずつ引く
      x_display_position -= moving_speed_;
      //DEBUG_PRINT_VAR(x_display_position);
    }

    //更新後の表示用のXの位置を設定する
    SetDisplayXPosition(x_display_position);

    //実際の到達位置と表示用の位置の差の絶対値がスピード値の絶対値より大きければ
    if (difference_position_y > moving_speed_) {
      //表示用の位置にスピード値を1ずつ足す
      y_display_position += moving_speed_;
      //DEBUG_PRINT_VAR(y_display_position);
    }
    else if (difference_position_y < -moving_speed_) {
      //表示用の位置からスピード値を1ずつ引く
      y_display_position -= moving_speed_;
      //DEBUG_PRINT_VAR(y_display_position);
    }

    //更新後の表示用のYの位置を設定する
    SetDisplayYPosition(y_display_position);
  }
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void Character::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int Character::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void Character::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int Character::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Character::SetWidth(int size_x) {
  width_= size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int Character::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Character::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int Character::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void Character::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float Character::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void Character::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float Character::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetCharacterType関数の定義
/// </summary>
/// <param = "character_type">キャラクターの種類</param>
/// <returns>なし</returns>
void Character::SetCharacterType(CharacterType character_type) {
  character_type_ = character_type;
}

/// <summary>
/// GetCharacterType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターの種類</returns>
Character::CharacterType Character::GetCharacterType() {
  return character_type_;
}

/// <summary>
/// SetDirectionType関数の定義
/// </summary>
/// <param = "direction">方向の種類</param>
/// <returns>なし</returns>
void Character::SetDirectionType(DirectionType direction) {
  now_direction_ = direction;
}

/// <summary>
/// GetDirectionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Character::DirectionType Character::GetDirectionType() {
  return now_direction_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Character::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Character::PhaseType Character::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetDisplayXPosition関数の定義
/// </summary>
/// <param = "display_x_coordinate">表示用のX座標</param>
/// <returns>なし</returns>
void Character::SetDisplayXPosition(float display_x_coordinate) {
  display_x_coordinate_ = display_x_coordinate;
}

/// <summary>
/// GetDisplayXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のX座標</returns>
float Character::GetDisplayXPosition() {
  return display_x_coordinate_;
}

/// <summary>
/// SetDisplayYPosition関数の定義
/// </summary>
/// <param = "display_y_coordinate">表示用のY座標</param>
/// <returns>なし</returns>
void Character::SetDisplayYPosition(float display_y_coordinate) {
  display_y_coordinate_ = display_y_coordinate;
}

/// <summary>
/// GetDisplayYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のY座標</returns>
float Character::GetDisplayYPosition() {
  return display_y_coordinate_;
}

/// <summary>
/// CheckIsMoving関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>移動中ならtrue、移動中でなければfalse</returns>
bool Character::CheckIsMoving() {
  return is_moving_;
}

/// <summary>
/// SetMovingSpeed関数の定義
/// </summary>
/// <param = "moving_speed">移動時のスピード</param>
/// <returns>なし</returns>
void Character::SetMovingSpeed(float moving_speed) {
  moving_speed_ = moving_speed;
}

/// <summary>
/// GetMovingSpeed関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>移動時のスピード</returns>
float Character::GetMovingSpeed() {
  return moving_speed_;
}

/// <summary>
/// SetXPositions関数の定義
/// </summary>
/// <param = "x">x_positions_に追加したいX位置の整数</param>
/// <param = "num">x_positions_の何番目の要素かを指定する整数</param>
/// <returns>なし</returns>
void Character::SetXPositions(int x, int num) {
  //x_positions_[num] = x;
}

/// <summary>
/// GetXPositions関数の定義
/// </summary>
/// <param>何番目の要素かを指定する整数</param>
/// <returns>x_positions_のi番目の要素の整数</returns>
//int Character::GetXPositions(int i) {
  //return x_positions_[i];
//}

/// <summary>
/// SetYPositions関数の定義
/// </summary>
/// <param = "y">y_positions_に追加したいX位置の整数</param>
/// <param = "num">y_positions_の何番目の要素かを指定する整数</param>
/// <returns>なし</returns>
void Character::SetYPositions(int y, int num) {
  //y_positions_[num] = y;
}

/// <summary>
/// GetYPositions関数の定義
/// </summary>
/// <param>なし</param>
/// <param>何番目の要素かを指定する整数</param>
/// <returns>y_positions_のi番目の要素の整数</returns>
//int Character::GetYPositions(int i) {
  //return y_positions_[i];
//}

/// <summary>
/// SetHp関数の定義
/// </summary>
/// <param = "hp">HP</param>
/// <returns>なし</returns>
void Character::SetHp(int hp) {
  hp_ = hp;
}

/// <summary>
/// GetHp関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>hp_</returns>
int Character::GetHp() {
  return hp_;
}

/// <summary>
/// SetAttackPower関数の定義
/// </summary>
/// <param>攻撃力</param>
/// <returns>なし</returns>
void Character::SetAttackPower(int attack_power) {
  attack_power_ = attack_power;
}

/// <summary>
/// GetAttackPower関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>attack_power_</returns>
int Character::GetAttackPower() {
  return attack_power_;
}

/// <summary>
/// SetDefensePower関数の定義
/// </summary>
/// <param>防御力</param>
/// <returns>なし</returns>
void Character::SetDefensePower(int defense_power) {
  defense_power_ = defense_power;
}

/// <summary>
/// GetDefensePower関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>defense_power_</returns>
int Character::GetDefensePower() {
  return defense_power_;
}

/// <summary>
/// Attack関数の定義
/// </summary>
/// <param>相手キャラクター(参照)</param>
/// <returns>なし</returns>
void Character::Attack(Character& character) {
  int hp = character.GetHp();
  int new_hp = hp - (attack_power_ - character.GetDefensePower());
  character.SetHp(new_hp);
}

/// <summary>
/// IncurDamage関数の定義
/// </summary>
/// <param>相手キャラクター(参照)</param>
/// <returns>なし</returns>
void Character::IncurDamage() {
  hp_ = hp_ - attack_power_;
  if (hp_ <= 0) {
    status_type_ = kDead;
  }
  //SetPlayerIsDead();
}

/// <summary>
/// CheckIsDead関数の定義
/// </summary>
/// <param>現在のステータス</param>
/// <returns>なし</returns>
bool Character::CheckIsDead(){
  if (status_type_ == kDead) {
    return true;
  }
  return false;
}

/// <summary>
/// SetStatusType関数の定義
/// </summary>
/// <param>現在のステータス</param>
/// <returns>なし</returns>
void Character::SetStatusType(StatusType status) {
  status_type_ = status;
}

/// <summary>
/// GetStatusType関数の定義
/// </summary>
/// <param>現在のステータス</param>
/// <returns>なし</returns>
Character::StatusType Character::GetStatusType() {
  return status_type_;
}

/// <summary>
/// SetHitPos関数の宣言
/// </summary>
/// <param = "x">プレイヤーがハチとぶつかった時のX位置</param>
/// <param = "y">プレイヤーがハチとぶつかった時のY位置</param>
/// <returns>なし</returns>
void Character::SetHitPos(int x, int y) {
  hit_x_ = x;
  hit_y_ = y;
}

/// <summary>
/// GetHitXPos関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーがハチとぶつかった時のX位置</returns>
int Character::GetHitXPos() {
  return hit_x_;
}

/// <summary>
/// GetHitYPos関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーがハチとぶつかった時のY位置</returns>
int Character::GetHitYPos() {
  return hit_y_;
}

/// <summary>
/// SetBearHitPos関数の宣言
/// </summary>
/// <param = "x">クマがハチとぶつかった時のX位置</param>
/// <param = "y">クマがハチとぶつかった時のY位置</param>
/// <returns>なし</returns>
void Character::SetBearHitPos(int x, int y) {
  bear_hit_x_ = x;
  bear_hit_y_ = y;
}

/// <summary>
/// GetBearHitXPos関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>クマがハチとぶつかった時のX位置</returns>
int Character::GetBearHitXPos() {
  return bear_hit_x_;
}

/// <summary>
/// GetBearHitYPos関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>クマがハチとぶつかった時のY位置</returns>
int Character::GetBearHitYPos() {
  return bear_hit_y_;
}

/// <summary>
/// GetPlayerIsDead関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>プレイヤーが死んだかの有無</returns>
bool Character::GetPlayerIsDead() {
  return player_is_dead_;
}

/// <summary>
/// SetPlayerIsDead関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Character::SetPlayerIsDead() {
  player_is_dead_ = true;
}

/// <summary>
/// GetBearIsAttacked関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>クマがハチに刺されたかの有無</returns>
bool Character::GetBearIsAttacked() {
  return bear_is_attacked_;
}

/// <summary>
/// SetBearIsAttacked関数の宣言
/// </summary>
/// <param>クマがハチに刺されたかの有無</param>
/// <returns>なし</returns>
void Character::SetBearIsAttacked(bool bear_is_attacked) {
  bear_is_attacked_ = bear_is_attacked;
}