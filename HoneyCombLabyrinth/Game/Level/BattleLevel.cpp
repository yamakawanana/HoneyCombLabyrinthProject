#include <iostream>
#include "DxLib.h"
#include "Game/Level/BattleLevel.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 120.0f;

  /// <summary>
  /// カウントダウンのグラフィックハンドルの配列の要素数を定数kElementNumberに格納する
  /// </summary>
  static const int kElementNumber = 10;

  /// <summary>
  /// ３秒前カウントダウンのグラフィックハンドルの配列の要素数を定数kThreeElementNumberに格納する
  /// </summary>
  static const int kThreeElementNumber = 3;

  /// <summary>
  /// タイムアップのグラフィックハンドルの配列の要素数を定数kTimeUpElementNumberに格納する
  /// </summary>
  static const int kTimeUpElementNumber = 4;

  /// <summary>
  /// アヒルのグラフィックハンドルの配列の要素数を定数kDuckElementNumberに格納する
  /// </summary>
  static const int kDuckElementNumber = 3;

  /// <summary>
  /// ダメージを受けたアヒルのグラフィックハンドルの配列の要素数を定数kDamageDuckElementNumberに格納する
  /// </summary>
  static const int kDamageDuckElementNumber = 6;

  /// <summary>
  /// クマのグラフィックハンドルの配列の要素数を定数kBearElementNumberに格納する
  /// </summary>
  static const int kBearElementNumber = 3;

  /// <summary>
  /// 光のグラフィックハンドルの配列の要素数を定数kLightElementNumberに格納する
  /// </summary>
  static const int kLightElementNumber = 8;

  /// <summary>
  /// 旗のグラフィックハンドルの配列の要素数を定数kGoalElementNumberに格納する
  /// </summary>
  static const int kGoalElementNumber = 4;

  /// <summary>
  /// 旗の画像の横向きの分割数を定数kFlagXに格納する
  /// </summary>
  static const int kFlagX = 1;

  /// <summary>
  /// 旗の画像の縦向きの分割数を定数kFlagYに格納する
  /// </summary>
  static const int kFlagY = 4;

  /// <summary>
  /// カウントダウンの画像の横向きの分割数を定数kCountdownXに格納する
  /// </summary>
  static const int kCountdownX = 5;

  /// <summary>
  /// カウントダウンの画像の縦向きの分割数を定数kCountdownYに格納する
  /// </summary>
  static const int kCountdownY = 2;

  /// <summary>
  /// ３秒前カウントダウンの画像の横向きの分割数を定数kThreeCountdownXに格納する
  /// </summary>
  static const int kThreeCountdownX = 3;

  /// <summary>
  /// ３秒前カウントダウンの画像の縦向きの分割数を定数kThreeCountdownYに格納する
  /// </summary>
  static const int kThreeCountdownY = 1;

  /// <summary>
  /// キャラクターの画像の横向きの分割数を定数kBearDuckXに格納する
  /// </summary>
  static const int kBearDuckX = 3;

  /// <summary>
  /// キャラクターの画像の縦向きの分割数を定数kBearDuckYに格納する
  /// </summary>
  static const int kBearDuckY = 1;

  /// <summary>
  /// アヒルがダメージを受ける画像の横向きの分割数を定数kDamageDuckXに格納する
  /// </summary>
  static const int kDamageDuckX = 6;

  /// <summary>
  /// アヒルがダメージを受ける画像の縦向きの分割数を定数kDamageDuckYに格納する
  /// </summary>
  static const int kDamageDuckY = 1;

  /// <summary>
  /// タイムアップの画像の横向きの分割数を定数kTimeUpXに格納する
  /// </summary>
  static const int kTimeUpX = 4;

  /// <summary>
  /// タイムアップの画像の縦向きの分割数を定数kTimeUpYに格納する
  /// </summary>
  static const int kTimeUpY = 1;

  /// <summary>
  /// アヒルがダメージを受ける画像の幅を定数kDamageDuckSizeXに格納する
  /// </summary>
  static const int kDamageDuckSizeX = 120;

  /// <summary>
  /// アヒルがダメージを受ける画像の高さを定数kDamageDuckSizeYに格納する
  /// </summary>
  static const int kDamageDuckSizeY = 64;

  /// <summary>
  /// クマがダメージを受ける画像の幅と高さを定数kDamageBearSizeに格納する
  /// </summary>
  static const int kDamageBearSize = 60;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// 少し透過させた状態でフェードインする時のフェード値を定数kMiddleFadeValueに格納する
  /// </summary>
  static const int kMiddleFadeValue = 50;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 10;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  /// 紙吹雪のフェードインの待ち時間を定数kConfettiWaitTimeに格納する
  /// </summary>
  static const int kConfettiWaitTime = 500;

  /// <summary>
  /// ３秒前カウントダウンの待ち時間を定数kConfettiWaitTimeに格納する
  /// </summary>
  static const int kThreeCountWaitTime = 1000;

  /// <summary>
  /// クマが走り始めた時間からの累積時間の制限時間を定数kRunningWaitTimeに格納する
  /// </summary>
  static const float kRunningWaitTime = 0.3f;

  /// <summary>
  /// クマが刺された直後から走っている状態に遷移するまでの時間を定数kAttackedWaitTimeに格納する
  /// </summary>
  static const float kAttackedWaitTime = 0.1f;

  /// <summary>
  /// クマが止まり始めた時間からの累積時間の制限時間を定数kStopWaitTimeに格納する
  /// </summary>
  static const float kStopWaitTime = 1.0f;

  /// <summary>
  /// アヒルとハチの位置が一致してから全体の動きを止めるまでの待ち時間を定数kTimeToStopに格納する
  /// </summary>
  static const float kTimeToStop = 0.0f;

  /// <summary>
  /// アヒルがハチに刺されてからBGMを止めるまでの待ち時間を定数kTimeToBgmStopに格納する
  /// </summary>
  static const float kTimeToBgmStop = 0.2f;

  /// <summary>
  /// アヒルがダメージを受けるアニメーションを実行する回数を定数kAnimationCountに格納する
  /// </summary>
  static const int kAnimationCount = 1;

  // <summary>
  //クマとアヒルの画像の幅と高さを定数kBearDuckSizeに格納する
  /// <summary>
  static const int kBearDuckSize = 40;

  // <summary>
  //旗の画像の幅を定数kGoalSizeXに格納する
  /// <summary>
  static const int kGoalSizeX = 106;

  // <summary>
  //旗の画像の高さを定数kGoalSizeYに格納する
  /// <summary>
  static const int kGoalSizeY = 70;

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
  /// ゴールのX位置を定数kGoalXに格納する
  /// </summary>
  static const int kGoalX = 16;

  /// <summary>
  /// ゴールのY位置を定数kGoalYに格納する
  /// </summary>
  static const int kGoalY = 7;

  /// <summary>
  /// 10秒前カウントダウンの画像の幅を定数kTenCountdownSizeXに格納する
  /// </summary>
  static const int kTenCountdownSizeX = 50;

  /// <summary>
  /// 10秒前カウントダウンの画像の高さを定数kTenCountdownSizeYに格納する
  /// </summary>
  static const int kTenCountdownSizeY = 50;

  /// <summary>
  /// 3秒前カウントダウンの画像の幅を定数kThreeCountdownSizeXに格納する
  /// </summary>
  static const int kThreeCountdownSizeX = 118;

  /// <summary>
  /// 3秒前カウントダウンの画像の高さを定数kThreeCountdownSizeYに格納する
  /// </summary>
  static const int kThreeCountdownSizeY = 117;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの縦向きの分割数を定数kConfettiYに格納する
  /// </summary>
  static const int kConfettiY = 12;

  /// <summary>
  /// 紙吹雪のアニメーションコマ数を定数kConfettiCountに格納する
  /// </summary>
  static const int kConfettiCount = 5;

  /// <summary>
  /// 2秒数えるための2の数字を定数kCountTwoに格納する
  /// </summary>
  static const int kCountTwo = 2;

  /// <summary>
  /// 3秒数えるための3の数字を定数kCountThreeに格納する
  /// </summary>
  static const int kCountThree = 3;

  /// <summary>
  //10秒前カウントダウンの表示開始位置を調整する定数kTenCountdownX
  /// <summary>
  static const int kTenCountdownX = 335;

  /// <summary>
  //5秒前～1秒前カウントダウンの表示開始位置を調整する定数kTenCountdownY
  /// <summary>
  static const int kFiveOneCountdownY = 240;

  /// <summary>
  //表示するX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 120;

  /// <summary>
  //表示するY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 560;

  /// <summary>
  /// 蜂の巣の１つの部屋の画像のファイル名を定数kRoomPngに格納する
  /// </summary>
  static const char* kRoomPng = "Assets/room.png";

  /// <summary>
  /// 蜂の巣の繋ぎ目の画像のファイル名を定数kJointPngに格納する
  /// </summary>
  static const char* kJointPng = "Assets/joint.png";

  /// <summary>
  /// BattleLevelの背景画像のファイル名を定数kBattleBackPngに格納する
  /// </summary>
  static const char* kBattleBackPng = "Assets/battle_back.png";

  /// <summary>
  /// 赤い蜂の画像のファイル名を定数kRedBeePngに格納する
  /// </summary>
  static const char* kRedBeePng = "Assets/red_bee.png";

  /// <summary>
  /// 黄色い蜂の画像のファイル名を定数kYellowBeePngに格納する
  /// </summary>
  static const char* kYellowBeePng = "Assets/yellow_bee.png";

  /// <summary>
  /// 笑顔のクマの画像のファイル名を定数kSmileBearPngに格納する
  /// </summary>
  static const char* kSmileBearPng = "Assets/smile_bear.png";

  /// <summary>
  /// 蜂蜜の画像のファイル名を定数kHoneyPngに格納する
  /// </summary>
  static const char* kHoneyPng = "Assets/honey.png";

  /// <summary>
  /// ゲームクリアの画像のファイル名を定数kGameClearPngに格納する
  /// </summary>
  static const char* kGameClearPng = "Assets/game_clear.png";

  /// <summary>
  /// キー操作情報の画像のファイル名を定数kKeyInfoPngに格納する
  /// </summary>
  static const char* kKeyInfoPng = "Assets/key_info.png";

  /// <summary>
  /// 黒い画像のファイル名を定数kBlackPngに格納する
  /// </summary>
  static const char* kBlackPng = "Assets/black.png";

  /// <summary>
  /// ゲームオーバーの画像のファイル名を定数kGameOverPngに格納する
  /// </summary>
  static const char* kGameOverPng = "Assets/gameover.png";

  /// <summary>
  /// スタートUIの画像のファイル名を定数kStartPngに格納する
  /// </summary>
  static const char* kStartPng = "Assets/start.png";

  /// <summary>
  /// ポーズUIの画像のファイル名を定数kPausePngに格納する
  /// </summary>
  static const char* kPausePng = "Assets/pause.png";

  /// <summary>
  /// クマの画像のファイル名を定数kBearPngに格納する
  /// </summary>
  static const char* kBearPng = "Assets/bear.png";

  /// <summary>
  /// アヒルの画像のファイル名を定数kDuckPngに格納する
  /// </summary>
  static const char* kDuckPng = "Assets/duck.png";

  /// <summary>
  /// ゴールの画像のファイル名を定数kGoalPngに格納する
  /// </summary>
  static const char* kGoalPng = "Assets/goal.png";

  /// <summary>
  /// ダメージを受けたアヒルの画像のファイル名を定数kDamageDuckPngに格納する
  /// </summary>
  static const char* kDamageDuckPng = "Assets/damage_duck.png";

  /// <summary>
  /// ダメージを受けたクマの画像のファイル名を定数kDamageBearPngに格納する
  /// </summary>
  static const char* kDamageBearPng = "Assets/damage_bear.png";

  /// <summary>
  /// カウントダウンの画像のファイル名を定数kCountdownPngに格納する
  /// </summary>
  static const char* kCountdownPng = "Assets/countdown.png";

  /// <summary>
  /// タイムアップの画像のファイル名を定数kTimeUpPngに格納する
  /// </summary>
  static const char* kTimeUpPng = "Assets/timeup.png";

  /// <summary>
  /// 10秒前カウントダウンの画像のファイル名を定数kTenNumberPngに格納する
  /// </summary>
  static const char* kTenNumberPng = "Assets/ten_countdown.png";

  /// <summary>
  /// 3秒前カウントダウンの画像のファイル名を定数kThreeNumberPngに格納する
  /// </summary>
  static const char* kThreeNumberPng = "Assets/number.png";

  /// <summary>
  /// 紙吹雪の画像のファイル名を定数kConfettiPngに格納する
  /// </summary>
  static const char* kConfettiPng = "Assets/confetti.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/No.0090.mp3";

  /// <summary>
  /// ダメージを受けたサウンドのファイル名を定数kDamageMp3に格納する
  /// </summary>
  static const char* kDamageMp3 = "Assets/punch.mp3";

  /// <summary>
  /// ゲームオーバーのサウンドのファイル名を定数kGameOverMp3に格納する
  /// </summary>
  static const char* kGameOverMp3 = "Assets/Shock4.mp3";

  /// <summary>
  /// ゲームクリアのサウンドのファイル名を定数kGameClearMp3に格納する
  /// </summary>
  static const char* kGameClearMp3 = "Assets/clear.mp3";

  /// <summary>
  /// タイムアップのサウンドのファイル名を定数kTimeUpMp3に格納する
  /// </summary>
  static const char* kTimeUpMp3 = "Assets/whistle.mp3";
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , player_controller_(nullptr)
  , menu_controller_(nullptr)
  , attacked_(false)
  , enemy_x_(0)
  , enemy_y_(0)
  , enemy_id_(0)
  , black_handle_(0)
  , last_render_(false)
  , animation_accumulation_time_(0.0f)
  , animation_accumulation_count_(0)
  , running_time_(0.0f)
  , stop_time_(0.0f)
  , gameover_handle_(0)
  , second_duck_handle_(0)
  , pause_time_(0.0f)
  , timeup_pause_time_(0.0f)
  , game_clear_time_(0.0f)
  , phase_type_(kPreparation)
  , rendered_three_count_(false)
  , gameover_fade_end_(false)
  , bgm_stop_waittime_(0.0f)
  , bear_attacked_waittime_(0.0f)
{
  DEBUG_PRINT(BattleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , player_controller_(nullptr)
  , menu_controller_(nullptr)
  , attacked_(false)
  , enemy_x_(0)
  , enemy_y_(0)
  , enemy_id_(0)
  , black_handle_(0)
  , last_render_(false)
  , animation_accumulation_time_(0.0f)
  , animation_accumulation_count_(0)
  , gameover_handle_(0)
  , second_duck_handle_(0)
  , pause_time_(0.0f)
  , timeup_pause_time_(0.0f)
  , phase_type_(kPreparation)
  , rendered_three_count_(false)
  , gameover_fade_end_(false)
  , bgm_stop_waittime_(0.0f)
  , bear_attacked_waittime_(0.0f)
{
  DEBUG_PRINT(BattleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::~BattleLevel() {
  DEBUG_PRINT(BattleLevelのデストラクタ);
}

/// <summary>
/// 各方向キーが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDirectionKey(Character& character, Field::DirectionType direction) {
  DEBUG_PRINT(各方向キーが押された時のイベント);

  //プレイヤーが移動する前にプレイヤーの現在位置をクマさんクラスに渡す
  int player_x = player_->GetXPosition();
  int player_y = player_->GetYPosition();
  bear_->SetDuckXPos(player_x);
  bear_->SetDuckYPos(player_y);

  //整数xとyを用意し、初期化
  int x = 0;
  int y = 0;

  //進む方向が歩けるか確認する
  bool can_walk = field_->MoveCharacter(&character, direction, x, y);

  if (can_walk) {
    int walk_sound = field_->GetBgmHandle();
    //サウンドを再生する
    PlaySoundMem(walk_sound, DX_PLAYTYPE_BACK);
    character.SetXPosition(x);
    character.SetYPosition(y);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);
  }

  //ぶつかった時の処理
  BumpCharacter(character);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  //フェードアウトでレベルを終了する
  //FadeOut();
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
  //プレイ中の場合
  if (phase_type_ == kProcessing) {

    //ポーズUIを表示中フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kDisplay);

    //プレイ中断フェーズに変更する
    phase_type_ = kStop;

    //全ての動きを止める
    StopAll();

    //サウンドを止める
    StopSoundMem(bgm_handle_);
  }

  //プレイ中段中の場合
  else if (phase_type_ == kStop) {

    //ポーズUIを表示前フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kPreDisplay);

    //プレイ中フェーズに変更する
    phase_type_ = kProcessing;

    //全ての動きを元に戻す
    SetPlayingAll();

    //サウンドを再生する
    PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP, FALSE);
  }
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 死んだ時のイベント(引数のキャラをタスクマネージャーから降ろす)
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::UnloadCharacter(Character& character) {
  DEBUG_PRINT(死んだ時のイベント);

  //引数のキャラのタスクを解放するためにrelease_taskに格納する
  Task* release_task = task_manager_->UnloadTask(character.GetId());

  //release_taskのメモリを解放する
  delete release_task;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(BattleLevelの初期化処理);

  //画像データをロードする
  ImageInfo room_info = LoadImage(kRoomPng);
  ImageInfo joint_info = LoadImage(kJointPng);
  ImageInfo battle_back_info = LoadImage(kBattleBackPng);
  ImageInfo red_bee_info = LoadImage(kRedBeePng);
  ImageInfo yellow_bee_info = LoadImage(kYellowBeePng);
  ImageInfo smile_bear_info = LoadImage(kSmileBearPng);
  ImageInfo honey_info = LoadImage(kHoneyPng);
  ImageInfo clear_info = LoadImage(kGameClearPng);
  ImageInfo key_info = LoadImage(kKeyInfoPng);
  ImageInfo black_info = LoadImage(kBlackPng);
  ImageInfo gameover_info = LoadImage(kGameOverPng);
  ImageInfo start_info = LoadImage(kStartPng);
  ImageInfo pause_info = LoadImage(kPausePng);
  std::array<int, kBearElementNumber> bear_handle;
  std::array<int, kDuckElementNumber> duck_handle;
  std::array<int, kGoalElementNumber> goal_handle;
  std::array<int, kDamageDuckElementNumber> damage_duck_handle;
  std::array<int, kBearElementNumber> damage_bear_handle;
  std::array<int, kElementNumber> countdown_handle;
  std::array<int, kTimeUpElementNumber> timeup_handle;
  std::array<int, kElementNumber> ten_countdown_handle;
  std::array<int, kThreeElementNumber> three_countdown_handle;
  std::array<int, kConfettiElementNumber> confetti_handle;
  int bear_gr_handle = LoadDivGraph(kBearPng, kBearElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &bear_handle[0]);
  int duck_gr_handle = LoadDivGraph(kDuckPng, kDuckElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &duck_handle[0]);
  int goal_gr_handle = LoadDivGraph(kGoalPng, kGoalElementNumber, kFlagX, kFlagY, kGoalSizeX, kGoalSizeY, &goal_handle[0]);
  int damage_gr_handle = LoadDivGraph(kDamageDuckPng, kDamageDuckElementNumber, kDamageDuckX, kDamageDuckY, kDamageDuckSizeX, kDamageDuckSizeY, &damage_duck_handle[0]);
  int damage_bear_gr_handle = LoadDivGraph(kDamageBearPng, kBearElementNumber, kBearDuckX, kBearDuckY, kDamageBearSize, kDamageBearSize, &damage_bear_handle[0]);
  int countdown_gr_handle = LoadDivGraph(kCountdownPng, kElementNumber, kCountdownX, kCountdownY, MAP_SIZE, MAP_SIZE, &countdown_handle[0]);
  int timeup_gr_handle = LoadDivGraph(kTimeUpPng, kTimeUpElementNumber, kTimeUpX, kTimeUpY, kScreenSizeX, kScreenSizeY, &timeup_handle[0]);
  int ten_countdown_gr_handle = LoadDivGraph(kTenNumberPng, kElementNumber, kCountdownX, kCountdownY, kTenCountdownSizeX, kTenCountdownSizeY, &ten_countdown_handle[0]);
  int three_countdown_gr_handle = LoadDivGraph(kThreeNumberPng, kThreeElementNumber, kThreeCountdownX, kThreeCountdownY, kThreeCountdownSizeX, kThreeCountdownSizeY, &three_countdown_handle[0]);
  int confetti_gr_handle = LoadDivGraph(kConfettiPng, kConfettiElementNumber, kBearDuckX, kConfettiY, kScreenSizeX, kScreenSizeY, &confetti_handle[0]);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int attacked_handle = LoadSoundMem(kDamageMp3);
  int gameover_sound_handle = LoadSoundMem(kGameOverMp3);
  int gameclear_sound_handle = LoadSoundMem(kGameClearMp3);
  int timeover_sound_handle = LoadSoundMem(kTimeUpMp3);

  //フィールドのインスタンスを生成する
  field_ = new Field(Task::kField, task_manager_);

  //プレイヤーのインスタンスを生成する
  player_ = new Player(Task::kPlayer, task_manager_, *this, duck_handle);

  //クマのインスタンスを生成する
  bear_ = new Bear(Task::kBear, task_manager_, *this, bear_handle, damage_bear_handle);

  //スタートUIのインスタンスを生成する
  start_ui_ = new StartUi(Task::kStartUi, *this);

  //バトル情報UIのインスタンスを生成する
  info_ui_ = new InfoUi(Task::kInfoUi, countdown_handle, timeup_handle, ten_countdown_handle, three_countdown_handle);

  //ポーズUIのインスタンスを生成する
  pause_ui_ = new PauseUi(Task::kPauseUi, pause_info.handle);

  //ゴールの旗のインスタンス生成
  goal_flag_ = new GoalFlag(Task::kGoalFlag, goal_handle);

  //ロードした画像データのグラフィックハンドルを渡す
  field_->SetRoomGrHandle(room_info.handle);
  field_->SetJointGrHandle(joint_info.handle);
  field_->SetBattleBackGrHandle(battle_back_info.handle);
  //field_->SetGoalGrHandle(goal_info.handle);
  field_->SetHoneyGrHandle(honey_info.handle);
  field_->SetClearGrHandle(clear_info.handle);
  field_->SetKeyInfoGrHandle(key_info.handle);
  //player_->SetGrHandle(player_info.handle);
  //player_->SetGrHandle(duck_gr_handle);
  //bear_->SetBearGrHandle(bear_info.handle);
  //bear_->SetBearGrHandle(bear_gr_handle);
  bear_->SetSmileBearHandle(smile_bear_info.handle);
  SetBlackGrHandle(black_info.handle);
  SetGameOverGrHandle(gameover_info.handle);
  //SetDuckSecondGrHandle(second_duck_info.handle);
  player_->SetDamageGrHandle(damage_duck_handle);
  info_ui_->SetGrHandle(countdown_gr_handle);
  SetConfettiHandle(confetti_handle);
  start_ui_->SetGrHandle(start_info.handle);
  //SetPushEnterGrHandle(gameover_result_info.handle);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetAttackedSoundHandle(attacked_handle);
  SetGameOverSoundHandle(gameover_sound_handle);
  SetGameClearSoundHandle(gameclear_sound_handle);
  SetTimeOverSoundHandle(timeover_sound_handle);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  //ロードしたプレイヤー画像から取得した幅をプレイヤーの画像の幅に設定する
  //player_->SetWidth(player_info.size_x);
  player_->SetWidth(kBearDuckSize);
  //ロードしたプレイヤー画像から取得した高さをプレイヤーの画像の高さに設定する
  //player_->SetHeight(player_info.size_y);
  player_->SetHeight(kBearDuckSize);

  //ロードしたクマ画像から取得した幅をクマの画像の幅に設定する
  //bear_->SetWidth(bear_info.size_x);
  bear_->SetWidth(kBearDuckSize);
  //ロードしたクマ画像から取得した高さをクマの画像の高さに設定する
  //bear_->SetHeight(bear_info.size_y);
  bear_->SetHeight(kBearDuckSize);

  //ロードした画像から取得した幅をスタートUI画像の幅に設定する
  start_ui_->SetWidth(start_info.size_x);
  //ロードした画像から取得した高さをスタートUI画像の幅に設定する
  start_ui_->SetHeight(start_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float> (start_info.size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float> (start_info.size_y) / 2;

  //スタートUI画像の幅の半分を設定する
  start_ui_->SetHalfWidth(half_width);
  //スタートUI画像の高さの半分を設定する
  start_ui_->SetHalfHeight(half_height);

  //ロードした画像から取得した幅をポーズUI画像の幅に設定する
  pause_ui_->SetWidth(pause_info.size_x);
  //ロードした画像から取得した高さをポーズUI画像の幅に設定する
  pause_ui_->SetHeight(pause_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  half_width = static_cast<float> (pause_info.size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  half_height = static_cast<float> (pause_info.size_y) / 2;

  //ポーズUI画像の幅の半分を設定する
  pause_ui_->SetHalfWidth(half_width);
  //ポーズUI画像の高さの半分を設定する
  pause_ui_->SetHalfHeight(half_height);

  //キャラクターの種類にプレイヤーを設定する
  player_->SetCharacterType(Character::kPlayer);

  //プレイヤーをFieldのキャラクターリストに登録する
  field_->RegisterCharacter(player_->GetId(), player_);

  //キャラクターの種類にクマを設定する
  bear_->SetCharacterType(Character::kBear);

  //クマをFieldのキャラクターリストに登録する
  field_->RegisterCharacter(bear_->GetId(), bear_);

  //生成したインスタンスをタスクマネージャーに積む
  task_manager_->AddTask(field_);
  task_manager_->AddTask(player_);
  task_manager_->AddTask(bear_);
  task_manager_->AddTask(info_ui_);
  task_manager_->AddTask(pause_ui_);
  task_manager_->AddTask(goal_flag_);

  for (int i = 0; i < kRedBeeNum; i++) {
    TaskId task_id = static_cast<TaskId>(static_cast<int>(TaskId::kRedBee) + i);

    //敵を生成する
    red_bee_[i] = new RedBee(task_id, task_manager_, *this, *this, *this);

    //敵の生成したインスタンスをタスクマネージャーに積む
    task_manager_->AddTask(red_bee_[i]);

    //キャラクターの種類に敵を設定する
    red_bee_[i]->SetCharacterType(Character::kRedBee);

    //敵をFieldのキャラクターリストに登録する
    field_->RegisterCharacter(red_bee_[i]->GetId(), red_bee_[i]);

    //敵キャラのロードした画像のグラフィックハンドルを渡す
    red_bee_[i]->SetGrHandle(red_bee_info.handle);

    //敵キャラの画像の幅と高さを設定する
    red_bee_[i]->SetWidth(red_bee_info.size_x);
    red_bee_[i]->SetHeight(red_bee_info.size_y);
  }

  for (int i = 0; i < kYellowBeeNum; i++) {
    TaskId task_id = static_cast<TaskId>(static_cast<int>(TaskId::kYellowBee) + i);

    //敵を生成する
    yellow_bee_[i] = new YellowBee(task_id, task_manager_, *this, *this, *this);

    //敵の生成したインスタンスをタスクマネージャーに積む
    task_manager_->AddTask(yellow_bee_[i]);

    //キャラクターの種類に敵を設定する
    yellow_bee_[i]->SetCharacterType(Character::kYellowBee);

    //敵をFieldのキャラクターリストに登録する
    field_->RegisterCharacter(yellow_bee_[i]->GetId(), yellow_bee_[i]);

    //敵キャラのロードした画像のグラフィックハンドルを渡す
    yellow_bee_[i]->SetGrHandle(yellow_bee_info.handle);

    //敵キャラの画像の幅と高さを設定する
    yellow_bee_[i]->SetWidth(yellow_bee_info.size_x);
    yellow_bee_[i]->SetHeight(yellow_bee_info.size_y);
  }

  //プレイヤーコントローラーを生成する
  player_controller_ = new PlayerController(Task::kPlayerController, *this, *player_);
  //生成したプレイヤーコントローラーを、タスクマネージャーに積む
  task_manager_->AddTask(player_controller_);

  //メニューコントローラーを生成する
  menu_controller_ = new MenuController(Task::kMenuController, *this);
  //生成したメニューコントローラーを、タスクマネージャーに積む
  task_manager_->AddTask(menu_controller_);

  //ゲームモードを生成する
  game_mode_ = new GameMode(Task::kGameMode, *this);
  //生成したゲームモードを、タスクマネージャーに積む
  task_manager_->AddTask(game_mode_);

  //ゲームステートを生成する
  game_state_ = new GameState(Task::kGameState, *this);
  //生成したゲームステートを、タスクマネージャーに積む
  task_manager_->AddTask(game_state_);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name ="time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(BattleLevelの毎フレーム更新処理のフェーズ処理);
  accumulation_time_ = accumulation_time_ + time;

  //アヒルさんとクマさんの位置を取得する
  int player_x = player_->GetXPosition();
  int player_y = player_->GetYPosition();
  int bear_x = bear_->GetXPosition();
  int bear_y = bear_->GetYPosition();

  //準備中フェーズの場合
  if (phase_type_ == kPreparation) {
    //スタートUI表示フェーズに変更する
    phase_type_ = kStartUiDisplay;
  }

  if (phase_type_ == kStartUiDisplay) {
    //スタートUIを積む
    //task_manager_->AddTask(start_ui_);
    //スタートUI終了待機フェーズに変更する
    phase_type_ = kStartUiFinishWaiting;
  }

  if (phase_type_ == kStartUiFinishWaiting) {
    //スタートUI終了待機フェーズの場合、プレイ中フェーズに変更する
    phase_type_ = kProcessing;
  }

  Field::FieldPhaseType phase = field_->GetFieldPhaseType();
  if (phase == Field::kProcessing && rendered_three_count_ == false) {
    RenderThreeCount();
  }

  //プレイヤーが死んだフェーズの場合
  if (phase_type_ == kPlayerDead) {

    //プレイヤー、赤いハチ、黄色いハチのいずれかのplayer_is_deadがtrueになっていたら、last_render_ をtrueにする
    for (int i = 0; i < kRedBeeNum; i++) {
      bool player_is_dead_player = player_->GetPlayerIsDead();
      bool player_is_dead_red_bee = red_bee_[i]->GetPlayerIsDead();
      bool player_is_dead_yellow_bee = yellow_bee_[i]->GetPlayerIsDead();
      if (player_is_dead_player || player_is_dead_red_bee || player_is_dead_yellow_bee) {
        last_render_ = true;
      }
    }

    //最後の描画が終わったことを表すlast_render_ がtrueになっていたら、
    if (last_render_ == true) {

      player_->SetPlayerIsDead();

      pause_time_ = pause_time_ + time;
      
      if (pause_time_ >= kTimeToStop) {
        //ぶつかった瞬間、全体の動きを止める
        StopAll();
      }
      if (pause_time_ >= kStopWaitTime) {
        //アヒルだけ終了フェーズにする
        SetDuckFinish();
      }
      
      //ダメージを受けた時のアニメーションの終了有無を取得する
      bool is_damage_animation_end = player_->CheckIsDamagedAnimationEnd();

      //ダメージを受けた時のアニメーションが終了した場合
      if (is_damage_animation_end) {
        //ゲームオーバー時のクリアの有無を設定する
        SetGameOver();
        //フェーズをアヒルが泣いているフェーズに変更する
        //phase_type_ = kDuckCrying;
      }
    }
    
  }

  //プレイヤーが死んだ直後の場合
  else if (player_->CheckIsDead() == true) {

    bgm_stop_waittime_ = bgm_stop_waittime_ + time;

    if (bgm_stop_waittime_ >= kTimeToBgmStop) {
      //サウンドを止める
      StopSoundMem(bgm_handle_);

      //ダメージを受けた時の効果音を再生する
      PlaySoundMem(attacked_handle_, DX_PLAYTYPE_BACK);

      bgm_stop_waittime_ = 0.0f;

      phase_type_ = kPlayerDead;
      //DEBUG_PRINT(アヒルが倒れた);

    }

  }

  if (phase_type_ == kFinishUiDisplay) {

  }

  if (phase_type_ == kFinishUiFinishWaiting) {

    //バトル終了フェーズに遷移する
    phase_type_ = kBattleFinish;
  }

  if (phase_type_ == kBattleFinish) {
    //バトル終了フェーズなら、そのままBattleLevelを終了できるようにする
    is_finish_ = true;
  }

  Bear::BearType bear_type = bear_->GetBearType();

  //クマが泣きながら行き止まりへ向かって走っている間だけ、アヒルとハチの動きを止める
  if (bear_type == Bear::kRunning || bear_type == Bear::kWait) {
    running_time_ = running_time_ + time;
    if (running_time_ >= kRunningWaitTime) {
      StopDuckBee();
    }
  }
  //クマが行き止まりで止まっている場合
  else if (bear_type == Bear::kStopInDeadEnd) {
    stop_time_ = stop_time_ + time;
    //アヒルさんの現在位置をセットする
    bear_->SetNowDuckXPos(player_x);
    bear_->SetNowDuckYPos(player_y);
    //アヒルとハチを動ける状態に戻す
    if (stop_time_ >= kStopWaitTime) {
      SetPlayingDuckBee();
      running_time_ = 0.0f;
      stop_time_ = 0.0f;
    }
  }
  //クマさんが笑顔の状態の場合
  else if (bear_type == Bear::kSmile) {
    stop_time_ = 0.0f;
    //アヒルさんの現在位置を「アヒルさんが居た位置」にセットする
    bear_->SetDuckXPos(player_x);
    bear_->SetDuckYPos(player_y);
    //アヒルとハチを動ける状態に戻す
    SetPlayingDuckBee();
  }

  //クマが刺された直後の状態の場合
  if (bear_type == Bear::kAttacked) {
    bear_attacked_waittime_ = bear_attacked_waittime_ + time;
    //クマが走っている状態に遷移する
    if (bear_attacked_waittime_ >= kAttackedWaitTime) {
      bear_attacked_waittime_ = 0.0f;
      bear_->SetBearType(Bear::kRunning);
    }
  }

  //クマとアヒルが両方ゴールした場合
  if (player_x == kGoalX && player_y == kGoalY && bear_x == kGoalX && bear_y == kGoalY && phase_type_ != kClear) {

    //ゲームクリア時の効果音を再生する
    PlaySoundMem(gameclear_sound_handle_, DX_PLAYTYPE_BACK);

    game_clear_time_ = game_clear_time_ + time;
    if (game_clear_time_ >= kRunningWaitTime) {
      //全体の動きを止める
      StopAll();
      if (game_clear_time_ >= kStopWaitTime) {
        int clear_handle = field_->GetClearGrHandle();
        FadeIn(0, 0, clear_handle, TRUE, kFadeValue);
        //ゲームクリアの状態に遷移する
        phase_type_ = kClear;
      }    
    }   
  }

  if (phase_type_ == kClear) {
    GameClear();
  }

  bool last_render = info_ui_->GetLastRender();
  //DEBUG_PRINT_VAR(last_render);
  if (last_render && phase_type_ != kTimeOver) {
    //全体の動きを止める
    StopAll();
    timeup_pause_time_ = timeup_pause_time_ + time;
    if (timeup_pause_time_ >= kStopWaitTime) {
      FadeIn(0, 0, black_handle_, TRUE, kMiddleFadeValue);
      //タイムオーバーの状態に遷移する
      DEBUG_PRINT(タイムオーバーの状態に遷移する);
      phase_type_ = kTimeOver;
      timeup_pause_time_ = 0.0f;
    }
  }

  if (phase_type_ == kTimeOver) {
    TimeUp();
  }

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }
  else if (accumulation_time_ >= kLimitTime) {
    DEBUG_PRINT(30秒経った);
    is_finish_ = true;
  }

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::ProcessingRender() {
  //DEBUG_PRINT(BattleLevelの毎フレームの描画処理);
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(BattleLevelの終了処理);

    //描画をクリアする
    ClearDrawScreen();

  //画像のグラフィックハンドルを取得する
  //取得したグラフィックハンドルを使い、リソースを破棄する
  int room_handle = DeleteGraph(field_->GetRoomGrHandle());
  int joint_handle = DeleteGraph(field_->GetJointGrHandle());
  int battle_back_handle = DeleteGraph(field_->GetBattleBackGrHandle());
  int player_handle = DeleteGraph(player_->GetGrHandle(0));
  int enemy_handle = DeleteGraph(red_bee_[0]->GetGrHandle());
  int bear_handle = DeleteGraph(bear_->GetBearGrHandle(0));
  int goal_handle = DeleteGraph(goal_flag_->GetGoalGrHandle(0));
  int honey_handle = DeleteGraph(field_->GetHoneyGrHandle());
  int clear_handle = DeleteGraph(field_->GetClearGrHandle());
  int key_info_handle = DeleteGraph(field_->GetKeyInfoGrHandle());
  int black_handle = DeleteGraph(GetBlackGrHandle());
  int gameover_handle = DeleteGraph(GetGameOverGrHandle());
  int player_damage_handle = DeleteGraph(player_->GetDamageGrHandle(0));
  int bear_damage_handle = DeleteGraph(bear_->GetDamageBearGrHandle(0));
  int smile_bear_handle = DeleteGraph(bear_->GetSmileBearHandle());
  int start_gr_handle = DeleteGraph(start_ui_->GetGrHandle());
  int pause_gr_handle = DeleteGraph(pause_ui_->GetGrHandle());
  for (int i = 0; i < kElementNumber; ++i) {
    int info = DeleteGraph(info_ui_->GetGrHandle(i));
  }
  for (int i = 0; i < kTimeUpElementNumber; ++i) {
    int info = DeleteGraph(info_ui_->GetTimeUpGrHandle(i));
  }
  for (int i = 0; i < kElementNumber; ++i) {
    int info = DeleteGraph(info_ui_->GetTenGrHandle(i));
  }
  for (int i = 0; i < kThreeElementNumber; ++i) {
    int info = DeleteGraph(info_ui_->GetThreeGrHandle(i));
  }
  for (int i = 0; i < kConfettiElementNumber; ++i) {
    int confetti = DeleteGraph(GetConfettiHandle(i));
  }

  //サウンドのリソースを破棄する
  int bgm_handle = DeleteSoundMem(GetBgmHandle());
  int attacked_handle = DeleteSoundMem(GetAttackedSoundHandle());
  int gameover_sound_handle = DeleteSoundMem(GetGameOverSoundHandle());
  int gameclear_sound_handle = DeleteSoundMem(GetGameClearSoundHandle());
  int timeover_sound_handle = DeleteSoundMem(GetTimeOverSoundHandle());

  if (end_type_ == kUnloadTask) {

    //タスクマネージャーに積んでいたタスクを解放するためにrelease_taskに格納する
    Task* release_task = task_manager_->UnloadTask(kMenuController);
    Task* field_release_task = task_manager_->UnloadTask(kField);
    Task* player_release_task = task_manager_->UnloadTask(kPlayer);
    Task* playercontroller_release_task = task_manager_->UnloadTask(kPlayerController);
    Task* bear_release_task = task_manager_->UnloadTask(kBear);
    Task* uiinfo_release_task = task_manager_->UnloadTask(kInfoUi);
    Task* gamemode_release_task = task_manager_->UnloadTask(kGameMode);
    Task* gamestate_release_task = task_manager_->UnloadTask(kGameState);
    Task* start_release_task = task_manager_->UnloadTask(kStartUi);
    Task* pause_release_task = task_manager_->UnloadTask(kPauseUi);
    Task* goal_release_task = task_manager_->UnloadTask(kGoalFlag);

    //release_taskのメモリを解放する
    delete release_task;
    delete field_release_task;
    delete player_release_task;
    delete playercontroller_release_task;
    delete bear_release_task;
    delete uiinfo_release_task;
    delete gamemode_release_task;
    delete gamestate_release_task;
    delete start_release_task;
    delete pause_release_task;
    delete goal_release_task;

    //赤いハチのタスクを解放する
    for (int i = 0; i < kRedBeeNum; i++) {
      TaskId task_id = static_cast<TaskId>(static_cast<int>(TaskId::kRedBee) + i);
      Task* enemy_release_task = task_manager_->UnloadTask(task_id);
      delete enemy_release_task;
    }

    //黄色いハチのタスクを解放する
    for (int i = 0; i < kYellowBeeNum; i++) {
      TaskId task_id = static_cast<TaskId>(static_cast<int>(TaskId::kYellowBee) + i);
      Task* enemy_release_task = task_manager_->UnloadTask(task_id);
      delete enemy_release_task;
    }

    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {

    //リソースを破棄する

    delete menu_controller_;
    menu_controller_ = nullptr;

    delete field_;
    field_ = nullptr;

    delete player_;
    player_ = nullptr;

    delete player_controller_;
    player_controller_ = nullptr;

    delete bear_;
    bear_ = nullptr;

    for (int i = 0; i < kRedBeeNum; i++) {
      delete red_bee_[i];
      red_bee_[i] = nullptr;
    }

    for (int i = 0; i < kYellowBeeNum; i++) {
      delete yellow_bee_[i];
      yellow_bee_[i] = nullptr;
    }

    delete info_ui_;
    info_ui_ = nullptr;

    delete game_mode_;
    game_mode_ = nullptr;

    delete game_state_;
    game_state_ = nullptr;

    delete start_ui_;
    start_ui_ = nullptr;

    delete pause_ui_;
    pause_ui_ = nullptr;

    delete goal_flag_;
    goal_flag_ = nullptr;

  }
  return true;
}

/// <summary>
/// 移動範囲をチェックする
/// </summary>
/// <param name = "enemy">敵キャラクターベースクラスの参照</param>
/// <returns>なし</returns>
void BattleLevel::CheckWalkDistance(EnemyBase& enemy) {
  //歩ける範囲のリスト型の変数walk_distancesを宣言
  std::vector<Field::DirectionType> walk_distances;
  //敵キャラクターベースクラスの参照とwalk_distancesを使い、移動範囲をチェックする
  field_->CheckWalkingDistance(enemy, walk_distances);

  //FieldクラスのCheckWalkDistance関数でwalk_distancesに格納した進める方向をセットする
  enemy.SetWalkDistance(walk_distances);

  //DEBUG_PRINT(BattleLevel　移動範囲をチェックした);
}

/// <summary>
/// キャラクターがぶつかる処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::BumpCharacter(Character& character) {
  //DEBUG_PRINT(ぶつかる処理に入った);

  //プレイヤーの位置を取得する
  int player_x = player_->GetXPosition();
  //DEBUG_PRINT_VAR(player_x);
  int player_y = player_->GetYPosition();
  //DEBUG_PRINT_VAR(player_y);

  //クマの位置を取得する
  int bear_x = bear_->GetXPosition();
  //DEBUG_PRINT_VAR(bear_x);
  int bear_y = bear_->GetYPosition();
  //DEBUG_PRINT_VAR(bear_y);

  //ハチの位置を取得する
  int red_bee_x = red_bee_[enemy_id_]->GetXPosition();
  int red_bee_y = red_bee_[enemy_id_]->GetYPosition();
  int yellow_bee_x = yellow_bee_[enemy_id_]->GetXPosition();
  int yellow_bee_y = yellow_bee_[enemy_id_]->GetYPosition();

  //アヒルとハチがぶつかった場合、ぶつかったハチがプレイヤーに攻撃する処理を実行する
  if (player_x == red_bee_x && player_y == red_bee_y) {
    AttackPlayer(player_x, player_y, red_bee_x, red_bee_y, character);
  }
  else if (player_x == yellow_bee_x && player_y == yellow_bee_y) {
    AttackPlayer(player_x, player_y, yellow_bee_x, yellow_bee_y, character);
  }

  //ハチとクマがぶつかった場合、クマがハチに刺された時の処理を実行する
  if (bear_x == red_bee_x && bear_y == red_bee_y) {
    BearStung(bear_x, bear_y, red_bee_x, red_bee_y, character);
    //ぶつかっていない方のハチの位置も保存する
    field_->SetAnotherBeeX(yellow_bee_x);
    field_->SetAnotherBeeY(yellow_bee_y);
  }
  else if (bear_x == yellow_bee_x && bear_y == yellow_bee_y) {
    BearStung(bear_x, bear_y, yellow_bee_x, yellow_bee_y, character);
    //ぶつかっていない方のハチの位置も保存する
    field_->SetAnotherBeeX(red_bee_x);
    field_->SetAnotherBeeY(red_bee_y);
  }
}

/// <summary>
/// 敵がプレイヤーにぶつかり攻撃する処理
/// </summary>
/// <param = "player_x">プレイヤーX位置</param>
/// <param = "player_y">プレイヤーY位置</param>
/// <param = "bee_x">ハチX位置</param>
/// <param = "bee_y">ハチY位置</param>
/// <param = "character">キャラクター</param>
void BattleLevel::AttackPlayer(int player_x, int player_y, int bee_x, int bee_y, Character& character) {
  if (player_x == bee_x && player_y == bee_y) {

    DEBUG_PRINT(ハチが);
    DEBUG_PRINT(プレイヤーとぶつかったので攻撃する);
    DEBUG_PRINT_VAR(player_->GetHp());

    //動いているキャラクターがプレイヤーの場合
    if (character.GetCharacterType() == Character::kPlayer) {
      //ぶつかった時の位置を保存する
      player_->SetHitPos(player_x, player_y);
    }
    //動いているキャラクターが赤いハチの場合
    else if (character.GetCharacterType() == Character::kRedBee) {
      //ぶつかった時の位置を保存する
      red_bee_[enemy_id_]->SetHitPos(bee_x, bee_y);
    }
    //動いているキャラクターが黄色いハチの場合
    else if (character.GetCharacterType() == Character::kYellowBee) {
      //ぶつかった位置を保存する
      yellow_bee_[enemy_id_]->SetHitPos(bee_x, bee_y);
    }

    //プレイヤーがダメージを受ける
    player_->IncurDamage();
    DEBUG_PRINT_VAR(player_->GetHp());
  }
}

/// <summary>
/// クマがハチに刺された時の処理
/// </summary>
/// <param = "bear_x">クマX位置</param>
/// <param = "bear_y">クマY位置</param>
/// <param = "bee_x">ハチX位置</param>
/// <param = "bee_y">ハチY位置</param>
/// <param = "character">キャラクター</param>
/// <param = "another_bee_x">もう一匹のハチのX位置</param>
/// <param = "another_bee_y">もう一匹のハチのY位置</param>
/// <returns>なし</returns>
void BattleLevel::BearStung(int bear_x, int bear_y, int bee_x, int bee_y, Character& character) {

  //動いているキャラクターがクマの場合
  if (character.GetCharacterType() == Character::kBear) {
    //ぶつかった時の位置を保存する
    bear_->SetBearHitPos(bear_x, bear_y);
  }
  //動いているキャラクターが赤いハチの場合
  else if (character.GetCharacterType() == Character::kRedBee) {
    //ぶつかった時の位置を保存する
    red_bee_[enemy_id_]->SetBearHitPos(bee_x, bee_y);
  }
  //動いているキャラクターが黄色いハチの場合
  else if (character.GetCharacterType() == Character::kYellowBee) {
    //ぶつかった位置を保存する
    yellow_bee_[enemy_id_]->SetBearHitPos(bee_x, bee_y);
  }

  //一番近い行き止まりへの経路を設定する
  SetNearestDeadEnd(bear_x, bear_y);

  //クマの現在の状態を取得する
  bool bear_type = bear_->GetBearType();

  if (bear_type != Bear::kAttacked) {
    //ダメージを受けた時の効果音を再生する
    PlaySoundMem(attacked_handle_, DX_PLAYTYPE_BACK);
    //クマが刺された直後の状態に遷移する
    bear_->SetBearType(Bear::kAttacked);
  }

}

/// <summary>
/// ゲームクリア終了のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::GameClear() {
  DEBUG_PRINT(ゲームクリア終了のイベント);

  //ゲームクリア時のクリアの有無を設定する
  SetGameClearInfo();

  //紙吹雪のアニメーションを描画する
  for (int i = 0; i < kConfettiCount; ++i) {
    DrawGraph(0, 0, confetti_handle_[i], TRUE);
    WaitTimer(kConfettiWaitTime);
  }

  //フェードアウトでレベルを終了する
  FadeOut();

  //フィニッシュUI表示フェーズに遷移する
  //phase_type_ = kFinishUiDisplay;

}

/// <summary>
/// カウントダウンのイベント
/// </summary>
/// <param name="remaining_time">残り時間</param>
/// <returns>なし</returns>
void BattleLevel::CountRemainingTime(int remaining_time) {
  //DEBUG_PRINT(カウントダウンのイベント);
  DEBUG_PRINT_VAR(remaining_time);
  //バトル情報UIに残り時間を設定する
  info_ui_->SetCountdown(remaining_time);
}

/// <summary>
/// タイムオーバーのイベント
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::TimeUp() {
  //DEBUG_PRINT(タイムオーバーのイベント);

  //タイムオーバー時の効果音を再生する
  PlaySoundMem(timeover_sound_handle_, DX_PLAYTYPE_BACK);

  info_ui_->RenderTimeUp();

  bool timeup_end = info_ui_->GetTimeUpRenderEnd();

  if (timeup_end) {
    //タイムアップのアニメーションが終わったら、ゲームオーバー
    SetGameOver();
  }

  //フィニッシュUI表示フェーズに遷移する
  //phase_type_ = kFinishUiDisplay;
}

/// <summary>
/// ゲームオーバー時にクリアの有無を設定する処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOver() {
  //DEBUG_PRINT(ゲームオーバー);

  //クリアの有無に無しを設定する
  game_mode_->SetIsGameClear(false);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  //クリアの有無に無しを設定する
  game_info->SetIsGameClear(false);

  //黒の画像を表示する
  FadeIn(0, 0, black_handle_, TRUE, kFadeValue);
  //ゲームオーバー時の効果音を再生する
  PlaySoundMem(gameover_sound_handle_, DX_PLAYTYPE_BACK);
  //ゲームオーバーの画像を表示する
  FadeIn(0, 0, gameover_handle_, TRUE, kFadeValue);

  //フェードアウトでレベルを終了する
  FadeOut();
}

/// <summary>
/// ゲームクリア時にクリアの有無を設定する処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetGameClearInfo() {
  //DEBUG_PRINT(ゲームクリア);
  //クリアの有無に無しを設定する
  game_mode_->SetIsGameClear(true);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  //クリアの有無に無しを設定する
  game_info->SetIsGameClear(true);

}

/// <summary>
/// UI終了のイベント
/// </summary>
/// <param name="task_id">終了するUIのタスクID</param>
/// <returns>なし</returns>
void BattleLevel::EndUi(TaskId task_id) {
  DEBUG_PRINT(UI終了のイベント);

  //引数のキャラのタスクを解放するためにtaskに格納する
  Task* task = task_manager_->UnloadTask(task_id);

  //release_taskのメモリを解放する
  delete task;

}

/// <summary>
/// LoadImage関数の定義
/// </summary>
/// <param = "filename">画像のファイル名</param>
/// <returns>ImageInfo構造体型のinfo</returns>
BattleLevel::ImageInfo BattleLevel::LoadImage(const char* filename) {
  BattleLevel::ImageInfo info;
  info.handle = LoadGraph(filename);
  GetGraphSize(info.handle, &info.size_x, &info.size_y);
  return info;
}

/// <summary>
/// フェードイン表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::FadeIn(int x, int y, int handle, bool is_transparent, int fade_value) {

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

/// <summary>
/// SetBlackGrHandle関数の定義
/// </summary>
/// <param = "black_handle">黒い画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetBlackGrHandle(int black_handle) {
  black_handle_ = black_handle;
}

/// <summary>
/// GetBlackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>黒い画像のグラフィックハンドル</returns>
int BattleLevel::GetBlackGrHandle() {
  return black_handle_;
}

/// </summary>
/// 2枚の画像でアニメーション表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "first_handle">１つ目のグラフィックハンドル</param>
/// <param = "second_handle">２つ目のグラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::TwoImageMoving(int x, int y, int first_handle, int second_handle, bool is_transparent, float time) {
  animation_accumulation_time_ = animation_accumulation_time_ + time;

  //一枚目の画像を表示する
  DrawGraph(x, y, first_handle, is_transparent);
  WaitTimer(kWaitTime);

  //二枚目の画像を表示する
  DrawGraph(x, y, second_handle, is_transparent);
  WaitTimer(kWaitTime);
}

/// <summary>
/// SetGameOverGrHandle関数の定義
/// </summary>
/// <param = "gameover_handle">アヒルが泣くアニメーションの画像1枚目のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOverGrHandle(int gameover_handle) {
  gameover_handle_ = gameover_handle;
}

