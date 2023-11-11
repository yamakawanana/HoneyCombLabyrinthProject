#pragma once
#include "System/Level/Level.h"
#include "System/LogConsole.h"
#include "Game/Field.h"
#include "Game/Character/Player/Player.h"
#include "Game/Character/Player//Bear.h"
#include "System/Controller/PlayerController.h"
//#include "Game/Interface/BattleLevelEventInterface.h"
#include "Game/Character/Enemy/RedBee.h"
#include "Game/Character/Enemy/YellowBee.h"
#include "System/Character.h"
#include "System/Controller/MenuController.h"
#include "Game/GameMode.h"
#include "Game/GameState.h"
#include "Game/StartUi.h"
//#include "Game/FinishUi.h"
#include "Game/InfoUi.h"
#include "Game/PauseUi.h"
#include "Game/GoalFlag.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 赤いハチの数を定数kRedBeeNumに格納する
  /// </summary>
  static const int kRedBeeNum = 1;

  /// <summary>
  /// 黄色いハチの数を定数kYellowBeeNumに格納する
  /// </summary>
  static const int kYellowBeeNum = 1;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの配列の要素数を定数kConfettiElementNumberに格納する
  /// </summary>
  static const int kConfettiElementNumber = 36;

}

/// <summary>
/// BattleLevelクラス
/// </summary>
class BattleLevel : public Level{
public:

  /// <summary>
  //ImageInfo構造体型を定義する
  /// <summary>
  struct ImageInfo {
    int handle; //画像のグラフィックハンドル
    int size_x; //画像の幅
    int size_y; //画像の高さ
  };

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
  //フェーズの種類(処理中のフェーズ)
  /// <summary>
  enum ProcessingPhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreparation,

    /// <summary>
    /// スタートUI表示
    /// </summary>
    kStartUiDisplay,

    /// <summary>
    /// スタートUI終了待機
    /// </summary>
    kStartUiFinishWaiting,

    /// <summary>
    /// プレイヤー(アヒル)が倒れる
    /// </summary>
    kPlayerDead,

    /// <summary>
    /// アヒルが泣いている
    /// </summary>
    kDuckCrying,

    /// <summary>
    /// タイムオーバー
    /// </summary>
    kTimeOver,

    /// <summary>
    /// ゲームクリア
    /// </summary>
    kClear,

    /// <summary>
    /// ゲームオーバー
    /// </summary>
    kGameOver,

    /// <summary>
    /// フィニッシュUI表示
    /// </summary>
    kFinishUiDisplay,

    /// <summary>
    /// フィニッシュUI終了待機
    /// </summary>
    kFinishUiFinishWaiting,

    /// <summary>
    /// 処理中
    /// </summary>
    kProcessing,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// バトル終了
    /// </summary>
    kBattleFinish,

    /// <summary>
    /// レベル遷移
    /// </summary>
    kLevelTransition,

    /// <summary>
    /// 終了済み
    /// </summary>
    kFinished,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~BattleLevel();

  /// <summary>
  /// 各方向キーが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDirectionKey(Character& character, Field::DirectionType direction);

  /// <summary>
  /// 移動範囲をチェックする
  /// </summary>
  /// <param name = "enemy">敵キャラクターベースクラスの参照</param>
  /// <returns>なし</returns>
  void CheckWalkDistance(EnemyBase& enemy);

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
  /// 死んだ時のイベント(引数のキャラをタスクマネージャーから降ろす)
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void UnloadCharacter(Character& character);

  /// <summary>
  /// キャラクターがぶつかる処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void BumpCharacter(Character& character);

  /// <summary>
  /// ゲームクリア終了のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void GameClear();

  /// <summary>
  /// カウントダウンのイベント
  /// </summary>
  /// <param name="remaining_time">残り時間</param>
  /// <returns>なし</returns>
  virtual void CountRemainingTime(int remaining_time);

  /// <summary>
  /// タイムオーバーのイベント
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual void TimeUp();

  /// <summary>
  /// 敵がプレイヤーにぶつかり攻撃する処理
  /// </summary>
  /// <param = "player_x">プレイヤーX位置</param>
  /// <param = "player_y">プレイヤーY位置</param>
  /// <param = "bee_x">ハチX位置</param>
  /// <param = "bee_y">ハチY位置</param>
  /// <param = "character">キャラクター</param>
  /// <returns>なし</returns>
  void AttackPlayer(int player_x, int player_y, int bee_x, int bee_y, Character& character);

  /// <summary>
  /// クマがハチに刺された時の処理
  /// </summary>
  /// <param = "bear_x">クマX位置</param>
  /// <param = "bear_y">クマY位置</param>
  /// <param = "bee_x">ハチX位置</param>
  /// <param = "bee_y">ハチY位置</param>
  /// <param = "character">キャラクター</param>
  /// <param = "another_bee_x">もう一匹のハチのX位置</param>
  /// <param = "another_bee_y">もう一匹のハチのY位置</param>
  /// <returns>なし</returns>
  void BearStung(int bear_x, int bear_y, int bee_x, int bee_y, Character& character);

