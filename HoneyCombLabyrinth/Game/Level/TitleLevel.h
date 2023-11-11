#pragma once
#include "DxLib.h"
#include "System/Level/Level.h"
#include "System/LogConsole.h"
#include "System/Controller/MenuController.h"
#include "Game/Interface/TitleLevelEventInterface.h"

/// <summary>
/// TitleLevelクラス
/// </summary>
class TitleLevel : public Level, public TitleLevelEventInterface {
public:

  /// <summary>
  /// アヒルのグラフィックハンドルの配列の要素数を定数kDuckElementNumberに格納する
  /// </summary>
  static const int kDuckElementNumber = 3;

  /// <summary>
  /// クマのグラフィックハンドルの配列の要素数を定数kBearElementNumberに格納する
  /// </summary>
  static const int kBearElementNumber = 3;

  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// 破棄フェーズ
    /// </summary>
    kDelete,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  TitleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  TitleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~TitleLevel();

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
  /// SetTitleGrHandle関数の宣言
  /// </summary>
  /// <param = "title_handle">Titleのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTitleGrHandle(int title_handle);

  /// <summary>
  /// GetTitleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Titleのグラフィックハンドル</returns>
  int GetTitleGrHandle();

  /// <summary>
  /// SetPushEnterGrHandle関数の宣言
  /// </summary>
  /// <param = "push_enter_handle">「Enterを押してね」の吹き出しのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetPushEnterGrHandle(int push_enter_handle);

  /// <summary>
  /// GetPushEnterGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>「Enterを押してね」の吹き出しのグラフィックハンドル</returns>
  int GetPushEnterGrHandle();

  /// <summary>
  /// SetDuckGrHandle関数の宣言
  /// </summary>
  /// <param = "duck_handle">アヒルのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDuckGrHandle(std::array<int, kDuckElementNumber> duck_handle);

  /// <summary>
  /// GetDuckGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>アヒルのグラフィックハンドル</returns>
  int GetDuckGrHandle(int element_num);

  /// <summary>
  /// SetBearGrHandle関数の宣言
  /// </summary>
  /// <param = "bear_handle">クマのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBearGrHandle(std::array<int, kBearElementNumber> bear_handle);

  /// <summary>
  /// GetBearGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>クマのグラフィックハンドル</returns>
  int GetBearGrHandle(int element_num);

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
  /// Titleロゴのグラフィックハンドル
  /// </summary>
  int title_handle_;

  /// <summary>
  /// 「Enterを押してね」の吹き出しのグラフィックハンドル
  /// </summary>
  int push_enter_handle_;

  /// <summary>
  /// アヒルのグラフィックハンドル
  /// </summary>
  std::array<int, kDuckElementNumber> standing_duck_handle_;

  /// <summary>
  /// クマのグラフィックハンドル
  /// </summary>
  std::array<int, kBearElementNumber> standing_bear_handle_;

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
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// Enterを押した時のサウンドハンドル
  /// </summary>
  int enter_handle_;
};