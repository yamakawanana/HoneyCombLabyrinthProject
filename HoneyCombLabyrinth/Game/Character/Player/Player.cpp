#include <iostream>
#include <thread>
#include "Game//Character/Player/Player.h"
#include "System/LogConsole.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// プレイヤーの描画開始X位置を定数kStartPlayerXに格納する
  /// </summary>
  static const int kStartPlayerX = -50;

  /// <summary>
  /// プレイヤーの描画開始Y位置を定数kStartPlayerYに格納する
  /// </summary>
  static const int kStartPlayerY = -10;

  /// <summary>
  /// プレイヤーの描画Y位置を調整するためにdisplay_x_coordinateと掛ける値を定数kRenderPlayerXに格納する
  /// </summary>
  static const float kRenderPlayerX = 0.8f;

  /// <summary>
  /// プレイヤーの描画Y位置を調整するためにdisplay_y_coordinateと掛ける値を定数kRenderPlayerYに格納する
  /// </summary>
  static const float kRenderPlayerY = 1.4f;

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.8f;

  /// <summary>
  /// アヒルがダメージを受けるアニメーションのリセット時間を定数kAnimationLimitTimeに格納する
  /// </summary>
  static const float kAnimationLimitTime = 3.6f;

  /// <summary>
  /// フェードインの開始時間を定数kFadeInTimeに格納する
  /// </summary>
  static const float kFadeInTime = 1.5f;

  /// <summary>
  /// 配列の2つ目の要素に切り替える時間を定数kAnimeFirstに格納する
  /// </summary>
  static const float kAnimeFirst = 0.2f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kAnimeSecondに格納する
  /// </summary>
  static const float kAnimeSecond = 0.4f;

  /// <summary>
  /// 配列の4つ目の要素に切り替える時間を定数kAnimeThirdに格納する
  /// </summary>
  static const float kAnimeThird = 0.6f;

  /// <summary>
  /// 配列の5つ目の要素に切り替える時間を定数kAnimeFourthに格納する
  /// </summary>
  static const float kAnimeFourth = 0.8f;

  /// <summary>
  /// 配列の5つ目の要素に切り替える時間を定数kAnimeFifthに格納する
  /// </summary>
  static const float kAnimeFifth = 1.0f;

  /// <summary>
  /// 配列の2つ目の要素に切り替える時間を定数kWalkFirstに格納する
  /// </summary>
  static const float kWalkFirst = 0.2f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kWalkSecondに格納する
  /// </summary>
  static const float kWalkSecond = 0.4f;

  /// <summary>
  /// 配列の2つ目の要素に戻す時間を定数kWalkThirdに格納する
  /// </summary>
  static const float kWalkThird = 0.6f;

  /// <summary>
  /// 配列の1つ目の要素番号を定数kFirstElementに格納する
  /// </summary>
  static const int kFirstElement = 0;

  /// <summary>
  /// 配列の2つ目の要素番号を定数kSecondElementに格納する
  /// </summary>
  static const int kSecondElement = 1;

  /// <summary>
  /// 配列の3つ目の要素番号を定数kThirdElementに格納する
  /// </summary>
  static const int kThirdElement = 2;

  /// <summary>
  /// 配列の4つ目の要素番号を定数kFourthElementに格納する
  /// </summary>
  static const int kFourthElement = 3;

  /// <summary>
  /// 配列の5つ目の要素番号を定数kFifthElementに格納する
  /// </summary>
  static const int kFifthElement = 4;

  /// <summary>
  /// 配列の6つ目の要素番号を定数kSixthElementに格納する
  /// </summary>
  static const int kSixthElement = 5;

  /// <summary>
  /// ダメージを受けたプレイヤーの描画開始X位置を定数kStartDamagePlayerXに格納する
  /// </summary>
  static const int kStartDamagePlayerX = -95;

  /// <summary>
  /// ダメージを受けたプレイヤーの描画開始Y位置を定数kStartDamagePlayerYに格納する
  /// </summary>
  static const int kStartDamagePlayerY = -25;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Player::Player(TaskId task_id, TaskManager* task_manager, CharacterEventInterface& event_interface, std::array<int, kDuckElementNumber> duck_handle)
  : Character(task_id, task_manager, event_interface)
  , gr_handle_(duck_handle)
  , change_amount_(100)
  , accumulation_time_(0.0f)
  , damage_accumulation_time_(0.0f)
  , is_damage_animation_end_(false)
  , gr_damage_handle_{}
{
  DEBUG_PRINT(Playerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Player::~Player() {
  DEBUG_PRINT(Playerのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void Player::UpdateFrame(float time) {
  //DEBUG_PRINT(Playerの毎フレーム更新処理);
  if (now_phase_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kLimitTime) {
      accumulation_time_ = 0.0f;
    }

    bool player_is_dead = GetPlayerIsDead();

    if (player_is_dead) {
      damage_accumulation_time_ = damage_accumulation_time_ + time;
      if (damage_accumulation_time_ >= kFadeInTime) {
        //ダメージを受けたアニメーションの終了有無をtrueにする
        is_damage_animation_end_ = true;
      }
      if (damage_accumulation_time_ >= kAnimationLimitTime) {
        //累積時間をリセットする
        damage_accumulation_time_ = 0.0f;
      }
    }

    Character::UpdateFrame(time);
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void Player::RenderFrame() {
  //DEBUG_PRINT(Playerの毎フレーム描画処理);
  if (now_phase_ == kPlaying || now_phase_ == kStop || now_phase_ == kFinish) {
    //X位置を取得する
    int x_coordinate = GetXPosition();
    //Y位置を取得する
    int y_coordinate = GetYPosition();

    //表示用のX位置を取得する
    float display_x_coordinate = GetDisplayXPosition();
    //DEBUG_PRINT_VAR(display_x_coordinate);

    //表示用のY位置を取得する
    float display_y_coordinate = GetDisplayYPosition();
    //DEBUG_PRINT_VAR(display_y_coordinate);

    //幅を取得する
    int width = GetWidth();
    
    //高さを取得する
    int height = GetHeight();

    //半分の幅を取得する
    float half_width = GetHalfWidth();
    
    //半分の高さを取得する
    float half_height = GetHalfHeight();

    //ゲーム情報のインスタンスを取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //ゲーム情報からマップの左上の座標を取得する
    int map_left_x = game_info->GetMapLeftX();
    int map_left_y = game_info->GetMapLeftY();

    bool player_is_dead = GetPlayerIsDead();

    if (!player_is_dead) {
      //表示用の位置を使って描画する
      if (accumulation_time_ < kWalkFirst) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderPlayerX) + kStartPlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderPlayerY) + kStartPlayerY, gr_handle_[kFirstElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkFirst && accumulation_time_ < kWalkSecond) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderPlayerX) + kStartPlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderPlayerY) + kStartPlayerY, gr_handle_[kSecondElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkSecond && accumulation_time_ < kWalkThird) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderPlayerX) + kStartPlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderPlayerY) + kStartPlayerY, gr_handle_[kThirdElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkThird && accumulation_time_ < kLimitTime) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderPlayerX) + kStartPlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderPlayerY) + kStartPlayerY, gr_handle_[kSecondElement], TRUE);
      }
    }
    //アヒルがダメージを受けた時は描画を変える
    else if (player_is_dead) {
      DrawDamagedPlayer(display_x_coordinate, display_y_coordinate);
    }

    //ぶつかった位置の表示位置を取得する
    int hit_display_x = GetHitXPos() * width;
    int hit_display_y = GetHitYPos() * height;
    //現在の表示位置とぶつかった位置の表示位置の差の絶対値を求める
    float difference_display_x = abs(display_x_coordinate - hit_display_x);
    //DEBUG_PRINT_VAR(difference_display_x);
    float difference_display_y = abs(display_y_coordinate - hit_display_y);
    //DEBUG_PRINT_VAR(difference_display_y);

    //現在の表示位置とぶつかった位置の表示位置の差の絶対値が1以下なら、ハチとぶつかった後の最後の描画が終わったことにする
    if (difference_display_x <= 1 && difference_display_y <= 1) {
      SetPlayerIsDead();
      //DEBUG_PRINT(プレイヤーの最後の描画が終わった);
    }
  }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Player::GetGrHandle(int element_num) {
  return gr_handle_[element_num];
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetGrHandle(int gr_handle) {
  //gr_handle_ = gr_handle;
}


/// <summary>
/// GetDamageGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Player::GetDamageGrHandle(int element_num) {
  return gr_damage_handle_[element_num];
}

