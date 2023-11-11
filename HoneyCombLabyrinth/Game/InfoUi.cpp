#include <iostream>
#include "Game/InfoUi.h"
#include "Game/GameInfo.h"
#include "Game/GameMode.h"
#include "System/LogConsole.h"
#include <DxLib.h>
#include <string>

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const int kLimitTime = 31;

  /// <summary>
  /// 表示する制限時間を定数kDisplayLimitTimeに格納する
  /// </summary>
  static const int kDisplayLimitTime = 30;

  /// <summary>
  /// 白色の値を取得
  /// </summary>
  unsigned int Cr = GetColor(255, 255, 255);

  /// <summary>
  //カウントダウンの表示開始位置を調整する定数kCountdownX
  /// <summary>
  static const int kCountdownX = -17;

  /// <summary>
  //10秒前カウントダウンの表示開始位置を調整する定数kTenCountdownX
  /// <summary>
  static const int kTenCountdownX = -30;

  /// <summary>
  //10秒前カウントダウンの表示開始位置を調整する定数kTenCountdownY
  /// <summary>
  static const int kTenCountdownY = 235;

  /// <summary>
  //カウントダウンの表示開始位置を調整する定数kCountdownY
  /// <summary>
  static const int kCountdownY = -260;

  /// <summary>
  /// リセット時間を定数kResetTimeに格納する
  /// </summary>
  static const float kResetTime = 4.0f;

  /// <summary>
  /// 配列の2つ目の要素に切り替える時間を定数kTimeFirstに格納する
  /// </summary>
  static const float kTimeFirst = 1.0f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kTimeSecondに格納する
  /// </summary>
  static const float kTimeSecond = 2.0f;

  /// <summary>
  /// 配列の4つ目の要素に切り替える時間を定数kTimeThirdに格納する
  /// </summary>
  static const float kTimeThird = 3.0f;

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
  /// クマが止まり始めた時間からの累積時間の制限時間を定数kStopWaitTimeに格納する
  /// </summary>
  static const float kStopWaitTime = 1.0f;

  /// <summary>
  /// 待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  /// 描画ブレンドモードのパラメータを定数kBlendValueに格納する
  /// </summary>
  static const int kBlendValue = 100;

  /// <summary>
  /// カウント10を表す定数kCountTen
  /// </summary>
  static const int kCountTen = 10;

  /// <summary>
  /// カウント5を表す定数kCountFive
  /// </summary>
  static const int kCountFive = 5;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 10;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