/// <summary>
/// GetGameOverGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルが泣くアニメーションの画像1枚目のグラフィックハンドル</returns>
int BattleLevel::GetGameOverGrHandle() {
  return gameover_handle_;
}

/// <summary>
/// SetDuckSecondGrHandle関数の定義
/// </summary>
/// <param = "second_duck_handle">アヒルが泣くアニメーションの画像2枚目のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetDuckSecondGrHandle(int second_duck_handle) {
  second_duck_handle_ = second_duck_handle;
}

/// <summary>
/// GetDuckSecondGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルが泣くアニメーションの画像2枚目のグラフィックハンドル</returns>
int BattleLevel::GetDuckSecondGrHandle() {
  return second_duck_handle_;
}

/// </summary>
/// クマがハチとぶつかった時に一番近い行き止まりへの最短経路を設定する
/// </summary>
/// <param = "bear_x">X位置</param>
/// <param = "bear_y">Y位置</param>
/// <returns>なし</returns>
void BattleLevel::SetNearestDeadEnd(int bear_x, int bear_y) {
  //3つの行き止まりそれぞれへの最短経路を調べる
  field_->SearchNarestDeadEnd(bear_x, bear_y, Field::MapType::kFirstDeadEnd);
  field_->SearchNarestDeadEnd(bear_x, bear_y, Field::MapType::kSecondDeadEnd);
  field_->SearchNarestDeadEnd(bear_x, bear_y, Field::MapType::kThirdDeadEnd);
  //3つの行き止まりそれぞれへの最短経路までかかる歩数を取得する
  int first_route_count = field_->GetRouteCount(Field::MapType::kFirstDeadEnd);
  int second_route_count = field_->GetRouteCount(Field::MapType::kSecondDeadEnd);
  int third_route_count = field_->GetRouteCount(Field::MapType::kThirdDeadEnd);

  //一番目の行き止まりが一番近い場合
  if (first_route_count <= second_route_count && first_route_count <= third_route_count) {
    Field::Pos* route = field_->GetRoute(Field::MapType::kFirstDeadEnd);
    bear_->SetNearestRoute(route, first_route_count);
  }
  //二番目の行き止まりが一番近い場合
  else if (second_route_count <= first_route_count && second_route_count <= third_route_count) {
    Field::Pos* route = field_->GetRoute(Field::MapType::kSecondDeadEnd);
    bear_->SetNearestRoute(route, second_route_count);
  }
  //三番目の行き止まりが一番近い場合
  else if (third_route_count <= first_route_count && third_route_count <= second_route_count) {
    Field::Pos* route = field_->GetRoute(Field::MapType::kThirdDeadEnd);
    bear_->SetNearestRoute(route, third_route_count);
  }
}

