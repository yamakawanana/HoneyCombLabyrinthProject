#include <iostream>
#include "Game/Character/Player/Bear.h"
#include "System/LogConsole.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// クマの描画開始X位置を定数kStartBearXに格納する
  /// </summary>
  static const int kStartBearX = -52;

  /// <summary>
  /// クマの描画開始Y位置を定数kStartBearYに格納する
  /// </summary>
  static const int kStartBearY = -10;

  /// <summary>
  /// クマの描画Y位置を調整するためにdisplay_x_coordinateと掛ける値を定数kRenderBearXに格納する
  /// </summary>
  static const float kRenderBearX = 0.8f;

  /// <summary>
  /// クマの描画Y位置を調整するためにdisplay_y_coordinateと掛ける値を定数kRenderBearYに格納する
  /// </summary>
  static const float kRenderBearY = 1.4f;

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.8f;

  /// <summary>
  /// bear_handle_の配列の2つ目の要素に切り替える時間を定数kWalkFirstに格納する
  /// </summary>
  static const float kWalkFirst = 0.2f;

  /// <summary>
  /// bear_handle_の配列の3つ目の要素に切り替える時間を定数kWalkSecondに格納する
  /// </summary>
  static const float kWalkSecond = 0.4f;

  /// <summary>
  /// bear_handle_の配列の2つ目の要素に戻す時間を定数kWalkThirdに格納する
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
  /// ダメージを受けたクマの描画開始X位置を定数kStartDamagePlayerXに格納する
  /// </summary>
  static const int kStartDamagePlayerX = -60;

  /// <summary>
  /// ダメージを受けたクマの描画開始Y位置を定数kStartDamagePlayerYに格納する
  /// </summary>
  static const int kStartDamagePlayerY = -25;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Bear::Bear(TaskId task_id, TaskManager* task_manager, std::array<int, kBearElementNumber> bear_handle, std::array<int, kBearElementNumber> damage_bear_handle)
  : Character(task_id, task_manager)
  , bear_handle_(bear_handle)
  , damage_bear_handle_(damage_bear_handle)
  , smile_bear_handle_(0)
  , change_amount_(1)
  , bear_type_(kWalking)
  , duck_x_(0)
  , duck_y_(0)
  , duck_now_x_(0)
  , duck_now_y_(0)
  , accumulation_time_(0.0f)
  , damage_accumulation_time_(0.0f)
  , smile_accumulation_time_(0.0f)
  , route_count_(0)
{
  DEBUG_PRINT(Bearのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Bear::~Bear() {
  DEBUG_PRINT(Bearのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void Bear::UpdateFrame(float time) {
  if (now_phase_ != kStop) {
    //DEBUG_PRINT(Bearの毎フレーム更新処理);
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kLimitTime) {
      accumulation_time_ = 0.0f;
    }
    //DEBUG_PRINT_VAR(accumulation_time_);

    //アヒルさんがいた位置情報を受け取り、X位置とY位置を更新する
    if (bear_type_ == kWalking) {
      if (duck_x_ != 0 && duck_y_ != 0) {
        SetXPosition(duck_x_);
        SetYPosition(duck_y_);
      }
    }
    else if (bear_type_ == kRunning) {
      //nearest_route_に保存されている要素の逆順にX位置とY位置を更新する
      SetXPosition(nearest_route_[route_count_ - 1].x);
      SetYPosition(nearest_route_[route_count_ - 1].y);
      if (route_count_ - 1 > 0) {
        route_count_ -= static_cast<int>(change_amount_);
        //一歩移動したら、待ち時間の状態に遷移する
        bear_type_ = kWait;
      }
      else {
        bear_type_ = kStopInDeadEnd;
      }
    }
    else if (bear_type_ == kWait) {
      damage_accumulation_time_ = damage_accumulation_time_ + time;
      if (damage_accumulation_time_ >= kLimitTime) {
        //累積時間をリセットする
        damage_accumulation_time_ = 0.0f;
        //走っている状態に遷移する
        bear_type_ = kRunning;
      }
    }
    else if (bear_type_ == kStopInDeadEnd) {
      //X位置を取得する
      int x_coordinate = GetXPosition();
      //Y位置を取得する
      int y_coordinate = GetYPosition();

      //アヒルさんと同じ位置になったら、笑顔の状態にする
      if (duck_now_x_ == x_coordinate && duck_now_y_ == y_coordinate) {
        bear_type_ = kSmile;
      }
    }
    else if (bear_type_ == kSmile) {
      smile_accumulation_time_ = smile_accumulation_time_ + time;
      if (smile_accumulation_time_ >= kLimitTime) {
        //累積時間をリセットする
        smile_accumulation_time_ = 0.0f;
        //歩いている状態に遷移する
        bear_type_ = kWalking;
      }
    }

    Character::UpdateFrame(time);
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void Bear::RenderFrame() {
  //DEBUG_PRINT(Bearの毎フレーム描画処理);
  if (now_phase_ == kPlaying || now_phase_ == kStop) {
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

    //歩いている状態あるいはハチに刺された直後の状態の場合
    if (bear_type_ == kWalking || bear_type_ == kAttacked) {
      if (accumulation_time_ < kWalkFirst) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartBearX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartBearY, bear_handle_[kFirstElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkFirst && accumulation_time_ < kWalkSecond) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartBearX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartBearY, bear_handle_[kSecondElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkSecond && accumulation_time_ < kWalkThird) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartBearX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartBearY, bear_handle_[kThirdElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkThird && accumulation_time_ < kLimitTime) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartBearX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartBearY, bear_handle_[kSecondElement], TRUE);
      }
    }
    //笑顔の状態の場合
    else if (bear_type_ == kSmile) {
      DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartBearX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartBearY, smile_bear_handle_, TRUE);
    }
    //走っている状態と待機時間の状態と行き止まりに居る状態の場合
    else if (bear_type_ == kRunning || bear_type_ == kWait || bear_type_ == kStopInDeadEnd) {
      if (accumulation_time_ < kWalkFirst) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartDamagePlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartDamagePlayerY, damage_bear_handle_[kFirstElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkFirst && accumulation_time_ < kWalkSecond) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartDamagePlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartDamagePlayerY, damage_bear_handle_[kSecondElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkSecond && accumulation_time_ < kWalkThird) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartDamagePlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartDamagePlayerY, damage_bear_handle_[kThirdElement], TRUE);
      }
      else if (accumulation_time_ >= kWalkThird && accumulation_time_ < kLimitTime) {
        DrawGraph(map_left_x + static_cast<int>(display_x_coordinate * kRenderBearX) + kStartDamagePlayerX, map_left_y + static_cast<int>(display_y_coordinate * kRenderBearY) + kStartDamagePlayerY, damage_bear_handle_[kSecondElement], TRUE);
      }
    }

    //ハチとぶつかった位置の表示位置を取得する
    int bear_hit_display_x = GetBearHitXPos() * width;
    int bear_hit_display_y = GetBearHitYPos() * height;
    //現在の表示位置とぶつかった位置の表示位置の差の絶対値を求める
    float bear_difference_display_x = abs(display_x_coordinate - bear_hit_display_x);
    float bear_difference_display_y = abs(display_y_coordinate - bear_hit_display_y);

    //現在の表示位置とぶつかった位置の表示位置の差の絶対値が1以下なら、ハチとぶつかった後の最後の描画が終わったことにする
    if (bear_difference_display_x <= 1 && bear_difference_display_y <= 1) {
      //SetBearIsAttacked(true);
      //DEBUG_PRINT(ハチがクマとぶつかった);
    }
  }
}

