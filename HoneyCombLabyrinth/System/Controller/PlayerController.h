#pragma once
#include <unordered_map>
#include "System/Task/Task.h"
#include "System/Character.h"
#include "System/Interface/CharacterControllerEventInterface.h"
#include "Game/Field.h"

/// <summary>
/// PlayerControllerクラス
/// </summary>
class PlayerController : public Task {
public:

  /// <summary>
  /// 前のフレームで押されたキーの要素数を定数kElementNumberに格納する
  /// </summary>
  static const int kElementNumber = 256;

  /// <summary>
  //キーの種類の列挙型KeyType型を定義する
  /// <summary>
  enum KeyType {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// 右上キー
    /// </summary>
    kRightUpKey,

    /// <summary>
    /// 右下キー
    /// </summary>
    kRightDownKey,

    /// <summary>
    /// 左上キー
    /// </summary>
    kLeftUpKey,

    /// <summary>
    /// 左下キー
    /// </summary>
    kLeftDownKey,

    /// <summary>
    /// 上キー
    /// </summary>
    kUpKey,

    /// <summary>
    /// 下キー
    /// </summary>
    kDownKey,

    /// <summary>
    /// 右キー
    /// </summary>
    kRightKey,

    /// <summary>
    /// 左キー
    /// </summary>
    kLeftKey,

    /// <summary>
    /// キーの最大値
    /// </summary>
    kMaxKey,
  };


  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  PlayerController(TaskId task_id, CharacterControllerEventInterface& character_interface, Character& character);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~PlayerController();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// IsPushedUpKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>上キーを押されている：true、上キーを押されていない：false</returns>
  bool IsPushedUpKey();

  /// <summary>
  /// IsPushedDownKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>下キーを押されている：true、下キーを押されていない：false</returns>
  bool IsPushedDownKey();

  /// <summary>
  /// IsPushedRightUpKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>右上キーを押されている：true、右上キーを押されていない：false</returns>
  bool IsPushedRightUpKey(float time);

  /// <summary>
  /// IsPushedRightDownKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>右下キーを押されている：true、右下キーを押されていない：false</returns>
  bool IsPushedRightDownKey(float time);

  /// <summary>
  /// IsPushedLeftUpKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>左上キーを押されている：true、左上キーを押されていない：false</returns>
  bool IsPushedLeftUpKey(float time);

  /// <summary>
  /// IsPushedLeftDownKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>左下キーを押されている：true、左下キーを押されていない：false</returns>
  bool IsPushedLeftDownKey(float time);

  /// <summary>
  /// IsPushedRightKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>右キーを押されている：true、右キーを押されていない：false</returns>
  bool IsPushedRightKey(float time);

  /// <summary>
  /// IsPushedLeftKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>左キーを押されている：true、左キーを押されていない：false</returns>
  bool IsPushedLeftKey(float time);

private:

  /// <summary>
  /// IsPushedKey関数の宣言
  /// </summary>
  /// <param name = "up_key_code">上キーの種類up_key_code</param>
  /// <param name = "down_key_code">下キーの種類down_key_code</param>
  /// <param name = "key_type">指定されたキーの種類key_type</param>
  /// <param name = "pushed">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
  /// <returns>指定されたキーを押されている：true、押されていない：false</returns>
  bool IsPushedKey(int up_key_code, int down_key_code, int key_code, bool& pushed, float time);

  /// <summary>
  /// IsPushedAllKey関数の宣言
  /// </summary>
  /// <param name = "first_key_code">キーの種類first_key_code</param>
  /// <param name = "second_key_code">キーの種類second_key_code</param>
  /// <param name = "all_pushed_">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
  /// <returns>指定されたキーを押されている：true、押されていない：false</returns>
  bool IsPushedAllKey(int first_key_code, int second_key_code, bool& all_pushed_, float time);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// キーの種類
  /// </summary>
  KeyType key_type_;

  /// <summary>
  /// キャラクターコントローラのイベントインターフェース
  /// </summary>
  CharacterControllerEventInterface& character_event_interface_;

  /// <summary>
  /// 各キーの押下の有無
  /// </summary>
  bool pushed_[static_cast<int>(kMaxKey)];

  /// <summary>
  /// 右上キーの押下の有無
  /// </summary>
  bool pushed_right_up_;

  /// <summary>
  /// 右下キーの押下の有無
  /// </summary>
  bool pushed_right_down_;

  /// <summary>
  /// 左上キーの押下の有無
  /// </summary>
  bool pushed_left_up_;

  /// <summary>
  /// 左下キーの押下の有無
  /// </summary>
  bool pushed_left_down_;

  /// <summary>
  /// 右キーの押下の有無
  /// </summary>
  bool pushed_right_;

  /// <summary>
  /// 左キーの押下の有無
  /// </summary>
  bool pushed_left_;

  /// <summary>
  ///// 操作するキャラクターのポインタ
  /// </summary>
  Character& character_;

  /// <summary>
  /// 複数のキーと押下の有無を格納する配列
  /// </summary>
  std::unordered_map<int, bool> pressed_keys_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  int right_accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  int left_accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float two_key_accumulation_time_;

  /// <summary>
  /// IsPushedAllKey関数で累積時間を増やすために足す値
  /// </summary>
  float change_amount_;

  /// <summary>
  /// 前のフレームで押されたキー
  /// </summary>
  KeyType prev_key_type_;

  /// <summary>
  /// キーが一定時間以上押されたかの有無
  /// </summary>
  bool long_pushed_;
};