/// <summary>
/// StopDuckBee関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopDuckBee() {
  player_->SetPhaseType(Player::kStop);
  for (int i = 0; i < kRedBeeNum; i++) {
    red_bee_[i]->SetPhaseType(RedBee::kStop);
  }
  for (int i = 0; i < kYellowBeeNum; i++) {
    yellow_bee_[i]->SetPhaseType(YellowBee::kStop);
  }
  game_state_->SetPhaseType(GameState::kStop);
}

/// <summary>
/// SetPlayingDuckBee関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetPlayingDuckBee() {
  player_->SetPhaseType(Player::kPlaying);
  for (int i = 0; i < kRedBeeNum; i++) {
    red_bee_[i]->SetPhaseType(RedBee::kPlaying);
  }
  for (int i = 0; i < kYellowBeeNum; i++) {
    yellow_bee_[i]->SetPhaseType(YellowBee::kPlaying);
  }
  game_state_->SetPhaseType(GameState::kPlaying);
}

/// <summary>
/// StopAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopAll() {
  player_->SetPhaseType(Player::kStop);
  bear_->SetPhaseType(Bear::kStop);
  for (int i = 0; i < kRedBeeNum; i++) {
    red_bee_[i]->SetPhaseType(RedBee::kStop);
  }
  for (int i = 0; i < kYellowBeeNum; i++) {
    yellow_bee_[i]->SetPhaseType(YellowBee::kStop);
  }
  game_state_->SetPhaseType(GameState::kStop);
  goal_flag_->SetPhaseType(GoalFlag::kStop);
}