/// <summary>
/// GetBearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Bear::GetBearGrHandle(int element_num) {
  return bear_handle_[element_num];
}

/// <summary>
/// SetBearGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Bear::SetBearGrHandle(int bear_handle) {
  //bear_handle_ = bear_handle;
}

/// <summary>
/// GetDamageBearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Bear::GetDamageBearGrHandle(int element_num) {
  return damage_bear_handle_[element_num];
}

/// <summary>
/// GetSmileBearHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>笑顔のクマのグラフィックハンドル</returns>
int Bear::GetSmileBearHandle() {
  return smile_bear_handle_;
}

/// <summary>
/// SetSmileBearHandle関数の定義
/// </summary>
/// <param = "smile_bear_handle">笑顔のクマのグラフィックハンドル</param>
/// <returns>なし</returns>
void Bear::SetSmileBearHandle(int smile_bear_handle) {
  smile_bear_handle_ = smile_bear_handle;
}

/// <summary>
/// SetDuckXPos関数の定義
/// </summary>
/// <param = "duck_x">アヒルさんがいたX位置</param>
/// <returns>なし</returns>
void Bear::SetDuckXPos(int duck_x) {
  duck_x_ = duck_x;
}

/// <summary>
/// SetDuckYPos関数の定義
/// </summary>
/// <param = "duck_y">アヒルさんがいたY位置</param>
/// <returns>なし</returns>
void Bear::SetDuckYPos(int duck_y) {
  duck_y_ = duck_y;
}

/// <summary>
/// SetNowDuckXPos関数の定義
/// </summary>
/// <param = "duck_x">アヒルさんの現在のX位置</param>
/// <returns>なし</returns>
void Bear::SetNowDuckXPos(int duck_x) {
  duck_now_x_ = duck_x;
}

/// <summary>
/// SetNowDuckYPos関数の定義
/// </summary>
/// <param = "duck_y">アヒルさんの現在のY位置</param>
/// <returns>なし</returns>
void Bear::SetNowDuckYPos(int duck_y) {
  duck_now_y_ = duck_y;
}

/// <summary>
/// 一番近い行き止まりの経路を設定する関数
/// </summary>
/// <param = "walk_distances">一番近い行き止まりの経路の配列</param>
/// <returns>なし</returns>
void Bear::SetNearestRoute(Field::Pos* nearest_route, int route_count) {
  //一番近い行き止まりまでの経路と、かかる歩数を設定する
  nearest_route_ = nearest_route;
  route_count_ = route_count;
}

/// <summary>
/// SetBearType関数の定義
/// </summary>
/// <param>現在のステータス</param>
/// <returns>なし</returns>
void Bear::SetBearType(BearType status) {
  bear_type_ = status;
}

/// <summary>
/// GetBearType関数の定義
/// </summary>
/// <param>現在のステータス</param>
/// <returns>なし</returns>
Bear::BearType Bear::GetBearType() {
  return bear_type_;
}