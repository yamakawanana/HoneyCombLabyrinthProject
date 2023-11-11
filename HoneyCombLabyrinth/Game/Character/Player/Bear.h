#pragma once
#include <array>
#include "System/Character.h"
#include "Game/Field.h"

/// <summary>
/// Bearクラス
/// </summary>
class Bear : public Character {
public:

  /// <summary>
  /// クマのグラフィックハンドルの配列の要素数を定数kBearElementNumberに格納する
  /// </summary>
  static const int kBearElementNumber = 3;

  /// <summary>
  //クマの状態のBearType型を定義する
  /// <summary>
  enum BearType {
    /// <summary>
    /// 普通の歩いている状態
    /// </summary>
    kWalking,

    /// <summary>
    /// ハチに刺された直後の状態
    /// </summary>
    kAttacked,

    /// <summary>
    /// 泣きながら走っている
    /// </summary>
    kRunning,

    /// <summary>
    /// 移動の待ち時間状態
    /// </summary>
    kWait,

    /// <summary>
    /// 行き止まりで止まっている状態
    /// </summary>
    kStopInDeadEnd,

    /// <summary>
    /// 行き止まりで止まっている時にクマさんが追いつき笑顔になった状態
    /// </summary>
    kSmile,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Bear(TaskId task_id, TaskManager* task_manager, std::array<int, kBearElementNumber> bear_handle, std::array<int, kBearElementNumber> damage_bear_handle);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Bear();

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
  /// GetBearGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>グラフィックハンドル</returns>
  int GetBearGrHandle(int element_num);

  /// <summary>
  /// SetBearGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBearGrHandle(int bear_handle);

  /// <summary>
  /// GetDamageBearGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetDamageBearGrHandle(int element_num);

  /// <summary>
  /// SetDamageBearGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  void SetDamageBearGrHandle(std::array<int, kBearElementNumber> damage_duck_handle);

  /// <summary>
  /// GetSmileBearHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetSmileBearHandle();

  /// <summary>
  /// SetSmileBearHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetSmileBearHandle(int gr_handle);

  /// <summary>
  /// SetDuckXPos関数の宣言
  /// </summary>
  /// <param = "duck_x">アヒルさんの居たX位置</param>
  /// <returns>なし</returns>
  void SetDuckXPos(int duck_x);

  /// <summary>
  /// SetDuckYPos関数の宣言
  /// </summary>
  /// <param = "duck_y">アヒルさんの居たY位置</param>
  /// <returns>なし</returns>
  void SetDuckYPos(int duck_y);

  /// <summary>
  /// SetNowDuckXPos関数の宣言
  /// </summary>
  /// <param = "duck_x">アヒルさんの現在のX位置</param>
  /// <returns>なし</returns>
  void SetNowDuckXPos(int duck_x);

  /// <summary>
  /// SetNowDuckYPos関数の宣言
  /// </summary>
  /// <param = "duck_y">アヒルさんの現在のY位置</param>
  /// <returns>なし</returns>
  void SetNowDuckYPos(int duck_y);

  /// <summary>
  /// 一番近い行き止まりの経路を設定する関数
  /// </summary>
  /// <param = "walk_distances">一番近い行き止まりの経路の配列</param>
  /// <returns>なし</returns>
  void SetNearestRoute(Field::Pos* nearest_route, int route_count);

  /// <summary>
  /// SetBearType関数の宣言
  /// </summary>
  /// <param>現在のステータス</param>
  /// <returns>なし</returns>
  void SetBearType(BearType status);

  /// <summary>
  /// GetBearType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>現在のステータス</returns>
  BearType GetBearType();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// グラフィックハンドル
  /// </summary>
  //int bear_handle_;

  /// <summary>
  /// クマのグラフィックハンドル
  /// </summary>
  std::array<int, kBearElementNumber> bear_handle_;

  /// <summary>
  /// ダメージを受けたクマのグラフィックハンドル
  /// </summary>
  std::array<int, kBearElementNumber> damage_bear_handle_;

  /// <summary>
  /// 笑顔のクマのグラフィックハンドル
  /// </summary>
  int smile_bear_handle_;

  /// <summary>
  /// 1フレームあたりのアニメーションの変化量
  /// </summary>
  float change_amount_;

  /// </summary>
  //クマの状態の種類
  /// </summary>
  BearType bear_type_;

  /// </summary>
  //アヒルさんの居たX位置
  /// </summary>
  int duck_x_;

  /// </summary>
  //アヒルさんの居たY位置
  /// </summary>
  int duck_y_;

  /// </summary>
  //アヒルさんの現在のX位置
  /// </summary>
  int duck_now_x_;

  /// </summary>
  //アヒルさんの現在のY位置
  /// </summary>
  int duck_now_y_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 一番近い行き止まりへの経路を保存する配列
  /// </summary>
  Field::Pos* nearest_route_;

  /// <summary>
  /// 一番近い行き止まりまでかかる歩数
  /// </summary>
  int route_count_;

  /// <summary>
  /// ダメージを受けた時に使う累積時間（秒）
  /// </summary>
  float damage_accumulation_time_;

  /// <summary>
  /// 笑顔の時に使う累積時間（秒）
  /// </summary>
  float smile_accumulation_time_;
};