/// <summary>
/// SetPlayingAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetPlayingAll() {
  player_->SetPhaseType(Player::kPlaying);
  bear_->SetPhaseType(Bear::kPlaying);
  for (int i = 0; i < kRedBeeNum; i++) {
    red_bee_[i]->SetPhaseType(RedBee::kPlaying);
  }
  for (int i = 0; i < kYellowBeeNum; i++) {
    yellow_bee_[i]->SetPhaseType(YellowBee::kPlaying);
  }
  game_state_->SetPhaseType(GameState::kPlaying);
  goal_flag_->SetPhaseType(GoalFlag::kProcessing);
}

/// <summary>
/// SetDuckFinish関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetDuckFinish() {
  player_->SetPhaseType(Player::kFinish);
  bear_->SetPhaseType(Bear::kPlaying);
  for (int i = 0; i < kRedBeeNum; i++) {
    red_bee_[i]->SetPhaseType(RedBee::kPlaying);
  }
  for (int i = 0; i < kYellowBeeNum; i++) {
    yellow_bee_[i]->SetPhaseType(YellowBee::kPlaying);
  }
  game_state_->SetPhaseType(GameState::kPlaying);
  goal_flag_->SetPhaseType(GoalFlag::kProcessing);
}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::FadeOut() {

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
    WaitTimer(kPlusAlpha);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// GetConfettiHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int BattleLevel::GetConfettiHandle(int element_num) {
  return confetti_handle_[element_num];
}

