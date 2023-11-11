#pragma once
#include "System/Level/Level.h"
#include "System/LogConsole.h"
#include "Game/Interface/ResultLevelEventInterface.h"
#include "System/Controller/MenuController.h"

/// <summary>
/// ResultLevelクラス
/// </summary>
class ResultLevel : public Level, public ResultLevelEventInterface {
public:
  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// フェーズ
    /// </summary>
    kDelete,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ResultLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ResultLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~ResultLevel();

  /// <summary>
  /// 決定ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDecide();

  /// <summary>
  /// 終了ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushFinish();

  /// <summary>
  /// ポーズボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushPause();

  /// <summary>
  /// BackSpaceボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushBackSpace();

  /// <summary>
  /// SetResultGrHandle関数の宣言
  /// </summary>
  /// <param = "title_handle">Resultのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetResultGrHandle(int title_handle);

  /// <summary>
  /// GetResultGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Resultのグラフィックハンドル</returns>
  int GetResultGrHandle();

  /// <summary>
  /// SetPushEnterGrHandle関数の宣言
  /// </summary>
  /// <param = "push_enter_handle">文字表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetPushEnterGrHandle(int push_enter_handle);

  /// <summary>
  /// GetPushEnterGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>文字表示のグラフィックハンドル</returns>
  int GetPushEnterGrHandle();

  /// <summary>
  /// SetBgmHandle関数の宣言
  /// </summary>
  /// <param = "bgm_handle">BGMのサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetBgmHandle(int bgm_handle);

  /// <summary>
  /// GetBgmHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BGMのサウンドハンドル</returns>
  int GetBgmHandle();

  /// <summary>
  /// SetEnterSoundHandle関数の宣言
  /// </summary>
  /// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetEnterSoundHandle(int enter_handle);

  /// <summary>
  /// GetEnterSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Enterを押した時のサウンドハンドル</returns>
  int GetEnterSoundHandle();

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut();

protected:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool InitializeUpdate(float time) override;

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool ProcessingUpdate(float time) override;

  /// <summary>
  /// 毎フレームの描画処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void ProcessingRender() override;

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time) override;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 終了の有無
  /// </summary>
  bool is_finish_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// メニューコントローラ
  /// </summary>
  MenuController* menu_controller_;

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// リザルト画面のグラフィックハンドル
  /// </summary>
  int result_handle_;

  /// <summary>
  /// 文字表示の画像のグラフィックハンドル
  /// </summary>
  int push_enter_handle_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// Enterを押した時のサウンドハンドル
  /// </summary>
  int enter_handle_;
};