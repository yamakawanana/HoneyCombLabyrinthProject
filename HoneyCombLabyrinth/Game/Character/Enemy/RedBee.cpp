#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "Game//Character/Enemy/RedBee.h"
#include "System/LogConsole.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 赤いハチが進むルートを格納する配列の要素数を定数kRedBeeRoadElementNumberに格納する
  /// </summary>
  static const int kRedBeeRoadElementNumber = 4;

  /// <summary>
  /// ランダムな整数を生成する時の整数の上限値を定数kRandomNumberに格納する
  /// </summary>
  static const int kRandomNumber = 4;

  /// <summary>
  //進むルートの座標1点目のX位置を定数kFirstRoadXに格納
  /// <summary>
  static const int kFirstRoadX = 10;

  /// <summary>
  //進むルートの座標1点目のY位置を定数kFirstRoadYに格納
  /// <summary>
  static const int kFirstRoadY = 1;

  /// <summary>
  //進むルートの座標2点目のX位置を定数kSecondRoadXに格納
  /// <summary>
  static const int kSecondRoadX = 8;

  /// <summary>
  //進むルートの座標2点目のY位置を定数kSecondRoadYに格納
  /// <summary>
  static const int kSecondRoadY = 3;

  /// <summary>
  //進むルートの座標3点目のX位置を定数kThirdRoadXに格納
  /// <summary>
  static const int kThirdRoadX = 12;

  /// <summary>
  //進むルートの座標3点目のY位置を定数kThirdRoadYに格納
  /// <summary>
  static const int kThirdRoadY = 3;

  /// <summary>
  //進むルートの座標4点目のX位置を定数kFourthRoadXに格納
  /// <summary>
  static const int kFourthRoadX = 14;

  /// <summary>
  //進むルートの座標4点目のY位置を定数kFourthRoadYに格納
  /// <summary>
  static const int kFourthRoadY = 1;

  /// <summary>
  //待ち時間を定数kWaitTimeに格納
  /// <summary>
  static const float kWaitTime = 2.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
RedBee::RedBee(TaskId task_id, TaskManager* task_manager, CharacterControllerEventInterface& controller_event_interface, EnemyEventInterface& enemy_event_interface, CharacterEventInterface& event_interface)
  : EnemyBase(task_id, task_manager, controller_event_interface, enemy_event_interface, event_interface)
  , thinking_phase_(kNone)
  , direction_(Field::DirectionType::kMax)
  , accumulation_time_(0.0f)
  , is_finish_(false)
  , enemy_root_num_(0)
  , change_amount_(1)
  , enemy_direction_type_(kPlus)
{
  DEBUG_PRINT(RedBeeのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
RedBee::~RedBee() {
  DEBUG_PRINT(RedBeeのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void RedBee::UpdateFrame(float time) {
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
/// 移動可能な向きの配列から移動方向を選択する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RedBee::DecideDirection() {

  //決定した移動先の向きとする
  //direction_ = ;

  DEBUG_PRINT(移動先を決定した);
}

/// <summary>
/// 決まった方向に移動する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void RedBee::MoveEnemy() {
  // 赤いハチが移動するルートのX位置とY位置を配列に格納する
  int red_bee_root_x[kRedBeeRoadElementNumber] = { kFirstRoadX , kSecondRoadX, kThirdRoadX, kFourthRoadX };
  int red_bee_root_y[kRedBeeRoadElementNumber] = { kFirstRoadY , kSecondRoadY, kThirdRoadY, kFourthRoadY };

  switch (enemy_direction_type_) {

  //敵の移動の向きが正の向きの時
  case EnemyDirectionType::kPlus: {

    // 移動位置を更新
    SetXPosition(red_bee_root_x[enemy_root_num_]);
    SetYPosition(red_bee_root_y[enemy_root_num_]);

    enemy_root_num_ += change_amount_;

    if (enemy_root_num_ >= kRedBeeRoadElementNumber) {
      enemy_root_num_ = 0;
    }

    break;
  }

  //敵の移動の向きが負の向きの時
  case EnemyDirectionType::kMinus: {

    // 移動位置を更新
    SetXPosition(red_bee_root_x[enemy_root_num_]);
    SetYPosition(red_bee_root_y[enemy_root_num_]);

    enemy_root_num_ -= change_amount_;

    if (enemy_root_num_ < 0) {
      enemy_root_num_ = kRedBeeRoadElementNumber -1;
    }

    break;
  }
  }

  // ランダムな数字のkRandomNumberが出た時だけ、周回する方向を変える
  //int random_index = CreateRandomNum();

  //if (random_index == kRandomNumber) {
  //  if (enemy_direction_type_ == kPlus) {
  //    enemy_direction_type_ = kMinus;
  //  }
  //  else {
  //    enemy_direction_type_ = kPlus;
  //  }
  //}

  //DEBUG_PRINT_VAR(enemy_root_num_);

  //ぶつかった時の処理を実行する
  enemy_controller_.HitCharacter();

}

/// <summary>
/// ランダムな整数を作る
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int RedBee::CreateRandomNum() {

  //乱数を生成する
  std::mt19937 gen(std::random_device{}());
  //ランダムに数字を出す
  std::uniform_int_distribution<int> dist(1, kRandomNumber);

  int random_index = dist(gen);

  //DEBUG_PRINT_VAR(random_index);

  return random_index;
}