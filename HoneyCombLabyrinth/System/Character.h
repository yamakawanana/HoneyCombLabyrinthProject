#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Interface/CharacterEventInterface.h"

/// <summary>
/// Characterクラス
/// </summary>
class Character : public Task {
public:
  /// <summary>
  /// 敵の数を定数kRedBeeNumに格納する
  /// </summary>
  static const int kRedBeeNum = 1;

  /// <summary>
  /// 敵の数を定数kYellowBeeNumに格納する
  /// </summary>
  static const int kYellowBeeNum = 1;


  /// <summary>
  //キャラクターの種類の列挙型CharacterType型を定義する
  /// <summary>
  enum CharacterType {
    /// <summary>
    /// プレイヤー
    /// </summary>
    kPlayer,

    /// <summary>
    /// クマ
    /// </summary>
    kBear,

    /// <summary>
    /// 赤いハチ
    /// </summary>
    kRedBee,

    /// <summary>
    /// 黄色いハチ
    /// </summary>
    kYellowBee,
  };


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
    /// クマが走っている状態
    /// </summary>
    kBearRunning,

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
  //方向の種類の列挙型DirectionType型を定義する
  /// <summary>
  enum DirectionType {
    /// <summary>
    /// 右上
    /// </summary>
    kRightUp,

    /// <summary>
    /// 右下
    /// </summary>
    kRightDown,

    /// <summary>
    /// 左上
    /// </summary>
    kLeftUp,

    /// <summary>
    /// 左下
    /// </summary>
    kLeftDown,

    /// <summary>
    /// 右
    /// </summary>
    kRight,

    /// <summary>
    /// 左
    /// </summary>
    kLeft,

    /// <summary>
    /// 何もない
    /// </summary>
    kNone,
  };


  /// <summary>
  //ステータスの種類
  /// <summary>
  enum StatusType {
    /// <summary>
    /// 元気
    /// </summary>
    kAlive,

    /// <summary>
    /// 死んだ
    /// </summary>
    kDead,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Character(TaskId task_id, TaskManager* task_manager, CharacterEventInterface& event_interface);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~Character();

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void InitCharacter(int gr_handle);

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// SetXPosition関数の宣言
  /// </summary>
  /// <param = "x_coordinate">X座標</param>
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
  /// <param = "y_coordinate">Y座標</param>
  /// <returns>なし</returns>
  void SetYPosition(int y_coordinate);

  /// <summary>
  /// GetYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Y座標</returns>
  int GetYPosition();

  /// <summary>
  /// SetWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetWidth(int size_x);

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// SetHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHeight(int size_y);

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// SetHalfWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetHalfWidth(float size_half_x);

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// SetHalfHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHalfHeight(float size_half_y);

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// <summary>
  /// SetCharacterType関数の宣言
  /// </summary>
  /// <param = "character_type">キャラクターの種類</param>
  /// <returns>なし</returns>
  void SetCharacterType(CharacterType character_type);

  /// <summary>
  /// GetCharacterType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キャラクターの種類</returns>
  CharacterType GetCharacterType();

  /// <summary>
  /// SetDirectionType関数の宣言
  /// </summary>
  /// <param = "direction">方向の種類</param>
  /// <returns>なし</returns>
  void SetDirectionType(DirectionType direction);

  /// <summary>
  /// GetDirectionType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>方向の種類</returns>
  DirectionType GetDirectionType();

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

  /// <summary>
  /// SetDisplayXPosition関数の宣言
  /// </summary>
  /// <param = "display_x_coordinate">表示用のX座標</param>
  /// <returns>なし</returns>
  void SetDisplayXPosition(float display_x_coordinate);

  /// <summary>
  /// GetDisplayXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のX座標</returns>
  float GetDisplayXPosition();

  /// <summary>
  /// SetDisplayYPosition関数の宣言
  /// </summary>
  /// <param = "display_y_coordinate">表示用のY座標</param>
  /// <returns>なし</returns>
  void SetDisplayYPosition(float display_y_coordinate);

  /// <summary>
  /// GetDisplayYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のY座標</returns>
  float GetDisplayYPosition();

  /// <summary>
  /// CheckIsMoving関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>移動中ならtrue、移動中でなければfalse</returns>
  bool CheckIsMoving();

  /// <summary>
  /// SetMovingSpeed関数の宣言
  /// </summary>
  /// <param = "moving_speed">移動時のスピード</param>
  /// <returns>なし</returns>
  void SetMovingSpeed(float moving_speed);

  /// <summary>
  /// GetMovingSpeed関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>移動時のスピード</returns>
  float GetMovingSpeed();

  /// <summary>
  /// SetXPositions関数の宣言
  /// </summary>
  /// <param = "x">x_positions_に追加したいX位置の整数</param>
  /// <param = "num">x_positions_の何番目の要素かを指定する整数</param>
  /// <returns>なし</returns>
  void SetXPositions(int x, int num);

  /// <summary>
  /// GetXPositions関数の宣言
  /// </summary>
  /// <param>何番目の要素かを指定する整数</param>
  /// <returns>x_positions_のi番目の要素の整数</returns>
  //int GetXPositions(int i);

  /// <summary>
  /// SetYPositions関数の宣言
  /// </summary>
  /// <param = "y">y_positions_に追加したいX位置の整数</param>
  /// <param = "num">y_positions_の何番目の要素かを指定する整数</param>
  /// <returns>なし</returns>
  void SetYPositions(int y, int num);

  /// <summary>
  /// GetYPositions関数の宣言
  /// </summary>
  /// <param>何番目の要素かを指定する整数</param>
  /// <returns>y_positions_のi番目の要素の整数</returns>
  //int GetYPositions(int i);

