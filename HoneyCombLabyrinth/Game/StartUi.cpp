#include <iostream>
#include "Game/StartUi.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// スタートUIを表示終了するまでの時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 4.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StartUi::StartUi(TaskId task_id, UiEventInterface& event_interface)
  : Task(task_id)
  , gr_handle_(0)
  , accumulation_time_(0.0f)
  , now_phase_(kDisplay)
  , event_interface_(event_interface)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
{
  //DEBUG_PRINT(StartUiのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
StartUi::~StartUi() {
  //DEBUG_PRINT(StartUiのデストラクタ);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void StartUi::InitStartUi(int gr_handle) {
  //DEBUG_PRINT(StartUiクラスの初期化処理);
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void StartUi::UpdateFrame(float time) {
  //DEBUG_PRINT(StartUiクラスの毎フレーム更新処理);

  if (now_phase_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;

    //１秒経過したら、UI終了待機フェーズにし、accumulation_time_をリセットする
    if (accumulation_time_ >= kLimitTime) {
      now_phase_ = kFinish;
      accumulation_time_ = 0.0f;
    }
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void StartUi::RenderFrame() {
  //DEBUG_PRINT(Playerの毎フレーム描画処理);

  if (now_phase_ == kDisplay) {
    //ゲーム情報を取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //画面の中心の位置を取得する
    int left_x = game_info->GetCenterX();
    int left_y = game_info->GetCenterY();

    //画面の中心の座標から画像の大きさの半分の長さを引いた位置にロゴを表示する
    DrawGraph(static_cast<int>(left_x - half_width_), static_cast<int>(left_y - half_height_), gr_handle_, TRUE);
  }

}

/// <summary>
/// GetGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int StartUi::GetGrHandle() {
  return gr_handle_;
}

/// <summary>
/// SetGrHandle関数の定義
/// </summary>
/// <param = "gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void StartUi::SetGrHandle(int gr_handle) {
  gr_handle_ = gr_handle;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StartUi::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int StartUi::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void StartUi::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int StartUi::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void StartUi::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float StartUi::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void StartUi::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float StartUi::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void StartUi::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
StartUi::PhaseType StartUi::GetPhaseType() {
  return now_phase_;
}