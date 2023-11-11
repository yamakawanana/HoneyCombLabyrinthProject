#pragma once
#include "System/Task/Task.h"

/// <summary>
/// UiEventInterfaceクラス
/// </summary>
class UiEventInterface {
public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~UiEventInterface() {
  }

  /// <summary>
  /// UI終了のイベント
  /// </summary>
  /// <param name="task_id">終了するUIのタスクID</param>
  /// <returns>なし</returns>
  virtual void EndUi(Task::TaskId task_id) = 0;

};
