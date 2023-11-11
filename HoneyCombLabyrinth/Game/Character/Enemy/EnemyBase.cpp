#include <iostream>
#include "Game/Character/Enemy/EnemyBase.h"
#include "Game/Level/BattleLevel.h"
#include "System/LogConsole.h"
#include "System/Interface/CharacterControllerEventInterface.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 敵の描画開始X位置を定数kStartEnemyXに格納する
  /// </summary>
  static const int kStartEnemyX = -45;

  /// <summary>
  /// 敵の描画開始Y位置を定数kStartEnemyYに格納する
  /// </summary>
  static const int kStartEnemyY = 0;

  /// <summary>
  /// 敵の描画Y位置を調整するためにdisplay_y_coordinateと掛ける値を定数kRenderEnemyYに格納する
  /// </summary>
  static const float kRenderEnemyY = 1.7f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
EnemyBase::EnemyBase(TaskId task_id, TaskManager* task_manager, CharacterControllerEventInterface& controller_event_interface, EnemyEventInterface& enemy_event_interface, CharacterEventInterface& event_interface)
  : Character(task_id, task_manager, event_interface)
  , enemy_gr_handle_(0)
  , change_amount_(1)
  , enemy_controller_(controller_event_interface, *this)
  , event_interface_(enemy_event_interface)
{
  DEBUG_PRINT(EnemyBaseのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
EnemyBase::~EnemyBase() {
  DEBUG_PRINT(EnemyBaseのデストラクタ);
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void EnemyBase::RenderFrame() {
  //DEBUG_PRINT(EnemyBaseの毎フレーム描画処理);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  if (now_phase_ == kPlaying || now_phase_ == kStop) {
    //X位置を取得する
  int x_coordinate = GetXPosition();
  //DEBUG_PRINT_VAR(x_coordinate);

  //Y位置を取得する
  int y_coordinate = GetYPosition();
  //DEBUG_PRINT_VAR(y_coordinate);

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

  //ゲーム情報からマップの左上の座標を取得する
  int map_left_x = game_info->GetMapLeftX();
  int map_left_y = game_info->GetMapLeftY();

  DrawGraph(map_left_x + static_cast<int>(display_x_coordinate) + kStartEnemyX, map_left_y + static_cast<int>(display_y_coordinate * kRenderEnemyY) + kStartEnemyY, enemy_gr_handle_, TRUE);

  //プレイヤーとぶつかった位置の表示位置を取得する
  int hit_display_x = GetHitXPos() * width;
  int hit_display_y = GetHitYPos() * height;
  //現在の表示位置とぶつかった位置の表示位置の差の絶対値を求める
  float difference_display_x = abs(display_x_coordinate - hit_display_x);
  //DEBUG_PRINT_VAR(difference_display_x);
  float difference_display_y = abs(display_y_coordinate - hit_display_y);
  //DEBUG_PRINT_VAR(difference_display_y);

  //現在の表示位置とぶつかった位置の表示位置の差の絶対値が1以下なら、プレイヤーとぶつかった後の最後の描画が終わったことにする
  if (difference_display_x <= 1 && difference_display_y <= 1) {
    SetPlayerIsDead();
    //DEBUG_PRINT(ハチの最後の描画が終わった);
  }

  //クマとぶつかった位置の表示位置を取得する
  int bear_hit_display_x = GetBearHitXPos() * width;
  int bear_hit_display_y = GetBearHitYPos() * height;
  //現在の表示位置とぶつかった位置の表示位置の差の絶対値を求める
  float bear_difference_display_x = abs(display_x_coordinate - bear_hit_display_x);
  float bear_difference_display_y = abs(display_y_coordinate - bear_hit_display_y);

  //現在の表示位置とぶつかった位置の表示位置の差の絶対値が1以下なら、クマとぶつかった後の最後の描画が終わったことにする
  if (bear_difference_display_x <= 1 && bear_difference_display_y <= 1) {
    //SetBearIsAttacked(true);
    //DEBUG_PRINT(ハチがクマとぶつかった);
  }
  }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int EnemyBase::GetGrHandle() {
  return enemy_gr_handle_;
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void EnemyBase::SetGrHandle(int gr_handle) {
  enemy_gr_handle_ = gr_handle;
}

/// <summary>
/// 敵キャラクターイベントインターフェースを設定する関数
/// </summary>
/// <param = "event_interface">敵キャラクターイベントインターフェース</param>
/// <returns>なし</returns>
void EnemyBase::SetEnemyEventInterface(EnemyEventInterface& event_interface) {
  event_interface_ = event_interface;
}

/// <summary>
/// 歩ける範囲を設定する関数
/// </summary>
/// <param = "walk_distances">歩ける範囲のリスト</param>
/// <returns>なし</returns>
void EnemyBase::SetWalkDistance(std::vector<Field::DirectionType> walk_distances) {
  walk_distances_ = walk_distances;
}
