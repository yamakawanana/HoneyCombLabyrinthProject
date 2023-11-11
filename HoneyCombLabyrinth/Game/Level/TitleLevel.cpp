#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include "Game/Level/TitleLevel.h"
#include "System/Controller/MenuController.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.6f;

  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  //「Enterを押してね」の吹き出しのX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 125;

  /// <summary>
  //「Enterを押してね」の吹き出しのY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 430;

  /// <summary>
  /// 吹き出しの画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

  /// <summary>
  /// キャラクターの画像の横向きの分割数を定数kBearDuckXに格納する
  /// </summary>
  static const int kBearDuckX = 3;

  /// <summary>
  /// キャラクターの画像の縦向きの分割数を定数kBearDuckYに格納する
  /// </summary>
  static const int kBearDuckY = 1;

  // <summary>
  //クマとアヒルの画像の幅と高さを定数kBearDuckSizeに格納する
  /// <summary>
  static const int kBearDuckSize = 40;

  /// <summary>
  /// 配列の2つ目の要素に切り替える時間を定数kWalkFirstに格納する
  /// </summary>
  static const float kWalkFirst = 0.4f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kWalkSecondに格納する
  /// </summary>
  static const float kWalkSecond = 0.8f;

  /// <summary>
  /// 配列の2つ目の要素に戻す時間を定数kWalkThirdに格納する
  /// </summary>
  static const float kWalkThird = 1.2f;

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
  //アヒルのX座標を定数kDuckXcoordinateに格納する
  /// <summary>
  static const int kDuckXcoordinate = 320;

  /// <summary>
  //アヒルのY座標を定数kDuckYcoordinateに格納する
  /// <summary>
  static const int kDuckYcoordinate = 205;

  /// <summary>
  //クマのX座標を定数kBearXcoordinateに格納する
  /// <summary>
  static const int kBearXcoordinate = 440;

  /// <summary>
  //クマのY座標を定数kBearYcoordinateに格納する
  /// <summary>
  static const int kBearYcoordinate = 180;

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

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// タイトル画面の背景画像のファイル名を定数kTitlePngに格納する
  /// </summary>
  static const char* kTitlePng = "Assets/title.png";

  /// <summary>
  /// 「Enterを押してね」の吹き出し画像のファイル名を定数kPushEnterPngに格納する
  /// </summary>
  static const char* kPushEnterPng = "Assets/push_enter.png";

  /// <summary>
  /// アヒルの画像のファイル名を定数kDuckPngに格納する
  /// </summary>
  static const char* kDuckPng = "Assets/standing_duck.png";

  /// <summary>
  /// クマの画像のファイル名を定数kBearPngに格納する
  /// </summary>
  static const char* kBearPng = "Assets/standing_bear.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/maou_bgm_fantasy05.mp3";

  /// <summary>
  /// Enterを押した時の音のサウンドファイル名を定数kEnterMp3に格納する
  /// </summary>
  static const char* kEnterMp3 = "Assets/Enter26.mp3";
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel()
: is_finish_(false)
, accumulation_time_(0.0f)
, menu_controller_(nullptr)
, end_type_(kUnloadTask)
, title_handle_(0)
, width_(0)
, height_(0)
, half_width_(0.0f)
, half_height_(0.0f)
{
  DEBUG_PRINT(TitleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , menu_controller_(nullptr)
  , end_type_(kUnloadTask)
  , title_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
{
  DEBUG_PRINT(TitleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::~TitleLevel() {
  DEBUG_PRINT(TitleLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  PlaySoundMem(enter_handle_, DX_PLAYTYPE_BACK);
  FadeOut();
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// SetTitleGrHandle関数の定義
/// </summary>
/// <param = "title_handle">Titleのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetTitleGrHandle(int title_handle) {
  title_handle_ = title_handle;
}

/// <summary>
/// GetTitleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Titleのグラフィックハンドル</returns>
int TitleLevel::GetTitleGrHandle() {
  return title_handle_;
}

/// <summary>
/// SetPushEnterGrHandle関数の定義
/// </summary>
/// <param = "push_enter_handle">「Enterを押してね」の吹き出しのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetPushEnterGrHandle(int push_enter_handle) {
  push_enter_handle_ = push_enter_handle;
}

/// <summary>
/// GetPushEnterGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>「Enterを押してね」の吹き出しのグラフィックハンドル</returns>
int TitleLevel::GetPushEnterGrHandle() {
  return push_enter_handle_;
}

/// <summary>
/// SetDuckGrHandle関数の定義
/// </summary>
/// <param = "duck_handle">アヒルのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetDuckGrHandle(std::array<int, kDuckElementNumber> duck_handle) {
  standing_duck_handle_ = duck_handle;
}

/// <summary>
/// GetDuckGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルのグラフィックハンドル</returns>
int TitleLevel::GetDuckGrHandle(int element_num) {
  return standing_duck_handle_[element_num];
}

/// <summary>
/// SetBearGrHandle関数の定義
/// </summary>
/// <param = "bear_handle">クマのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetBearGrHandle(std::array<int, kBearElementNumber> bear_handle) {
  standing_bear_handle_ = bear_handle;
}

/// <summary>
/// GetBearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>クマのグラフィックハンドル</returns>
int TitleLevel::GetBearGrHandle(int element_num) {
  return standing_bear_handle_[element_num];
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int TitleLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetEnterSoundHandle関数の定義
/// </summary>
/// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetEnterSoundHandle(int enter_handle) {
  enter_handle_ = enter_handle;
}

/// <summary>
/// GetEnterSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Enterを押した時のサウンドハンドル</returns>
int TitleLevel::GetEnterSoundHandle() {
  return enter_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int TitleLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int TitleLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float TitleLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float TitleLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(TitleLevelの初期化処理);
  //メニューコントローラーを生成する
  menu_controller_ = new MenuController(Task::kMenuController, *this);
  //生成したメニューコントローラーを、タスクマネージャーに積む
  task_manager_->AddTask(menu_controller_);

  //画像データをロードする
  int title_handle = LoadGraph(kTitlePng);
  int push_enter_handle = LoadGraph(kPushEnterPng);
  std::array<int, kDuckElementNumber> standing_duck_handle;
  int standing_duck_gr_handle = LoadDivGraph(kDuckPng, kDuckElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &standing_duck_handle[0]);
  std::array<int, kBearElementNumber> standing_bear_handle;
  int standing_bear_gr_handle = LoadDivGraph(kBearPng, kBearElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &standing_bear_handle[0]);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int enter_handle = LoadSoundMem(kEnterMp3);

  //グラフィックハンドルを設定する
  SetTitleGrHandle(title_handle);
  SetPushEnterGrHandle(push_enter_handle);
  SetDuckGrHandle(standing_duck_handle);
  SetBearGrHandle(standing_bear_handle);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetEnterSoundHandle(enter_handle);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  //ロードした画像の幅を取得して保存するための整数size_xを用意して初期化
  int size_x = 0;
  //ロードした画像の高さを取得して保存するための整数size_yを用意して初期化
  int size_y = 0;

  //ロードしたキャラクターの画像のサイズを取得する
  GetGraphSize(title_handle, &size_x, &size_y);

  DEBUG_PRINT_VAR(size_x);
  DEBUG_PRINT_VAR(size_y);

  //画像の幅を設定する
  SetWidth(size_x);
  //画像の高さを設定する
  SetHeight(size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float>(size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float>(size_y) / 2;

  //画像の幅の半分を設定する
  SetHalfWidth(half_width);
  //画像の高さの半分を設定する
  SetHalfHeight(half_height);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(TitleLevelの毎フレーム更新処理のフェーズ処理);

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
  }

  DEBUG_PRINT_VAR(accumulation_time_);

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
void TitleLevel::ProcessingRender() {
  //DEBUG_PRINT(TitleLevelの描画処理);

  //タイトルを表示する
  DrawGraph(0, 0, title_handle_, TRUE);

  //「Enterを押してね」の吹き出しを点滅させて表示する
  if (accumulation_time_ < kFlashBubble) {
    DrawGraph(kXcoordinate, kYcoordinate, push_enter_handle_, TRUE);
  }
  else if (accumulation_time_ >= kFlashBubble && accumulation_time_ < kLimitTime) {
    //DrawGraph(kXcoordinate, kYcoordinate, push_enter_handle, TRUE);
  }

  //アヒルのアニメーションを表示する
  if (accumulation_time_ < kWalkFirst) {
    DrawGraph(kDuckXcoordinate, kDuckYcoordinate, standing_duck_handle_[kFirstElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkFirst && accumulation_time_ < kWalkSecond) {
    DrawGraph(kDuckXcoordinate, kDuckYcoordinate, standing_duck_handle_[kSecondElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkSecond && accumulation_time_ < kWalkThird) {
    DrawGraph(kDuckXcoordinate, kDuckYcoordinate, standing_duck_handle_[kThirdElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkThird && accumulation_time_ < kLimitTime) {
    DrawGraph(kDuckXcoordinate, kDuckYcoordinate, standing_duck_handle_[kSecondElement], TRUE);
  }

  //クマのアニメーションを表示する
  if (accumulation_time_ < kWalkFirst) {
    DrawGraph(kBearXcoordinate, kBearYcoordinate, standing_bear_handle_[kFirstElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkFirst && accumulation_time_ < kWalkSecond) {
    DrawGraph(kBearXcoordinate, kBearYcoordinate, standing_bear_handle_[kSecondElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkSecond && accumulation_time_ < kWalkThird) {
    DrawGraph(kBearXcoordinate, kBearYcoordinate, standing_bear_handle_[kThirdElement], TRUE);
  }
  else if (accumulation_time_ >= kWalkThird && accumulation_time_ < kLimitTime) {
    DrawGraph(kBearXcoordinate, kBearYcoordinate, standing_bear_handle_[kSecondElement], TRUE);
  }
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(TitleLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  int title_handle = DeleteGraph(GetTitleGrHandle());
  int push_enter_handle = DeleteGraph(GetPushEnterGrHandle());
  for (int i = 0; i < kDuckElementNumber; ++i) {
    int info = DeleteGraph(GetDuckGrHandle(i));
  }
  for (int i = 0; i < kBearElementNumber; ++i) {
    int confetti = DeleteGraph(GetBearGrHandle(i));
  }

  //サウンドのリソースを破棄する
  int bgm_handle = DeleteSoundMem(GetBgmHandle());
  int enter_handle = DeleteSoundMem(GetEnterSoundHandle());

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
void TitleLevel::FadeOut() {

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