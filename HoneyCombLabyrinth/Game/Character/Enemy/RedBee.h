#pragma once
#include "Game/Character/Enemy/EnemyBase.h"
#include "Game/Interface/EnemyEventInterface.h"

/// <summary>
/// RedBeeクラス
/// </summary>
class RedBee : public EnemyBase {
public:
  /// <summary>
  /// 進む方向の種類
  /// </summary>
  enum EnemyDirectionType {
    /// <summary>
    /// 正の向き
    /// </summary>
    kPlus,

    /// <summary>
    /// 負の向き
    /// </summary>
    kMinus,
  };


  /// <summary>
  /// 思考フェーズの種類
  /// </summary>
  enum ThinkingPhaseType {
    /// <summary>
    /// 何もしていない
    /// </summary>
    kNone,

    /// <summary>
    /// 周囲の移動箇所確認
    /// </summary>
    kCheckingAround,

    /// <summary>
    /// 行く先を決定
    /// </summary>
    kFinding,

    /// <summary>
    /// 移動
    /// </summary>
    kMoving,

    /// <summary>
    /// 次の移動までの待機
    /// </summary>
    kWaiting,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  RedBee(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~RedBee();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// 移動可能な向きの配列から１つ選択する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void DecideDirection();

  /// <summary>
  /// 決まった方向に移動する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void MoveEnemy();

  /// <summary>
  /// 次の移動まで待機する時間をランダムに作る
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  int CreateRandomNum();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //現在のフェーズ
  /// </summary>
  ThinkingPhaseType thinking_phase_;

  /// </summary>
  //決定した移動先の向き
  /// </summary>
  Field::DirectionType direction_;

  /// <summary>
  /// 累積時間
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 終了の有無
  /// </summary>
  bool is_finish_;

  /// <summary>
  /// 進むルートの要素番号
  /// </summary>
  int enemy_root_num_;

  /// <summary>
  /// 敵が移動する時の変化量
  /// </summary>
  int change_amount_;

  /// <summary>
  /// 敵が移動する時の進む方向
  /// </summary>
  EnemyDirectionType enemy_direction_type_;
};