InfoUi::InfoUi(TaskId task_id, std::array<int, kElementNumber> countdown_handle, std::array<int, kTimeUpElementNumber> timeup_handle, std::array<int, kElementNumber> ten_countdown_handle, std::array<int, kThreeElementNumber> three_countdown_handle)
  : Task(task_id)
  , countdown_gr_handle_(countdown_handle)
  , timeup_gr_handle_(timeup_handle)
  , ten_countdown_gr_handle_(ten_countdown_handle)
  , three_countdown_gr_handle_(three_countdown_handle)
  , countdown_(kLimitTime)
  , accumulation_time_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , last_render_(false)
  , timeup_end_(false)
{
  DEBUG_PRINT(InfoUiのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
InfoUi::~InfoUi() {
  DEBUG_PRINT(InfoUiのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void InfoUi::UpdateFrame(float time) {
  //DEBUG_PRINT(Playerの毎フレーム更新処理);

}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void InfoUi::RenderFrame() {
  //DEBUG_PRINT(InfoUiの毎フレーム描画処理);

    //ゲーム情報を取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //位置を取得する
    int left_x = game_info->GetCenterX();
    int left_y = game_info->GetCenterY();
    int y_resolution = game_info->GetResolutionYSize();

    //カウントダウンから各桁の値を取得する
    int countdown_two_digit = (countdown_ / kCountTen) % kCountTen;
    int countdown_one_digit = (countdown_ / 1) % kCountTen;

    //グラフィックハンドルの幅と高さを格納する変数を用意する
    int x_size = 0, y_size = 0;

    if (countdown_ > kCountTen && countdown_ < kLimitTime) {
      //カウントダウンを描画する
      GetGraphSize(countdown_gr_handle_[countdown_two_digit], &x_size, &y_size);
      DrawGraph(left_x - (x_size / 2) + kCountdownX, left_y - (y_size / 2) + kCountdownY, countdown_gr_handle_[countdown_two_digit], true);
      GetGraphSize(countdown_gr_handle_[countdown_one_digit], &x_size, &y_size);
      DrawGraph(left_x + (x_size / 2) + kCountdownX, left_y - (y_size / 2) + kCountdownY, countdown_gr_handle_[countdown_one_digit], true);
    }

    //カウントダウンが10以下になった場合
    if (countdown_ > 0 && countdown_ <= kCountTen) {
      GetGraphSize(ten_countdown_gr_handle_[countdown_two_digit], &x_size, &y_size);
      DrawGraph(left_x - (x_size / 2) + kTenCountdownX, left_y - (y_size / 2) + kCountdownY, ten_countdown_gr_handle_[countdown_two_digit], true);
      GetGraphSize(ten_countdown_gr_handle_[countdown_one_digit], &x_size, &y_size);
      DrawGraph(left_x + (x_size / 2) + kTenCountdownX, left_y - (y_size / 2) + kCountdownY, ten_countdown_gr_handle_[countdown_one_digit], true);
    }

    //DEBUG_PRINT_VAR(countdown_);
    if (countdown_ <= 0) {
      SetLastRender();
    }
}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetGrHandle(int element_num) {
  return countdown_gr_handle_[element_num];
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void InfoUi::SetGrHandle(int gr_handle) {
  //gr_handle_ = gr_handle;
}

/// <summary>
/// GetTimeUpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int InfoUi::GetTimeUpGrHandle(int element_num) {
  return timeup_gr_handle_[element_num];
}

/// <summary>
/// GetTenGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>10秒前カウントダウングラフィックハンドル</returns>
int InfoUi::GetTenGrHandle(int element_num) {
  return ten_countdown_gr_handle_[element_num];
}

/// <summary>
/// GetThreeGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>3秒前カウントダウングラフィックハンドル</returns>
int InfoUi::GetThreeGrHandle(int element_num) {
  return three_countdown_gr_handle_[element_num];
}

/// <summary>
/// SetCountdown関数の定義
/// </summary>
/// <param = "countdown">カウントダウンの値</param>
/// <returns>なし</returns>
void InfoUi::SetCountdown(int countdown) {
  countdown_ = countdown;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void InfoUi::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int InfoUi::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void InfoUi::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int InfoUi::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void InfoUi::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float InfoUi::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void InfoUi::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float InfoUi::GetHalfHeight() {
  return half_height_;
}

/// タイムアップを描画する
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void InfoUi::RenderTimeUp() {
  DrawGraph(0, 0, timeup_gr_handle_[kFourthElement], TRUE);
  FadeIn(0, 0, timeup_gr_handle_[kFourthElement], TRUE, kFadeValue);
  timeup_end_ = true;
}

/// <summary>
/// GetLastRender関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>最後の描画が終わったかの有無</returns>
bool InfoUi::GetLastRender() {
  if (last_render_ == true) {
    return true;
  }
  return false;
}

/// <summary>
/// SetLastRender関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void InfoUi::SetLastRender() {
  last_render_ = true;
}

/// <summary>
/// GetTimeUpRenderEnd関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>タイムアップのアニメーションが終わったかの有無</returns>
bool InfoUi::GetTimeUpRenderEnd() {
  if (timeup_end_ == true) {
    return true;
  }
  return false;
}

/// フェードイン表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void InfoUi::FadeIn(int x, int y, int handle, bool is_transparent, int fade_value) {

  DEBUG_PRINT(フェードイン開始);

  //アルファ値を少しずつ変化させて画像を表示する
  for (int alpha = 0; alpha <= fade_value; alpha += kPlusAlpha) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawGraph(x, y, handle, is_transparent);

    //アルファ値の変化に待ち時間を設ける
    WaitTimer(kWaitTime);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}