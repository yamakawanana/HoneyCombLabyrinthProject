#pragma once
#include "System/Task/Task.h"
#include "Game/GameStateEventInterface.h"

/// <summary>
/// GameStateクラス
/// </summary>
class GameState : public Task {
public:

  /// <summary>
  /// フェーズの種類
  /// </summary>
  enum PhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreraration,

    /// <summary>
    /// プレイ中
    /// </summary>
    kPlaying,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kFinish,

    /// <summary>
    /// フェーズの種類の最大数
    /// </summary>
    kMax,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  GameState(TaskId task_id, GameStateEventInterface& event_interface);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GameState();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name="time">最後のフレームを完了するのに要した時間 (秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// SetPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetPhaseType(PhaseType type);

  /// <summary>
  /// GetPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PhaseType GetPhaseType();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// ゲームステートのイベントインターフェース
  /// </summary>
  GameStateEventInterface& event_interface_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// <summary>
  /// 残り時間
  /// </summary>
  int time_remaining_;

  /// <summary>
  /// 蓄積時間
  /// </summary>
  float accumulation_time_;
};