  /// <summary>
  /// ゲームオーバー時にクリアの有無を設定する処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetGameOver();

  /// <summary>
  /// ゲームクリア時にクリアの有無を設定する処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetGameClearInfo();

  /// <summary>
  /// UI終了のイベント
  /// </summary>
  /// <param name="task_id">終了するUIのタスクID</param>
  /// <returns>なし</returns>
  virtual void EndUi(TaskId task_id);

  /// <summary>
  /// LoadImage関数の宣言
  /// </summary>
  /// <param = "filename">画像のファイル名</param>
  /// <returns>ImageInfo構造体型のinfo</returns>
  ImageInfo LoadImage(const char* filename);

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int handle, bool is_transparent, int fade_value);

  /// <summary>
  /// SetBlackGrHandle関数の宣言
  /// </summary>
  /// <param = "black_handle">黒い画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBlackGrHandle(int black_handle);

  /// <summary>
  /// GetBlackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>黒い画像のグラフィックハンドル</returns>
  int GetBlackGrHandle();

  /// <summary>
  /// SetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param = "gameover_handle">ゲームオーバーの画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGameOverGrHandle(int gameover_handle);

  /// <summary>
  /// GetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバーの画像のグラフィックハンドル</returns>
  int GetGameOverGrHandle();

  /// <summary>
  /// SetDuckSecondGrHandle関数の宣言
  /// </summary>
  /// <param = "second_duck_handle">アヒルが泣くアニメーションの画像2枚目のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDuckSecondGrHandle(int second_duck_handle);

  /// <summary>
  /// GetDuckSecondGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>アヒルが泣くアニメーションの画像2枚目のグラフィックハンドル</returns>
  int GetDuckSecondGrHandle();

  /// </summary>
  /// 2枚の画像でアニメーション表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "first_handle">１つ目のグラフィックハンドル</param>
  /// <param = "second_handle">２つ目のグラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void TwoImageMoving(int x, int y, int first_handle, int second_handle, bool is_transparent, float time);

  /// </summary>
  /// クマがハチとぶつかった時に一番近い行き止まりへの最短経路を設定する
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "first_handle">１つ目のグラフィックハンドル</param>
  /// <param = "second_handle">２つ目のグラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void SetNearestDeadEnd(int bear_x, int bear_y);

  /// <summary>
  /// StopDuckBee関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopDuckBee();

  /// <summary>
  /// SetPlayingDuckBee関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayingDuckBee();

  /// <summary>
  /// StopAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopAll();

  /// <summary>
  /// SetPlayingAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayingAll();

  /// <summary>
  /// SetDuckFinish関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetDuckFinish();

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut();

  /// <summary>
  /// SetConfettiHandle関数の宣言
  /// </summary>
  /// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle);

  /// <summary>
  /// GetConfettiHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>紙吹雪のグラフィックハンドル</returns>
  int GetConfettiHandle(int element_num);

  /// <summary>
  /// RenderThreeCount関数の定義
  /// </summary>
  /// <param >なし</param>
  /// <returns>なし</returns>
  void RenderThreeCount();

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
  /// SetAttackedSoundHandle関数の宣言
  /// </summary>
  /// <param = "attacked_handle">ダメージを受けた時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetAttackedSoundHandle(int attacked_handle);

  /// <summary>
  /// GetAttackedSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ダメージを受けた時のサウンドハンドル</returns>
  int GetAttackedSoundHandle();

  /// <summary>
  /// SetGameOverSoundHandle関数の宣言
  /// </summary>
  /// <param = "gameover_sound_handle">ゲームオーバー時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetGameOverSoundHandle(int gameover_sound_handle);

  /// <summary>
  /// GetGameOverSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバー時のサウンドハンドル</returns>
  int GetGameOverSoundHandle();

  /// <summary>
  /// SetGameClearSoundHandle関数の宣言
  /// </summary>
  /// <param = "gameclear_sound_handle">ゲームクリア時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetGameClearSoundHandle(int gameclear_sound_handle);

  /// <summary>
  /// GetGameClearSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームクリア時のサウンドハンドル</returns>
  int GetGameClearSoundHandle();

  /// <summary>
  /// SetTimeOverSoundHandle関数の宣言
  /// </summary>
  /// <param = "timeover_sound_handle">タイムオーバー時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetTimeOverSoundHandle(int timeover_sound_handle);

  /// <summary>
  /// GetTimeOverSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>タイムオーバー時のサウンドハンドル</returns>
  int GetTimeOverSoundHandle();

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
  /// フィールド処理
  /// </summary>
  Field* field_;

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// プレイヤー(アヒル)
  /// </summary>
  Player* player_;

  /// <summary>
  /// クマ
  /// </summary>
  Bear* bear_;

  /// <summary>
  /// プレイヤーコントローラ
  /// </summary>
  PlayerController* player_controller_;

  /// <summary>
  /// 赤いハチ(ハチ)
  /// </summary>
  RedBee* red_bee_[kRedBeeNum];

  /// <summary>
  /// 黄色いハチ(ハチ)
  /// </summary>
  YellowBee* yellow_bee_[kYellowBeeNum];

  /// <summary>
  /// メニューコントローラ
  /// </summary>
  MenuController* menu_controller_;

  /// <summary>
  /// プレイヤーが攻撃されたかの有無
  /// </summary>
  bool attacked_;

  /// <summary>
  /// ぶつかる処理で使う敵のX位置を格納する変数
  /// </summary>
  int enemy_x_;

  /// <summary>
  /// ぶつかる処理で使う敵のX位置を格納する変数
  /// </summary>
  int enemy_y_;

  /// <summary>
  /// ぶつかる処理で使う敵のIDを格納する変数
  /// </summary>
  int enemy_id_;

  /// <summary>
  /// ゲームモード
  /// </summary>
  GameMode* game_mode_;

  /// <summary>
  /// ゲームステート
  /// </summary>
  GameState* game_state_;

  /// <summary>
  /// フェーズの種類
  /// </summary>
  ProcessingPhaseType phase_type_;

  /// <summary>
  /// スタートUI
  /// </summary>
  StartUi* start_ui_;

  /// <summary>
  /// バトル情報UI
  /// </summary>
  InfoUi* info_ui_;

  /// <summary>
  /// ポーズ情報UI
  /// </summary>
  PauseUi* pause_ui_;

  /// <summary>
  /// ゴールの旗クラス
  /// </summary>
  GoalFlag* goal_flag_;

  /// <summary>
  /// 黒い画像のグラフィックハンドル
  /// </summary>
  int black_handle_;

  /// <summary>
  /// 最後の描画が終わったかの有無
  /// </summary>
  bool last_render_;

  /// <summary>
  /// クマが刺された時の最後の描画が終わったかの有無
  /// </summary>
  bool bear_last_render_;

  /// <summary>
  /// 2枚の画像でアニメーション表示する関数で使う累積時間（秒）
  /// </summary>
  float animation_accumulation_time_;

  /// <summary>
  /// 2枚の画像でアニメーション表示する関数で使う累積回数
  /// </summary>
  int animation_accumulation_count_;

  /// <summary>
  /// クマが走っている状態の累積時間（秒）
  /// </summary>
  float running_time_;

  /// <summary>
  /// クマが行き止まりで止まっている状態の累積時間（秒）
  /// </summary>
  float stop_time_;

  /// <summary>
  /// 全体が止まっている状態の累積時間（秒）
  /// </summary>
  float pause_time_;

  /// <summary>
  /// ゲームオーバーの画像のグラフィックハンドル
  /// </summary>
  int gameover_handle_;

  /// <summary>
  /// アヒルが泣くアニメーションの画像2枚目のグラフィックハンドル
  /// </summary>
  int second_duck_handle_;

  /// <summary>
  /// カウントダウンが0になってから全体が止まっている状態の累積時間（秒）
  /// </summary>
  float timeup_pause_time_;

  /// <summary>
  /// ゲームクリア状態の累積時間（秒）
  /// </summary>
  float game_clear_time_;

  /// <summary>
  /// 紙吹雪のグラフィックハンドル
  /// </summary>
  std::array<int, kConfettiElementNumber> confetti_handle_;

  /// <summary>
  /// 最初の3秒前カウントが終わったかの有無
  /// </summary>
  bool rendered_three_count_;

  /// <summary>
  /// 文字表示の画像のグラフィックハンドル
  /// </summary>
  int push_enter_handle_;

  /// <summary>
  /// ゲームオーバー時の画像のフェードインが終わったかの有無
  /// </summary>
  bool gameover_fade_end_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// ダメージを受けた時のサウンドハンドル
  /// </summary>
  int attacked_handle_;

  /// <summary>
  /// ゲームオーバー時のサウンドハンドル
  /// </summary>
  int gameover_sound_handle_;

  /// <summary>
  /// ゲームクリア時のサウンドハンドル
  /// </summary>
  int gameclear_sound_handle_;

  /// <summary>
  /// タイムオーバー時のサウンドハンドル
  /// </summary>
  int timeover_sound_handle_;

  /// <summary>
  /// プレイヤーがハチに刺されてからBGMを止めるまでの累積時間（秒）
  /// </summary>
  float bgm_stop_waittime_;

  /// <summary>
  /// クマがハチに刺されてから走っている状態に遷移するまでの累積時間（秒）
  /// </summary>
  float bear_attacked_waittime_;
};