/// <summary>
/// SetConfettiHandle関数の定義
/// </summary>
/// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle) {
  confetti_handle_ = confetti_handle;
}

/// <summary>
/// RenderThreeCount関数の定義
/// </summary>
/// <param >なし</param>
/// <returns>なし</returns>
void BattleLevel::RenderThreeCount() {
  //開始3秒前の数字を表示する
  int three_handle = info_ui_->GetThreeGrHandle(kCountThree - 1);
  DrawGraph(kTenCountdownX, kFiveOneCountdownY, three_handle, true);
  WaitTimer(kThreeCountWaitTime);
  //開始2秒前の数字を表示する
  int two_handle = info_ui_->GetThreeGrHandle(kCountTwo - 1);
  DrawGraph(kTenCountdownX, kFiveOneCountdownY, two_handle, true);
  WaitTimer(kThreeCountWaitTime);
  //開始1秒前の数字を表示する
  int one_handle = info_ui_->GetThreeGrHandle(0);
  DrawGraph(kTenCountdownX, kFiveOneCountdownY, one_handle, true);
  WaitTimer(kThreeCountWaitTime);
  //スタートUIを表示する
  task_manager_->AddTask(start_ui_);
  rendered_three_count_ = true;
}

/// <summary>
/// SetPushEnterGrHandle関数の定義
/// </summary>
/// <param = "push_enter_handle">文字表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetPushEnterGrHandle(int push_enter_handle) {
  push_enter_handle_ = push_enter_handle;
}

