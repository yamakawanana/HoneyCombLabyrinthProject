#include <iostream>
#include "DxLib.h"
#include "System/Task/TaskManager.h"
#include "System/Task/Task.h"
#include "System/LogConsole.h"
#include "System/Level/LevelChanger.h"
#include "System/Level/Level.h"
#include "Game/GameInfo.h"
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#endif

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  // <summary>
  //taskクラスに設定するIDの定数kFirstIdを用意する
  /// <summary>
  static const int kFirstId = 1;

  // <summary>
  //毎フレーム更新処理の引数として入れる0.0fを変数float_timeに格納する
  /// <summary>
  float float_time = 0.0f;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  // <summary>
  //毎フレーム更新処理の引数として入れる0.0fを変数float_timeに格納する
  /// <summary>

  //====================================================
  //白色の値を取得
  //====================================================
  unsigned int Cr = GetColor(255, 255, 255);

  /// <summary>
  //DrawString関数のX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 250;

  /// <summary>
  //メインループである事の文字出力のDrawString関数のY座標を定数kYMainroopに格納する
  /// <summary>
  static const int kYMainroop = 160;

  /// <summary>
  //ミリ秒を秒に変換するために1000で割るので、1000を定数kNumConvertSecondに格納する
  /// <summary>
  static const float kNumConvertSecond = 1000;

  /// <summary>
  //カラービット数を定数kColorBitNumに格納する
  /// <summary>
  static const int kColorBitNum = 32;
}

/// <summary>
/// プログラムは WinMain から始まります
/// </summary>
/// <param name = "hInstance">アプリケーションの現在のインスタンスハンドル</param>
/// <param name = "hPrevInstance">Win16 の産物（常にNULL）</param>
/// <param name = "lpCmdLine">コマンドライン引数</param>
/// <param name = "nCmdShow">ウィンドウの表示状態</param>
/// <returns>アプリケーションの終了コード</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#if defined(_WIN64) || defined(_WIN32)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetBreakAlloc(253);
#endif

  ////LogConsoleクラスを宣言する
  //LogConsole log_console;

  ////CreateConsole関数を呼び出す
  //log_console.CreateConsole();

  ////ゲーム情報のインスタンスを作成する
  GameInfo::CreateInstance();

  ////インスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  ////ゲーム情報を初期化する
  if (game_info != nullptr) {
    game_info->InitGameInfo();
  }

  ////解像度の幅と高さを取得する
  int resolution_x_size = game_info->GetResolutionXSize();
  int resolution_y_size = game_info->GetResolutionYSize();

  SetWindowUserCloseEnableFlag(FALSE);

  //====================================================
  //DXライブラリの初期化前の設定
  //====================================================
  ChangeWindowMode(TRUE); // ウィンドウモードに設定
  SetGraphMode(resolution_x_size, resolution_y_size, kColorBitNum);

  //====================================================
  //DXライブラリの初期化処理
  //====================================================
  if (DxLib_Init() == -1) {
    return -1;          // エラーが起きたら直ちに終了
  }

  //====================================================
  //TaskManagerクラスを生成
  //====================================================
  TaskManager* task_manager = new TaskManager();
  //生成に失敗した場合、アプリを終了する
  if (task_manager == nullptr) {
    DxLib_End();
    return -1;
  }

  //====================================================
  //LevelChangerクラスを生成
  //====================================================
  LevelChanger* level_changer = new LevelChanger();

  //====================================================
  //タスクIDを設定する
  //====================================================

  level_changer->SetTaskManager(task_manager);

  //====================================================
  //TaskManagerにタスクを積む
  //====================================================
  task_manager->AddTask(level_changer);

  //====================================================
  //メッセージループ
  //
  //メッセージが終了でない間ループする
  //====================================================
  MSG msg = { 0 };
  while (true) {
    //====================================================
    //終了メッセージを受け取ったなら、ループを抜ける
    //====================================================
    if (msg.message == WM_QUIT) {
      break;
    }

    //====================================================
    //メッセージが存在するなら
    //メッセージ処理を実行する
    //====================================================
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      //====================================================
      //仮想キーメッセージを文字メッセージへ変換
      //====================================================
      TranslateMessage(&msg);

      //====================================================
      //ウィンドウプロシージャにメッセージを転送
      //====================================================
      DispatchMessage(&msg);
    }
    //====================================================
    //メッセージが来ていない時はメインループ処理
    //====================================================
    else {
      //====================================================
      //メインループである事を文字出力で確認
      //====================================================
      //DrawString(kXcoordinate, kYMainroop, "MainLoop", Cr);
      //DEBUG_PRINT(メインループ);

      //メインループに入った時の時間を取得する
      int start_time = GetNowCount();

      //====================================================
      // 積んであるタスクの1フレームの処理を実行する
      //====================================================
      task_manager->UpdateTask(float_time);

      //====================================================
      // 積んであるタスクの1フレームの描画処理を実行する
      //====================================================

      //描画する
      task_manager->RenderTask();

      //メインループの処理が終わった時の時間を取得する
      int end_time = GetNowCount();

      //終わった時間から始まった時間を引き、経過した時間を取得
      int elapsed_time = end_time - start_time;

      //終わった時間を、次の開始時間に設定する
      start_time = end_time;

      //前回の経過した時間を秒に変換し、タスクマネージャーの１フレームの処理に渡す
      float_time = elapsed_time / kNumConvertSecond;
    }
  }

  //====================================================
  // 積んであるタスクを降ろす
  //====================================================
  task_manager->UnloadTask(level_changer->GetId());

  //TaskManagerクラスのメモリを開放する
  delete task_manager;
  task_manager = nullptr;

  //LevelChangerクラスのメモリを開放する
  delete level_changer;
  level_changer = nullptr;

  //ＤＸライブラリ使用の終了処理
  DxLib_End();

  //ゲーム情報を解放する
  game_info->ReleaseInstance();

  //DestroyConsole関数を呼び出す
  //log_console.DestroyConsole();

  //====================================================
  //ソフトの終了
  //====================================================
  return 0;
}