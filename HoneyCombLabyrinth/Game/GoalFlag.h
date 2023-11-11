#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include <array>

/// <summary>
/// GoalFlagクラス
/// </summary>
class GoalFlag : public Task {
public:
  /// <summary>
  /// 旗のグラフィックハンドルの配列の要素数を定数kGoalElementNumberに格納する
  /// </summary>
  static const int kGoalElementNumber = 4;

  /// <summary>
  //フェーズの種類の列挙型PhaseType型を定義する
  /// <summary>
  enum PhaseType {

    /// <summary>
    /// 処理フェーズ
    /// </summary>
    kProcessing,

    /// <summary>
    /// 中断フェーズ
    /// </summary>
    kStop,
  };

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  GoalFlag(TaskId task_id, std::array<int, kGoalElementNumber> goal_handle);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~GoalFlag();

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name="gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void InitGoalFlag(int gr_handle);

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name="time">最後のフレームを完了するのに要した時間 (秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// 毎フレーム描画処理
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// SetXPosition関数の宣言
  /// </summary>
  /// <param="x_coordinate">X座標</param>
  /// <returns>なし</returns>
  void SetXPosition(int x_coordinate);

  /// <summary>
  /// GetXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>X座標</returns>
  int GetXPosition();

  /// <summary>
  /// SetYPosition関数の宣言
  /// </summary>
  /// <param="y_coordinate">Y座標</param>
  /// <returns>なし</returns>
  void SetYPosition(int y_coordinate);

  /// <summary>
  /// GetYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Y座標</returns>
  int GetYPosition();

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// <summary>
  /// SetGoalGrHandle関数の宣言
  /// </summary>
  /// <param = "goal_handle">ゴール旗のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGoalGrHandle(int goal_handle);

  /// <summary>
  /// GetGoalGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetGoalGrHandle(int element_num);

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

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// <summary>
  /// X座標
  /// </summary>
  int x_coordinate_;

  /// <summary>
  /// Y座標
  /// </summary>
  int y_coordinate_;

  /// <summary>
  /// 画像の幅
  /// </summary>
  int width_;

  /// <summary>
  /// 画像の高さ
  /// </summary>
  int height_;

  /// <summary>
  /// 画像の幅の半分
  /// </summary>
  float half_width_;

  /// <summary>
  /// 画像の高さの半分
  /// </summary>
  float half_height_;

  /// <summary>
  /// ゴール旗のグラフィックハンドル
  /// </summary>
  std::array<int, kGoalElementNumber> goal_handle_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;
};