/// <summary>
/// GetPushEnterGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>文字表示のグラフィックハンドル</returns>
int BattleLevel::GetPushEnterGrHandle() {
  return push_enter_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int BattleLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetAttackedSoundHandle関数の定義
/// </summary>
/// <param = "attacked_handle">ダメージを受けた時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetAttackedSoundHandle(int attacked_handle) {
  attacked_handle_ = attacked_handle;
}

/// <summary>
/// GetAttackedSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ダメージを受けた時のサウンドハンドル</returns>
int BattleLevel::GetAttackedSoundHandle() {
  return attacked_handle_;
}

/// <summary>
/// SetGameOverSoundHandle関数の定義
/// </summary>
/// <param = "gameover_sound_handle">ゲームオーバー時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOverSoundHandle(int gameover_sound_handle) {
  gameover_sound_handle_ = gameover_sound_handle;
}

/// <summary>
/// GetGameOverSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ゲームオーバー時のサウンドハンドル</returns>
int BattleLevel::GetGameOverSoundHandle() {
  return gameover_sound_handle_;
}

/// <summary>
/// SetGameClearSoundHandle関数の定義
/// </summary>
/// <param = "gameclear_sound_handle">ゲームクリア時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameClearSoundHandle(int gameclear_sound_handle) {
  gameclear_sound_handle_ = gameclear_sound_handle;
}

/// <summary>
/// GetGameClearSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ゲームクリア時のサウンドハンドル</returns>
int BattleLevel::GetGameClearSoundHandle() {
  return gameclear_sound_handle_;
}

/// <summary>
/// SetTimeOverSoundHandle関数の定義
/// </summary>
/// <param = "timeover_sound_handle">タイムオーバー時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetTimeOverSoundHandle(int timeover_sound_handle) {
  timeover_sound_handle_ = timeover_sound_handle;
}

/// <summary>
/// GetTimeOverSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>タイムオーバー時のサウンドハンドル</returns>
int BattleLevel::GetTimeOverSoundHandle() {
  return timeover_sound_handle_;
}