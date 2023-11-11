#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "Game/Character/Enemy/YellowBee.h"
#include "System/LogConsole.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 黄色いハチが進むルートを格納する配列の要素数を定数kYellowBeeRoadElementNumberに格納する
  /// </summary>
  static const int kYellowBeeRoadElementNumber = 4;

  /// <summary>
  /// ランダムな整数を生成する時の整数の上限値を定数kRandomNumberに格納する
  /// </summary>
  static const int kRandomNumber = 4;

  /// <summary>
  //進むルートの座標1点目のX位置を定数kFirstRoadXに格納
  /// <summary>
  static const int kFirstRoadX = 14;

  /// <summary>
  //進むルートの座標1点目のY位置を定数kFirstRoadYに格納
  /// <summary>
  static const int kFirstRoadY = 5;

  /// <summary>
  //進むルートの座標2点目のX位置を定数kSecondRoadXに格納
  /// <summary>
  static const int kSecondRoadX = 10;

  /// <summary>
  //進むルートの座標2点目のY位置を定数kSecondRoadYに格納
  /// <summary>
  static const int kSecondRoadY = 5;

  /// <summary>
  //進むルートの座標3点目のX位置を定数kThirdRoadXに格納
  /// <summary>
  static const int kThirdRoadX = 6;

  /// <summary>
  //進むルートの座標3点目のY位置を定数kThirdRoadYに格納
  /// <summary>
  static const int kThirdRoadY = 5;

  /// <summary>
  //進むルートの座標4点目のX位置を定数kFourthRoadXに格納
  /// <summary>
  static const int kFourthRoadX = 4;

  /// <summary>
  //進むルートの座標4点目のY位置を定数kFourthRoadYに格納
  /// <summary>
  static const int kFourthRoadY = 3;

  /// <summary>
  //待ち時間を定数kWaitTimeに格納
  /// <summary>
  static const float kWaitTime = 2.2f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
YellowBee::YellowBee(TaskId task_id, TaskManager* task_manager)
  : EnemyBase(task_id, task_manager)
  , thinking_phase_(kNone)
  , direction_(Field::DirectionType::kMax)
  , accumulation_time_(0.0f)
  , is_finish_(false)
  , enemy_root_num_(0)
  , change_amount_(1)
{
  DEBUG_PRINT(YellowBeeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
YellowBee::~YellowBee() {
  DEBUG_PRINT(YellowBeeのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void YellowBee::UpdateFrame(float time) {
  if (now_phase_ != kStop) {
    // DEBUG_PRINT(YellowBeeの毎フレーム更新処理);

    bool result = false;

    switch (thinking_phase_) {

      //フェーズが何もしていないフェーズの場合
    case ThinkingPhaseType::kNone: {

      thinking_phase_ = kMoving;
      DEBUG_PRINT(移動フェーズに遷移);

      break;
    }
      //フェーズが移動フェーズの場合
    case ThinkingPhaseType::kMoving: {
      MoveEnemy();
      //移動フェーズが終わったら、次の移動までの待機フェーズに遷移する
      thinking_phase_ = kWaiting;
      //DEBUG_PRINT(次の移動までの待機フェーズに遷移);
      break;
    }
      //フェーズが次の移動までの待機の場合
    case ThinkingPhaseType::kWaiting: {
      accumulation_time_ = accumulation_time_ + time;
      //float wait_time = CreateRandomNum();
      if (kWaitTime <= accumulation_time_) {
        accumulation_time_ = 0.0f;
        //次の移動までの待機が終わったら、周囲の移動箇所確認フェーズに遷移
        thinking_phase_ = kMoving;
        //DEBUG_PRINT(移動フェーズに遷移);
      }
      break;
    }
    }
  }
    Character::UpdateFrame(time);
}

/// <summary>
/// 移動先を決定する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void YellowBee::DecideDirection() {

  //direction_ = event_interface_.DecidePlayerEnemyMinDistance();

  DEBUG_PRINT(移動先を決定した);
}

/// <summary>
/// 決まった方向に移動する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void YellowBee::MoveEnemy() {
  //黄色いハチが移動するルートのX位置とY位置を配列に格納する
  int yellow_bee_root_x[kYellowBeeRoadElementNumber] = { kFirstRoadX , kSecondRoadX, kThirdRoadX, kFourthRoadX };
  int yellow_bee_root_y[kYellowBeeRoadElementNumber] = { kFirstRoadY , kSecondRoadY, kThirdRoadY, kFourthRoadY };

  //配列に格納されている位置に順番に進む
  SetXPosition(yellow_bee_root_x[enemy_root_num_]);
  SetYPosition(yellow_bee_root_y[enemy_root_num_]);

  enemy_root_num_ = enemy_root_num_ + change_amount_;

  if (enemy_root_num_ >= kYellowBeeRoadElementNumber - 1) {
    change_amount_ *= -1;
  }
  else if (enemy_root_num_ <= 0) {
    change_amount_ *= -1;
  }

  //ぶつかった時の処理を実行する
  enemy_controller_.HitCharacter();

}

/// <summary>
/// ランダムな整数を作る
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int YellowBee::CreateRandomNum() {

  //乱数を生成する
  std::mt19937 gen(std::random_device{}());
  //ランダムに数字を出す
  std::uniform_int_distribution<int> dist(1, kRandomNumber);

  int random_index = dist(gen);

  //DEBUG_PRINT_VAR(random_index);

  return random_index;
}