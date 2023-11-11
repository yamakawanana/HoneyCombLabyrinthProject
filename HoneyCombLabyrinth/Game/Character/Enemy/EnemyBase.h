#pragma once
#include <vector>
#include "System/Character.h"
#include "Game/Interface/EnemyEventInterface.h"
#include "Game/Field.h"
#include "Game/Controller/EnemyController.h"

/// <summary>
/// EnemyBaseクラス
/// </summary>
class EnemyBase : public Character {
public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  EnemyBase(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~EnemyBase();

  /// 毎フレーム描画処理
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// GetGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetGrHandle();

  /// <summary>
  /// SetGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGrHandle(int gr_handle);

  /// <summary>
  /// 敵キャラクターイベントインターフェースを設定する関数
  /// </summary>
  /// <param = "event_interface">敵キャラクターイベントインターフェースのポインタ</param>
  /// <returns>なし</returns>
  void SetEnemyEventInterface(EnemyEventInterface& event_interface);

  /// <summary>
  /// 歩ける範囲を設定する関数
  /// </summary>
  /// <param = "walk_distances">歩ける範囲のリスト</param>
  /// <returns>なし</returns>
  void SetWalkDistance(std::vector<Field::DirectionType> walk_distances);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// グラフィックハンドル
  /// </summary>
  int enemy_gr_handle_;

  /// <summary>
  /// 1フレームあたりのアニメーションの変化量
  /// </summary>
  int change_amount_;

protected:

  /// <summary>
  /// 敵コントローラ
  /// </summary>
  EnemyController enemy_controller_;

  /// <summary>
  /// フェーズの種類
  /// </summary>
  //EnemyEventInterface& event_interface_;

  /// <summary>
  /// 歩ける範囲を保存する配列
  /// </summary>
  std::vector<Field::DirectionType> walk_distances_;
};
