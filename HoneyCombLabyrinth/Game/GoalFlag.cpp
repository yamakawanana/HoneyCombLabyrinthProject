#include <iostream>
#include "Game/GoalFlag.h"
#include "System/LogConsole.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.8f;

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
  /// 配列の2つ目の要素に切り替える時間を定数kTimeFirstに格納する
  /// </summary>
  static const float kTimeFirst = 0.2f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kTimeSecondに格納する
  /// </summary>
  static const float kTimeSecond = 0.4f;

  /// <summary>
  /// 配列の4つ目の要素に切り替える時間を定数kTimeThirdに格納する
  /// </summary>
  static const float kTimeThird = 0.6f;

  /// <summary>
  /// ゴール旗の描画開始X位置を定数kGoalXに格納する
  /// </summary>
  static const int kGoalX = 600;

  /// <summary>
  /// ゴール旗の描画開始Y位置を定数kGoalYに格納する
  /// </summary>
  static const int kGoalY = 380;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GoalFlag::GoalFlag(TaskId task_id, std::array<int, kGoalElementNumber> goal_handle)
  : Task(task_id)
  , goal_handle_(goal_handle)
  , x_coordinate_(0)
  , y_coordinate_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , now_phase_(kProcessing)
{
  DEBUG_PRINT(GoalFlagのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GoalFlag::~GoalFlag() {
  DEBUG_PRINT(GoalFlagのデストラクタ);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void GoalFlag::InitGoalFlag(int gr_handle) {
  DEBUG_PRINT(GoalFlagクラスの初期化処理);
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void GoalFlag::UpdateFrame(float time) {
  //DEBUG_PRINT(GoalFlagクラスの毎フレーム更新処理);

  if (now_phase_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kLimitTime) {
      accumulation_time_ = 0.0f;
    }
  }

}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void GoalFlag::RenderFrame() {
  //ゴールの旗を描画する
  if (accumulation_time_ < kTimeFirst) {
    DrawGraph(kGoalX, kGoalY, goal_handle_[kFirstElement], TRUE);
  }
  else if (accumulation_time_ >= kTimeFirst && accumulation_time_ < kTimeSecond) {
    DrawGraph(kGoalX, kGoalY, goal_handle_[kSecondElement], TRUE);
  }
  else if (accumulation_time_ >= kTimeSecond && accumulation_time_ < kTimeThird) {
    DrawGraph(kGoalX, kGoalY, goal_handle_[kThirdElement], TRUE);
  }
  else if (accumulation_time_ >= kTimeThird && accumulation_time_ < kLimitTime) {
    DrawGraph(kGoalX, kGoalY, goal_handle_[kFourthElement], TRUE);
  }
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param="x_coordinate">X座標</param>
/// <returns>なし</returns>
void GoalFlag::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int GoalFlag::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param="y_coordinate">Y座標</param>
/// <returns>なし</returns>
void GoalFlag::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int GoalFlag::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int GoalFlag::GetWidth() {
  return width_;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int GoalFlag::GetHeight() {
  return height_;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float GoalFlag::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float GoalFlag::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// GetGoalGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int GoalFlag::GetGoalGrHandle(int element_num) {
  return goal_handle_[element_num];
}

/// <summary>
/// SetGoalGrHandle関数の定義
/// </summary>
/// <param = "goal_handle">ゴール旗のグラフィックハンドル</param>
/// <returns>なし</returns>
void GoalFlag::SetGoalGrHandle(int goal_handle) {
  //goal_handle_ = goal_handle;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void GoalFlag::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
GoalFlag::PhaseType GoalFlag::GetPhaseType() {
  return now_phase_;
}