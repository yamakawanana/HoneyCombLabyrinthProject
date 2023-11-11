#pragma once
#include "System/Task/Task.h"
#include "System/Interface/MenuControllerEventInterface.h"

/// <summary>
/// MenuControllerクラス
/// </summary>
class MenuController : public Task {
public:

  /// <summary>
  //キーの種類の列挙型KeyType型を定義する
  /// <summary>
  enum KeyType {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// エンターキー(決定ボタン)
    /// </summary>
    kEnterKey,

    /// <summary>
    /// ESCキー(終了ボタン)
    /// </summary>
    kEscKey,

    /// <summary>
    /// スペースキー(ポーズボタン)
    /// </summary>
    kSpaceKey,

    /// <summary>
    /// バックスペースキー
    /// </summary>
    kBackSpaceKey,

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
  MenuController(TaskId task_id, MenuControllerEventInterface& event_interface);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~MenuController();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// IsPushedEnterKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>エンターキーを押されている：true、エンターキーを押されていない：false</returns>
  bool IsPushedEnterKey();

  /// <summary>
  /// IsPushedEscKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>ESCキーを押されている：true、ESCキーを押されていない：false</returns>
  bool IsPushedEscKey();

  /// <summary>
  /// IsPushedSpaceKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>スペースキーを押されている：true、スペースキーを押されていない：false</returns>
  bool IsPushedSpaceKey();

  /// <summary>
  /// IsPushedBackSpaceKey関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>バックスペースキーを押されている：true、バックスペースキーを押されていない：false</returns>
  bool IsPushedBackSpaceKey();

private:

  /// <summary>
  /// IsPushedKey関数の宣言
  /// </summary>
  /// <param name = "key_type">キーの種類key_type</param>
  /// <param name = "pushed">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
  /// <returns>指定されたキーを押されている：true、押されていない：false</returns>
  bool IsPushedKey(int key_code, bool& pushed);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// キーの種類
  /// </summary>
  KeyType key_type_;

  /// <summary>
  /// メニューコントローラのイベントインターフェース
  /// </summary>
  MenuControllerEventInterface& menucontroller_event_interface_;

  /// <summary>
  /// 各キーの押下の有無
  /// </summary>
  bool pushed_[static_cast<int>(kMaxKey)];
};
