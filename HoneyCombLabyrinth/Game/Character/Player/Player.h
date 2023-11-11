#pragma once
#include <array>
#include "System/Character.h"

/// <summary>
/// Playerクラス
/// </summary>
class Player : public Character {
public:

  /// <summary>
  /// アヒルのグラフィックハンドルの配列の要素数を定数kDuckElementNumberに格納する
  /// </summary>
  static const int kDuckElementNumber = 3;

  /// <summary>
  /// ダメージを受けたアヒルのグラフィックハンドルの配列の要素数を定数kDamageDuckElementNumberに格納する
  /// </summary>
  static const int kDamageDuckElementNumber = 6;

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Player(TaskId task_id, TaskManager* task_manager, CharacterEventInterface& event_interface, std::array<int, kDuckElementNumber> duck_handle);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Player();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

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
  int GetGrHandle(int element_num);

  /// <summary>
  /// SetGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGrHandle(int gr_handle);

  /// <summary>
  /// GetDamageGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetDamageGrHandle(int element_num);

  /// <summary>
  /// SetDamageGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  void SetDamageGrHandle(std::array<int, kDamageDuckElementNumber> damage_duck_handle);

  /// <summary>
  /// ダメージを受けたプレイヤーを表示する処理
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <returns>なし</returns>
  void DrawDamagedPlayer(float x, float y);

  /// <summary>
  /// CheckIsDamagedAnimationEnd関数の宣言
  /// </summary>
  /// <param>ダメージを受けたアニメーションの終了有無</param>
  /// <returns>なし</returns>
  bool CheckIsDamagedAnimationEnd();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// グラフィックハンドル
  /// </summary>
  //int gr_handle_;

  /// <summary>
  /// アヒルのグラフィックハンドル
  /// </summary>
  std::array<int, kDuckElementNumber> gr_handle_;

  /// <summary>
  /// 1フレームあたりのアニメーションの変化量
  /// </summary>
  float change_amount_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// ダメージを受けたアヒルのグラフィックハンドル
  /// </summary>
  std::array<int, kDamageDuckElementNumber> gr_damage_handle_;

  /// <summary>
  /// ダメージを受けた時のアニメーションで使う累積時間（秒）
  /// </summary>
  float damage_accumulation_time_;

  /// <summary>
  /// ダメージを受けた時のアニメーションの終了有無
  /// </summary>
  bool is_damage_animation_end_;
};
