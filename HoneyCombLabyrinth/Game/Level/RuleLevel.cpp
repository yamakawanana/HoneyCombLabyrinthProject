#include <iostream>
#include <chrono>
#include <thread>
#include "Game/Level/RuleLevel.h"
#include "System/Controller/MenuController.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

  /// <summary>
  /// 三角形の画像を動かすタイミングを定数kMoveTriangleに格納する
  /// </summary>
  static const float kMoveTriangle = 0.5f;

  /// <summary>
  //三角形の画像のX位置を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 380;

  /// <summary>
  //三角形の画像のY位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 495;

  /// <summary>
  //三角形の画像を下にずらした時のY位置を定数kSecondYcoordinateに格納する
  /// <summary>
  static const int kSecondYcoordinate = 500;

  /// <summary>
  /// ルール説明の画像の横向きの分割数を定数kRuleXに格納する
  /// </summary>
  static const int kRuleX = 4;

  /// <summary>
  /// ルール説明の画像の縦向きの分割数を定数kRuleYに格納する
  /// </summary>
  static const int kRuleY = 1;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

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
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 10;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 30;

  /// <summary>
  /// ルール説明画面の背景画像のファイル名を定数kRulePngに格納する
  /// </summary>
  static const char* kRulePng = "Assets/rule.png";

  /// <summary>
  /// 三角形の画像のファイル名を定数kTrianglePngに格納する
  /// </summary>
  static const char* kTrianglePng = "Assets/triangle.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/No.0141.mp3";

  /// <summary>
  /// 次のレベルに遷移する効果音のサウンドファイル名を定数kNextLevelMp3に格納する
  /// </summary>
  static const char* kNextLevelMp3 = "Assets/Enter26.mp3";

  /// <summary>
  /// ルール説明の次のページに遷移する効果音のサウンドファイル名を定数kNextPageMp3に格納する
  /// </summary>
  static const char* kNextPageMp3 = "Assets/Enter2.mp3";
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
RuleLevel::RuleLevel()
{
  DEBUG_PRINT(RuleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
RuleLevel::RuleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , menu_controller_(nullptr)
  , end_type_(kUnloadTask)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , phase_type_(kFirst)
{
  DEBUG_PRINT(RuleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
RuleLevel::~RuleLevel() {
  DEBUG_PRINT(RuleLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RuleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);

  switch (phase_type_) {

  case kFirst:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kSecond;
    break;

  case kSecond:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kThird;
    break;

  case kThird:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kFourth;
    break;

  case kFourth:
    phase_type_ = kFadeOut;
    break;
  }

}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RuleLevel::OnPushFinish() {
  DEBUG_PRINT(Escキーが押された時のイベント);
  phase_type_ = kFadeOut;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RuleLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RuleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);

  switch (phase_type_) {

  case kSecond:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kFirst;
    break;

  case kThird:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kSecond;
    break;

  case kFourth:
    PlaySoundMem(next_page_handle_, DX_PLAYTYPE_BACK);
    phase_type_ = kThird;
    break;
  }

}

/// <summary>
/// SetRuleGrHandle関数の定義
/// </summary>
/// <param = "rule_handle">Ruleのグラフィックハンドル</param>
/// <returns>なし</returns>
void RuleLevel::SetRuleGrHandle(std::array<int, kRuleElementNumber> rule_handle) {
  rule_handle_ = rule_handle;
}

/// <summary>
/// GetRuleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Ruleのグラフィックハンドル</returns>
int RuleLevel::GetRuleGrHandle(int element_num) {
  return rule_handle_[element_num];
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void RuleLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int RuleLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void RuleLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int RuleLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void RuleLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// SetTriangleGrHandle関数の定義
/// </summary>
/// <param = "triangle_handle">三角形の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void RuleLevel::SetTriangleGrHandle(int triangle_handle) {
  triangle_handle_ = triangle_handle;
}

/// <summary>
/// GetTriangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>三角形の画像のグラフィックハンドル</returns>
int RuleLevel::GetTriangleGrHandle() {
  return triangle_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void RuleLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int RuleLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetNextPageSoundHandle関数の定義
/// </summary>
/// <param = "next_page_handle">ルール説明の次のページに遷移する時のサウンドハンドル</param>
/// <returns>なし</returns>
void RuleLevel::SetNextPageSoundHandle(int next_page_handle) {
  next_page_handle_ = next_page_handle;
}

/// <summary>
/// GetNextPageSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ルール説明の次のページに遷移する時のサウンドハンドル</returns>
int RuleLevel::GetNextPageSoundHandle() {
  return next_page_handle_;
}

/// <summary>
/// SetNextLevelSoundHandle関数の定義
/// </summary>
/// <param = "next_level_handle">次のレベルに遷移する時のサウンドハンドル</param>
/// <returns>なし</returns>
void RuleLevel::SetNextLevelSoundHandle(int next_level_handle) {
  next_level_handle_ = next_level_handle;
}

/// <summary>
/// GetNextLevelSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>次のレベルに遷移する時のサウンドハンドル</returns>
int RuleLevel::GetNextLevelSoundHandle() {
  return next_level_handle_;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float RuleLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void RuleLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float RuleLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool RuleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(RuleLevelの初期化処理);
  //メニューコントローラーを生成する
  menu_controller_ = new MenuController(Task::kMenuController, *this);
  //生成したメニューコントローラーを、タスクマネージャーに積む
  task_manager_->AddTask(menu_controller_);

  //画像データをロードする
  std::array<int, kRuleElementNumber> rule_handle;
  int rule_gr_handle = LoadDivGraph(kRulePng, kRuleElementNumber, kRuleX, kRuleY, kScreenSizeX, kScreenSizeY, &rule_handle[0]);
  int triangle_handle = LoadGraph(kTrianglePng);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int next_level_handle = LoadSoundMem(kNextLevelMp3);
  int next_page_handle = LoadSoundMem(kNextPageMp3);

  //グラフィックハンドルを設定する
  SetRuleGrHandle(rule_handle);
  //三角形の画像のグラフィックハンドルを設定する
  SetTriangleGrHandle(triangle_handle);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetNextPageSoundHandle(next_page_handle);
  SetNextLevelSoundHandle(next_level_handle);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool RuleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(RuleLevelの毎フレーム更新処理のフェーズ処理);

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
  }

  //×ボタンが押された場合
  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
  }

  //描画処理を実行する
  ProcessingRender();

  //各ボタンを押された時のイベントでis_finish_がtrueになった時、処理終了する
  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void RuleLevel::ProcessingRender() {
  //ルール説明画像を描画する
  if (phase_type_ == kFirst) {
    DrawGraph(0, 0, rule_handle_[kFirstElement], TRUE);
  }
  else if (phase_type_ == kSecond) {
    ClearDrawScreen();
    DrawGraph(0, 0, rule_handle_[kSecondElement], TRUE);
  }
  else if (phase_type_ ==  kThird) {
    ClearDrawScreen();
    DrawGraph(0, 0, rule_handle_[kThirdElement], TRUE);
  }
  else if (phase_type_ == kFourth) {
    ClearDrawScreen();
    DrawGraph(0, 0, rule_handle_[kFourthElement], TRUE);
  }
  else if (phase_type_ == kFadeOut) {
    PlaySoundMem(next_level_handle_, DX_PLAYTYPE_BACK);
    FadeOut();
  }

  //三角形の画像を描画する
  if (accumulation_time_ < kMoveTriangle) {
    DrawGraph(kXcoordinate, kYcoordinate, triangle_handle_, TRUE);
  }
  else if (accumulation_time_ >= kMoveTriangle && accumulation_time_ < kLimitTime) {
    DrawGraph(kXcoordinate, kSecondYcoordinate, triangle_handle_, TRUE);
  }

}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool RuleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(RuleLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  for (int i = 0; i < kRuleElementNumber; ++i) {
    int info = DeleteGraph(GetRuleGrHandle(i));
  }
  int triangle_handle = DeleteGraph(GetTriangleGrHandle());

  //サウンドのリソースを破棄する
  int bgm_handle = DeleteSoundMem(GetBgmHandle());
  int next_page_handle = DeleteSoundMem(GetNextPageSoundHandle());
  int next_level_handle = DeleteSoundMem(GetNextLevelSoundHandle());

  if (end_type_ == kUnloadTask) {
    //タスクマネージャーに積んでいたメニューコントローラータスクを解放するためにrelease_taskに格納する
    Task* release_task = task_manager_->UnloadTask(kMenuController);

    //release_taskのメモリを解放する
    delete release_task;

    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {
    //メニューコントローラーを破棄する
    delete menu_controller_;
    menu_controller_ = nullptr;
  }
  return true;
}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void RuleLevel::FadeOut() {

  //DEBUG_PRINT(フェードアウト開始);

  //アルファ値を少しずつ変化させて表示する
  for (int alpha = 0; alpha <= kFadeValue; alpha += kPlusAlpha) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, kScreenSizeX, kScreenSizeY, Cr, TRUE);

    if (alpha >= kFadeValue) {
      is_finish_ = true;
    }

    //DEBUG_PRINT_VAR(alpha);

    //アルファ値の変化に待ち時間を設ける
    WaitTimer(kWaitTime);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}