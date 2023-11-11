#pragma once
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include <array>

/// <summary>
/// InfoUiクラス
/// </summary>
class InfoUi : public Task {
public:

  /// <summary>
  /// カウントダウンのグラフィックハンドルの配列の要素数を定数kElementNumberに格納する
  /// </summary>
  static const int kElementNumber = 10;

  /// <summary>
  /// タイムアップのグラフィックハンドルの配列の要素数を定数kTimeUpElementNumberに格納する
  /// </summary>
  static const int kTimeUpElementNumber = 4;

  /// <summary>
  /// ３秒前カウントダウンのグラフィックハンドルの配列の要素数を定数kThreeElementNumberに格納する
  /// </summary>
  static const int kThreeElementNumber = 3;

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  InfoUi(TaskId task_id, std::array<int, kElementNumber> countdown_handle, std::array<int, kTimeUpElementNumber> timeup_handle, std::array<int, kElementNumber> ten_countdown_handle, std::array<int, kThreeElementNumber> three_countdown_handle);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~InfoUi();

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
  /// GetTimeUpGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetTimeUpGrHandle(int element_num);

  /// <summary>
  /// SetTimeUpGrHandle関数の宣言
  /// </summary>
  /// <param = "gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTimeUpGrHandle(int gr_handle);

  /// <summary>
  /// GetTenGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>10秒前グラフィックハンドル</returns>
  int GetTenGrHandle(int element_num);

  /// <summary>
  /// GetThreeGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>3秒前グラフィックハンドル</returns>
  int GetThreeGrHandle(int element_num);

  /// <summary>
  /// SetCountdown関数の宣言
  /// </summary>
  /// <param = "countdown">カウントダウンの値</param>
  /// <returns>なし</returns>
  void SetCountdown(int countdown);

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

  /// タイムアップを描画する
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderTimeUp();

  /// <summary>
  /// GetLastRender関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>最後の描画が終わったかの有無</returns>
  bool GetLastRender();

  /// <summary>
  /// SetLastRender関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetLastRender();

  /// <summary>
  /// GetTimeUpRenderEnd関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>タイムアップのアニメーションが終わったかの有無</returns>
  bool GetTimeUpRenderEnd();

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int handle, bool is_transparent, int fade_value);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

  /// <summary>
  /// カウントダウンのグラフィックハンドル
  /// </summary>
  std::array<int, kElementNumber> countdown_gr_handle_;

  /// <summary>
  /// TimeUpのグラフィックハンドル
  /// </summary>
  std::array<int, kTimeUpElementNumber> timeup_gr_handle_;

  /// <summary>
  /// 10秒前カウントダウンのグラフィックハンドル
  /// </summary>
  std::array<int, kElementNumber> ten_countdown_gr_handle_;

  /// <summary>
  /// 3秒前カウントダウンのグラフィックハンドル
  /// </summary>
  std::array<int, kThreeElementNumber> three_countdown_gr_handle_;

  /// <summary>
  /// カウントダウンのカウント
  /// </summary>
  int countdown_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

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
  /// 最後の描画が終わったかの有無
  /// </summary>
  bool last_render_;

  /// <summary>
  /// タイムアップのアニメーションが終わったかの有無
  /// </summary>
  bool timeup_end_;
};
