#include <iostream>
#include "Game/Level/ResultLevel.h"
#include "Game/GameInfo.h"
#include <DxLib.h>
#include <string>

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
  //ゲームオーバーの場合に文字を表示するX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 20;

  /// <summary>
  //ゲームオーバーの場合に文字を表示するY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 480;

  /// <summary>
  //ゲームクリアの場合に文字を表示するX座標を定数kPushMessageXcoordinateに格納する
  /// <summary>
  static const int kClearXcoordinate = 200;

  /// <summary>
  //ゲームクリアの場合に文字を表示するY座標を定数kPushMessageYcoordinateに格納する
  /// <summary>
  static const int kClearYcoordinate = 250;

  /// <summary>
  /// 文字表示の画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

  /// <summary>
  /// クリアした場合のリザルト画面の背景画像のファイル名を定数kClearResultPngに格納する
  /// </summary>
  static const char* kClearResultPng = "Assets/Images/gameclear_result.png";

  /// <summary>
  /// ゲームオーバーした場合のリザルト画面の背景画像のファイル名を定数kGameOverResultPngに格納する
  /// </summary>
  static const char* kGameOverResultPng = "Assets/Images/gameover_result.png";

  /// <summary>
  /// 「[Enter]タイトル画面に戻る」の画像のファイル名を定数kPushEnterPngに格納する
  /// </summary>
  static const char* kPushEnterPng = "Assets/Images/backtitle_black.png";

  /// <summary>
  /// ゲームクリア時のリザルト画面BGMのサウンドファイル名を定数kClearBgmMp3に格納する
  /// </summary>
  static const char* kClearBgmMp3 = "Assets/Sounds/Ein_Prosit.mp3";

  /// <summary>
  /// ゲームオーバー時のリザルト画面BGMのサウンドファイル名を定数kGameOverBgmMp3に格納する
  /// </summary>
  static const char* kGameOverBgmMp3 = "Assets/Sounds/PerituneMaterial_Koi_Wazurai.mp3";

  /// <summary>
  /// Enterを押した時の音のサウンドファイル名を定数kEnterMp3に格納する
  /// </summary>
  static const char* kEnterMp3 = "Assets/Sounds/Enter26.mp3";

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
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel()
{
  DEBUG_PRINT(ResultLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , menu_controller_(nullptr)
  , end_type_(kUnloadTask)
{
  DEBUG_PRINT(ResultLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::~ResultLevel() {
  DEBUG_PRINT(ResultLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  PlaySoundMem(enter_handle_, DX_PLAYTYPE_BACK);
  FadeOut();
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(ResultLevelの初期化処理);
  //メニューコントローラーを生成する
  menu_controller_ = new MenuController(Task::kMenuController);
  //生成したメニューコントローラーを、タスクマネージャーに積む
  task_manager_->AddTask(menu_controller_);

  //ゲーム情報を取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲームクリアの有無を取得する
  bool is_clear = game_info->GetIsGameClear();

  //サウンドハンドルを格納するための変数を用意する
  int bgm_handle = 0;

  //ゲームクリアした場合
  if (is_clear) {
    //サウンドデータをロードする
    bgm_handle = LoadSoundMem(kClearBgmMp3);
  }
  else {
    bgm_handle = LoadSoundMem(kGameOverBgmMp3);
  }

  //Enterを押した時の効果音のサウンドハンドルを取得する
  int enter_handle = LoadSoundMem(kEnterMp3);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetEnterSoundHandle(enter_handle);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(ResultLevelの毎フレーム更新処理のフェーズ処理);
  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
    is_finish_ = true;
  }

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }

  //描画処理を実行する
  ProcessingRender();

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ResultLevel::ProcessingRender() {
  //DEBUG_PRINT(ResultLevelの描画処理);

  //ゲーム情報を取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲームクリアの有無を取得する
  bool is_clear = game_info->GetIsGameClear();

  //ゲームクリアした場合
  if (is_clear) {
    //リザルト画面の画像データをロードする
    int result_handle = LoadGraph(kClearResultPng);

    //文字表示の画像データをロードする
    int push_enter_handle = LoadGraph(kPushEnterPng);

    //グラフィックハンドルを設定する
    SetResultGrHandle(result_handle);
    SetPushEnterGrHandle(push_enter_handle);

    //リザルト画面を表示する
    DrawGraph(0, 0, result_handle_, TRUE);

    //文字表示の画像を点滅させて表示する
    if (accumulation_time_ < kFlashBubble) {
      DrawGraph(kClearXcoordinate, kClearYcoordinate, push_enter_handle_, TRUE);
    } 
  }
  //ゲームオーバーの場合
  else {
    //リザルト画面の画像データをロードする
    int result_handle = LoadGraph(kGameOverResultPng);

    //文字表示の画像データをロードする
    int push_enter_handle = LoadGraph(kPushEnterPng);

    //グラフィックハンドルを設定する
    SetResultGrHandle(result_handle);
    SetPushEnterGrHandle(push_enter_handle);

    //リザルト画面を表示する
    DrawGraph(0, 0, result_handle_, TRUE);

    //文字表示の画像を点滅させて表示する
    if (accumulation_time_ < kFlashBubble) {
      DrawGraph(kXcoordinate, kYcoordinate, push_enter_handle_, TRUE);
    }
  }
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(ResultLevelの終了処理);

  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  int result_handle = DeleteGraph(GetResultGrHandle());
  int push_enter_handle = DeleteGraph(GetPushEnterGrHandle());

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
/// SetResultGrHandle関数の定義
/// </summary>
/// <param = "result_handle">Resultのグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetResultGrHandle(int result_handle) {
  result_handle_ = result_handle;
}

/// <summary>
/// GetResultGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Resultのグラフィックハンドル</returns>
int ResultLevel::GetResultGrHandle() {
  return result_handle_;
}

/// <summary>
/// SetPushEnterGrHandle関数の定義
/// </summary>
/// <param = "push_enter_handle">文字表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetPushEnterGrHandle(int push_enter_handle) {
  push_enter_handle_ = push_enter_handle;
}

/// <summary>
/// GetPushEnterGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>文字表示のグラフィックハンドル</returns>
int ResultLevel::GetPushEnterGrHandle() {
  return push_enter_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int ResultLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetEnterSoundHandle関数の定義
/// </summary>
/// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetEnterSoundHandle(int enter_handle) {
  enter_handle_ = enter_handle;
}

/// <summary>
/// GetEnterSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Enterを押した時のサウンドハンドル</returns>
int ResultLevel::GetEnterSoundHandle() {
  return enter_handle_;
}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void ResultLevel::FadeOut() {

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