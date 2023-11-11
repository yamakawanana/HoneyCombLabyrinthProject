#include <iostream>
#include "Game/GameState.h"
#include "System/LogConsole.h"
#include "Game/GameStateEventInterface.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const int kLimitTime = 31;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameState::GameState(TaskId task_id, GameStateEventInterface& event_interface)
  : Task(task_id)
  , event_interface_(event_interface)
  , now_phase_(PhaseType::kPreraration)
  , time_remaining_(kLimitTime)
  , accumulation_time_(0.0f)
{
  DEBUG_PRINT(GameStateのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
GameState::~GameState() {
  DEBUG_PRINT(GameStateのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理　UpdateFrame関数の定義
/// </summary>
/// <param name="time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void GameState::UpdateFrame(float time) {
  //DEBUG_PRINT(GameStateクラスの毎フレーム更新処理);

  if (now_phase_ != kStop) {

    switch (now_phase_) {
      //フェーズが準備中フェーズの場合
    case kPreraration: {
      now_phase_ = kPlaying;
      DEBUG_PRINT(プレイ中フェーズに遷移);
      break;
    }
                     //フェーズがプレイ中フェーズの場合
    case kPlaying: {
      //前回の1Frameにかかった時間を累積時間に足す
      accumulation_time_ = accumulation_time_ + time;

      //累積時間が1秒以上だったら
      if (accumulation_time_ >= 1.0f) {
        //残り時間を-1する
        time_remaining_--;
        //累積時間をリセットする
        accumulation_time_ = 0.0f;
        //カウントダウンのイベント関数を呼ぶ
        event_interface_.CountRemainingTime(time_remaining_);

        //残り時間が0以下になったら
        if (time_remaining_ <= 0) {
          //タイムオーバーのイベント関数を呼ぶ
          //event_interface_.TimeUp();
          now_phase_ = kFinish;
          DEBUG_PRINT(終了フェーズに遷移);
        }
      }

      break;
    }
                 //フェーズが終了フェーズの場合
    case kFinish: {

      break;
    }
    }
  }
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void GameState::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
GameState::PhaseType GameState::GetPhaseType() {
  return now_phase_;
}