/// <summary>
/// SetDamageGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Player::SetDamageGrHandle(std::array<int, kDamageDuckElementNumber> damage_duck_handle) {
  gr_damage_handle_ = damage_duck_handle;
}

/// <summary>
/// ダメージを受けたプレイヤーを表示する処理
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>なし</returns>
void Player::DrawDamagedPlayer(float x, float y) {
  //DEBUG_PRINT(DrawDamagedPlayer);
  //DEBUG_PRINT_VAR(damage_accumulation_time_);
  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲーム情報からマップの左上の座標を取得する
  int map_left_x = game_info->GetMapLeftX();
  int map_left_y = game_info->GetMapLeftY();

  //表示用の位置を使って描画する
  if (damage_accumulation_time_ < kAnimeFirst) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kFirstElement], TRUE);
  }
  else if (damage_accumulation_time_ >= kAnimeFirst && damage_accumulation_time_ < kAnimeSecond) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kSecondElement], TRUE);
  }
  else if (damage_accumulation_time_ >= kAnimeSecond && damage_accumulation_time_ < kAnimeThird) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kThirdElement], TRUE);
  }
  else if (damage_accumulation_time_ >= kAnimeThird && damage_accumulation_time_ < kAnimeFourth) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kFourthElement], TRUE);
  }
  else if (damage_accumulation_time_ >= kAnimeFourth && damage_accumulation_time_ < kAnimeFifth) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kFifthElement], TRUE);
  }
  else if (damage_accumulation_time_ >= kAnimeFifth && damage_accumulation_time_ < kAnimationLimitTime) {
    DrawGraph(map_left_x + static_cast<int>(x * kRenderPlayerX) + kStartDamagePlayerX, map_left_y + static_cast<int>(y * kRenderPlayerY) + kStartDamagePlayerY, gr_damage_handle_[kSixthElement], TRUE);
  }

}

/// <summary>
/// CheckIsDamagedAnimationEnd関数の定義
/// </summary>
/// <param>ダメージを受けたアニメーションの終了有無</param>
/// <returns>なし</returns>
bool Player::CheckIsDamagedAnimationEnd() {
  if (is_damage_animation_end_) {
    return true;
  }
  return false;
}