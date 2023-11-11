#include <iostream>
#include <DxLib.h>
#include "System/Controller/MenuController.h"
#include "System/Task/Task.h"
#include "System/LogConsole.h"
#include "System/Character.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
MenuController::MenuController(TaskId task_id, MenuControllerEventInterface& event_interface)
  : Task(task_id)
  , key_type_(kNone)
  , menucontroller_event_interface_(event_interface)
  , pushed_{false}
{
  DEBUG_PRINT(MenuControllerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
MenuController::~MenuController() {
  DEBUG_PRINT(MenuControllerのデストラクタ);
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void MenuController::UpdateFrame(float time) {
  //DEBUG_PRINT(MenuControllerの毎フレーム更新処理);
  if (IsPushedEnterKey()) {
    menucontroller_event_interface_.OnPushDecide();
    DEBUG_PRINT(エンターキーが押された);
  }
  else if (IsPushedEscKey()) {
    menucontroller_event_interface_.OnPushFinish();
    DEBUG_PRINT(終了キーが押された);
  }
  else if (IsPushedSpaceKey()) {
    menucontroller_event_interface_.OnPushPause();
    DEBUG_PRINT(ポーズキーが押された);
  }
  else if (IsPushedBackSpaceKey()) {
    menucontroller_event_interface_.OnPushBackSpace();
    DEBUG_PRINT(バックスペースキーが押された);
  }
}

/// <summary>
/// IsPushedEnterKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>エンターキーを押されている：true、エンターキーを押されていない：false</returns>
bool MenuController::IsPushedEnterKey() {
  return IsPushedKey(KEY_INPUT_RETURN, pushed_[static_cast<int>(kEnterKey)]);
}

/// <summary>
/// IsPushedEscKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>ESCキーを押されている：true、ESCキーを押されていない：false</returns>
bool MenuController::IsPushedEscKey() {
  return IsPushedKey(KEY_INPUT_ESCAPE, pushed_[static_cast<int>(kEscKey)]);
}

/// <summary>
/// IsPushedSpaceKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>スペースキーを押されている：true、スペースキーを押されていない：false</returns>
bool MenuController::IsPushedSpaceKey() {
  return IsPushedKey(KEY_INPUT_SPACE, pushed_[static_cast<int>(kSpaceKey)]);
}

/// <summary>
/// IsPushedBackSpaceKey関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>バックスペースキーを押されている：true、バックスペースキーを押されていない：false</returns>
bool MenuController::IsPushedBackSpaceKey() {
  return IsPushedKey(KEY_INPUT_BACK, pushed_[static_cast<int>(kBackSpaceKey)]);
}

/// <summary>
/// IsPushedKey関数の定義
/// </summary>
/// <param name = "key_type">キーの種類key_type</param>
/// <param name = "pushed">指定されたキーを押されている：pushedがtrue、押されていない：pushedがfalse</param>
/// <returns>指定されたキーを押されている：true、押されていない：false</returns>
bool MenuController::IsPushedKey(int key_code, bool& pushed) {

  //キーが押されたら、pushedを「押されている状態」とする
  if (CheckHitKey(key_code) == 1) {
    pushed = true;
  }

  //キーが押されている場合
  if (pushed) {
    //キーが押されてから離されている場合、trueを返す
    if (CheckHitKey(key_code) == 0) {
      //押されているかの有無はfalseに戻す
      pushed = false;
      DEBUG_PRINT(キーが押された);
      return true;
    }
  }
  
  return false;
}