  /// <summary>
  /// SetHp関数の宣言
  /// </summary>
  /// <param = "hp">HP</param>
  /// <returns>なし</returns>
  void SetHp(int hp);

  /// <summary>
  /// GetHp関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>hp_</returns>
  int GetHp();

  /// <summary>
  /// SetAttackPower関数の宣言
  /// </summary>
  /// <param>攻撃力</param>
  /// <returns>なし</returns>
  void SetAttackPower(int attack_power);

  /// <summary>
  /// GetAttackPower関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>attack_power_</returns>
  int GetAttackPower();

  /// <summary>
  /// SetDefensePower関数の宣言
  /// </summary>
  /// <param>防御力</param>
  /// <returns>なし</returns>
  void SetDefensePower(int defense_power);

  /// <summary>
  /// GetDefensePower関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>defense_power_</returns>
  int GetDefensePower();

  /// <summary>
  /// Attack関数の宣言
  /// </summary>
  /// <param>相手キャラクター(参照)</param>
  /// <returns>なし</returns>
  void Attack(Character& character);

  /// <summary>
  /// IncurDamage関数の宣言
  /// </summary>
  /// <param>相手キャラクター(参照)</param>
  /// <returns>なし</returns>
  void IncurDamage();

  /// <summary>
  /// CheckIsDead関数の宣言
  /// </summary>
  /// <param>現在のステータス</param>
  /// <returns>なし</returns>
  bool CheckIsDead();

  /// <summary>
  /// SetStatusType関数の宣言
  /// </summary>
  /// <param>現在のステータス</param>
  /// <returns>なし</returns>
  void SetStatusType(StatusType status);

  /// <summary>
  /// GetStatusType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>現在のステータス</returns>
  StatusType GetStatusType();

  /// <summary>
  /// SetHitPos関数の宣言
  /// </summary>
  /// <param = "x">プレイヤーがハチとぶつかった時のX位置</param>
  /// <param = "y">プレイヤーがハチとぶつかった時のY位置</param>
  /// <returns>なし</returns>
  void SetHitPos(int x, int y);

  /// <summary>
  /// GetHitXPos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーがハチとぶつかった時のX位置</returns>
  int GetHitXPos();

  /// <summary>
  /// GetHitYPos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーがハチとぶつかった時のY位置</returns>
  int GetHitYPos();

  /// <summary>
  /// SetBearHitPos関数の宣言
  /// </summary>
  /// <param = "x">クマがハチとぶつかった時のX位置</param>
  /// <param = "y">クマがハチとぶつかった時のY位置</param>
  /// <returns>なし</returns>
  void SetBearHitPos(int x, int y);

  /// <summary>
  /// GetBearHitXPos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>クマがハチとぶつかった時のX位置</returns>
  int GetBearHitXPos();

  /// <summary>
  /// GetBearHitYPos関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>クマがハチとぶつかった時のY位置</returns>
  int GetBearHitYPos();

  /// <summary>
  /// GetPlayerIsDead関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>プレイヤーが死んだかの有無</returns>
  bool GetPlayerIsDead();

  /// <summary>
  /// SetPlayerIsDead関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayerIsDead();

  /// <summary>
  /// GetBearIsAttacked関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>クマがハチに刺されたかの有無</returns>
  bool GetBearIsAttacked();

  /// <summary>
  /// SetBearIsAttacked関数の宣言
  /// </summary>
  /// <param>クマがハチに刺されたかの有無</param>
  /// <returns>なし</returns>
  void SetBearIsAttacked(bool bear_is_attacked);

protected:
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

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //キャラクターの種類
  /// </summary>
  CharacterType character_type_;

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

  /// </summary>
  //現在の向き
  /// </summary>
  DirectionType now_direction_;

  /// <summary>
  /// 表示用のX座標
  /// </summary>
  float display_x_coordinate_;

  /// <summary>
  /// 表示用のY座標
  /// </summary>
  float display_y_coordinate_;

  /// <summary>
  /// 移動中かの有無
  /// </summary>
  bool is_moving_;

  /// <summary>
  /// 移動時のスピード(足しこむ値)
  /// </summary>
  float moving_speed_;

  /// </summary>
  //複数のX座標を保存するための配列
  /// </summary>
  //int x_positions_[kRedBeeNum];

  /// </summary>
  //複数のY座標を保存するための配列
  /// </summary>
  //int y_positions_[kRedBeeNum];

  /// <summary>
  /// キャラクターイベントインターフェース
  /// </summary>
  CharacterEventInterface& event_interface_;

  /// <summary>
  /// ヒットポイント
  /// </summary>
  int hp_;

  /// <summary>
  /// 攻撃力
  /// </summary>
  int attack_power_;

  /// <summary>
  /// 防御力
  /// </summary>
  int defense_power_;

  /// <summary>
  /// 現在のステータス
  /// </summary>
  StatusType status_type_;

  /// <summary>
  /// ハチとプレイヤーがぶつかった時のX位置
  /// </summary>
  int hit_x_;

  /// <summary>
  /// ハチとプレイヤーがぶつかった時のY位置
  /// </summary>
  int hit_y_;

  /// <summary>
  /// プレイヤーの死亡の有無を受け取る変数
  /// </summary>
  bool player_is_dead_;

  /// <summary>
  /// ハチとクマがぶつかった時のX位置
  /// </summary>
  int bear_hit_x_;

  /// <summary>
  /// ハチとクマがぶつかった時のY位置
  /// </summary>
  int bear_hit_y_;

  /// <summary>
  /// クマがハチに刺されたかの有無を受け取る変数
  /// </summary>
  bool bear_is_attacked_;
};
