#pragma once
#include <map>
#include <array>
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "System/Character.h"

//フィールドの行数
#define ROW 9
//フィールドの列数
#define COLUMN 19
//マップチップ一つのドットサイズ
#define MAP_SIZE	32
//蜂の巣の一部屋を描画する時の縦向きのドットサイズ
#define MAP_SIZE_Y	55
//キューで管理するデータ数の上限
#define MAX_NUM (COLUMN * ROW)
#define QUEUE_SIZE (MAX_NUM + 1)

/// <summary>
/// Fieldクラス
/// </summary>
class Field : public Task {
public:
  /// <summary>
  //敵が各方向に進める場合の行先の座標を保存する配列の要素数を定数kElementXYに格納する
  /// <summary>
  static const int kElementXY = 2;

  /// <summary>
  /// 光のグラフィックハンドルの配列の要素数を定数kLightElementNumberに格納する
  /// </summary>
  static const int kLightElementNumber = 8;

  /// <summary>
  //Pos構造体型を定義する
  /// <summary>
  struct Pos {
    int x; //幅優先探索で使うX位置
    int y; //幅優先探索で使うY位置
    int before_x; //1つ前に探索したX位置
    int before_y; //1つ前に探索したY位置
  };

  /// <summary>
  //Queue構造体型を定義する
  /// <summary>
  struct Queue {
    int tail; // キューの最後尾
    int head; // キューの最先端
    Pos queue_data[QUEUE_SIZE];
  };

  /// <summary>
  //フェーズの種類の列挙型FieldPhaseType型を定義する
  /// <summary>
  enum FieldPhaseType {
    /// <summary>
    /// フィールド初期化フェーズ
    /// </summary>
    kFieldInitialized,

    /// <summary>
    /// プレイヤー・敵キャラクターの初期化フェーズ
    /// </summary>
    kPlayerEnemyInitialized,

    /// <summary>
    /// 処理フェーズ
    /// </summary>
    kProcessing,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kEnding,

    /// <summary>
    /// 終了済みフェーズ
    /// </summary>
    kEnded,

    /// <summary>
    /// 中断フェーズ
    /// </summary>
    kStop,
  };


  /// <summary>
  //マップの種類の列挙型MapType型を定義する
  /// <summary>
  enum MapType {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// 蜂の巣の部屋
    /// </summary>
    kRoom,

    /// <summary>
    /// 蜂の巣の部屋と部屋の間の繋ぎ目
    /// </summary>
    kJoint,

    /// <summary>
    /// 壁
    /// </summary>
    kWall,

    /// <summary>
    /// プレイヤーの開始位置
    /// </summary>
    kPlayerStartPosition,

    /// <summary>
    /// クマの開始位置
    /// </summary>
    kBearStartPosition,

    /// <summary>
    /// 赤いハチの開始位置
    /// </summary>
    kRedBee,

    /// <summary>
    /// 黄色いハチの開始位置
    /// </summary>
    kYellowBee,

    /// <summary>
    /// 迷路の最初の行き止まり
    /// </summary>
    kFirstDeadEnd,

    /// <summary>
    /// 迷路の2つ目の行き止まり
    /// </summary>
    kSecondDeadEnd,

    /// <summary>
    /// 迷路の3つ目の行き止まり
    /// </summary>
    kThirdDeadEnd,

    /// <summary>
    /// 探索が終わった位置
    /// </summary>
    kPassed,
  };

  /// <summary>
  //調べる方向の種類の列挙型DirectionType型を定義する
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
    /// 最大値
    /// </summary>
    kMax,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Field();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// SetWallGrHandle関数の宣言
  /// </summary>
  /// <param = "wall_handle">壁のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWallGrHandle(int wall_handle);

  /// <summary>
  /// GetWallGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>壁のグラフィックハンドル</returns>
  int GetWallGrHandle();

  /// <summary>
  /// SetRoomGrHandle関数の宣言
  /// </summary>
  /// <param = "room_handle">蜂の巣の部屋のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetRoomGrHandle(int room_handle);

  /// <summary>
  /// GetRoomGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>蜂の巣の部屋のグラフィックハンドル</returns>
  int GetRoomGrHandle();

  /// <summary>
  /// SetJointGrHandle関数の宣言
  /// </summary>
  /// <param = "joint_handle">蜂の巣の部屋と部屋の繋ぎ目のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetJointGrHandle(int joint_handle);

  /// <summary>
  /// GetJointGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>蜂の巣の部屋と部屋の繋ぎ目のグラフィックハンドル</returns>
  int GetJointGrHandle();

  /// <summary>
  /// SetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBattleBackGrHandle(int battle_back_handle);

  /// <summary>
  /// GetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BattleLevelの背景のグラフィックハンドル</returns>
  int GetBattleBackGrHandle();

  /// <summary>
  /// SetHoneyGrHandle関数の宣言
  /// </summary>
  /// <param = "honey_handle">蜂蜜のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHoneyGrHandle(int honey_handle);

  /// <summary>
  /// GetHoneyGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>蜂蜜のグラフィックハンドル</returns>
  int GetHoneyGrHandle();

  /// <summary>
  /// SetClearGrHandle関数の宣言
  /// </summary>
  /// <param = "clear_handle">ゲームクリアの画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetClearGrHandle(int clear_handle);

  /// <summary>
  /// GetClearGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームクリアの画像のグラフィックハンドル</returns>
  int GetClearGrHandle();

  /// <summary>
  /// SetKeyInfoGrHandle関数の宣言
  /// </summary>
  /// <param = "key_info_handle">キー操作情報の画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetKeyInfoGrHandle(int key_info_handle);

  /// <summary>
  /// GetKeyInfoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>キー操作情報の画像のグラフィックハンドル</returns>
  int GetKeyInfoGrHandle();

  /// <summary>
  /// GetLightGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetLightGrHandle(int element_num);

  /// <summary>
  /// RegisterCharacter関数の宣言
  /// </summary>
  /// <param>キャラクターのポインタ</param>
  /// <returns>なし</returns>
  void RegisterCharacter(int task_id, Character* character);

  /// <summary>
  /// キャラクター初期化フェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool CharacterPhaseInitialize(float time);

  /// <summary>
  /// キャラクターが移動できるかどうか確認する処理
  /// </summary>
  /// <param name>移動するキャラクターのポインタ </param>
  /// <param name>向かう方向 </param>
  /// <param name>移動先のX位置 </param>
  /// <param name>移動先のY位置 </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool MoveCharacter(Character* character, DirectionType direction_type, int& x_pos, int& y_pos);

  /// <summary>
  /// 移動範囲をチェックする
  /// </summary>
  /// <param name = "character">キャラクターの参照</param>
  /// <param name = "walk_distances">歩ける範囲のリストの参照</param>
  /// <returns>なし</returns>
  void CheckWalkingDistance(Character& character, std::vector<Field::DirectionType>& walk_distances);

  /// <summary>
  /// 指定位置が歩ける状態かを確認する処理
  /// </summary>
  /// <param name>移動するキャラクターのポインタ </param>
  /// <param name>向かう方向 </param>
  /// <param name>移動先のX位置 </param>
  /// <param name>移動先のY位置 </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool CheckIsCanGoForward(int x, int y);

  /// <summary>
  /// キャラクターの開始時の位置を設定する
  /// </summary>
  /// <param name = "character">キャラクターのポインタ</param>
  /// <param name = "x">X位置 </param>
  /// <param name = "y">Y位置 </param>
  /// <returns>なし</returns>
  void SetCharacterStartPos(Character* character, int x, int y);

  /// <summary>
  /// キャラクターの開始時の表示位置を設定する
  /// </summary>
  /// <param name = "character">キャラクターのポインタ</param>
  /// <param name = "x">X位置 </param>
  /// <param name = "y">Y位置 </param>
  /// <returns>なし</returns>
  void SetCharacterStartDisplayPos(Character* character, int x, int y);

  /// <summary>
  /// 幅優先探索で使う迷路情報を初期化する
  /// </summary>
  /// <param name = ""></param>
  /// <param name = ""> </param>
  /// <param name = ""> </param>
  /// <returns>なし</returns>
  void SearchMapInitialize();

  /// <summary>
  /// 幅優先探索で使うキューを初期化する
  /// </summary>
  /// <param name = "queue">Queue構造体型のqueue</param>
  /// <returns>なし</returns>
  void InitQueue(Queue* queue);

  /// <summary>
  /// キューに要素を追加する
  /// </summary>
  /// <param name = "queue">Queue構造体型のqueue</param>
  /// <param name = "input">Pos構造体型のinput</param>
  /// <returns>なし</returns>
  void Enqueue(Queue* queue, Pos* input);

  /// <summary>
  /// キューから要素を取り出す
  /// </summary>
  /// <param name = "queue">Queue構造体型のqueue</param>
  /// <returns>キューから取り出したPos構造体型の要素</returns>
  Pos* Dequeue(Queue* queue);

  /// <summary>
  /// クマさんがハチとぶつかった地点から一番近い行き止まりを特定する
  /// </summary>
  /// <param name = "start_x">クマさんがハチとぶつかった地点のX位置</param>
  /// <param name = "start_y">クマさんがハチとぶつかった地点のY位置</param>
  /// <param = "another_bee_x">もう一匹のハチのX位置</param>
  /// <param = "another_bee_y">もう一匹のハチのY位置</param>
  /// <returns>なし</returns>
  void SearchNarestDeadEnd(int start_x, int start_y, MapType maptype);

  /// <summary>
  /// 座標を更新する処理
  /// </summary>
  /// <param name = "x">X位置</param>
  /// <param name = "y">Y位置</param>
  /// <param name = "middle_x">中間地点のX位置</param>
  /// <param name = "middle_y">中間地点のY位置</param>
  /// <returns>なし</returns>
  void UpdatePos(DirectionType direction_type, int& x, int& y, int& x_middle_pos, int& y_middle_pos);

  /// <summary>
  /// 行き止まりに向かう途中の道にハチがいたら見つける処理
  /// </summary>
  /// <param name = "x">X位置</param>
  /// <param name = "y">Y位置</param>
  /// <param name = "element_num">route_配列の要素数</param>
  /// <returns>なし</returns>
  bool FindBeeInRoute(int x, int y, int element_num, int& found_another_bee);

  /// <summary>
  /// SetAnotherBeeX関数の宣言
  /// </summary>
  /// <param = "another_bee_x">もう一匹のハチのX位置</param>
  /// <returns>なし</returns>
  void SetAnotherBeeX(int another_bee_x);

  /// <summary>
  /// GetAnotherBeeX関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>もう一匹のハチのX位置</returns>
  int GetAnotherBeeX();

  /// <summary>
  /// SetAnotherBeeY関数の宣言
  /// </summary>
  /// <param = "another_bee_y">もう一匹のハチのY位置</param>
  /// <returns>なし</returns>
  void SetAnotherBeeY(int another_bee_y);

  /// <summary>
  /// GetAnotherBeeY関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>もう一匹のハチのY位置</returns>
  int GetAnotherBeeY();

  /// <summary>
  /// 行き止まりまでの最短経路を保存する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  int SaveNarestRoute(int element_num, MapType maptype);

  /// <summary>
  /// SetRouteCount関数の宣言
  /// </summary>
  /// <param = "route_count">最短経路でかかる歩数</param>
  /// <param = "maptype">行き止まりの種類</param>
  /// <returns>なし</returns>
  void SetRouteCount(int route_count, MapType maptype);

  /// <summary>
  /// GetRouteCount関数の宣言
  /// </summary>
  /// <param = "maptype">行き止まりの種類</param>
  /// <returns>最短経路でかかる歩数/returns>
  int GetRouteCount(MapType maptype);

  /// <summary>
  /// GetRoute関数の宣言
  /// </summary>
  /// <param = "maptype">行き止まりの種類</param>
  /// <returns>最短経路に含まれる座標/returns>
  Pos* GetRoute(MapType maptype);

  /// <summary>
  /// SetFieldPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetFieldPhaseType(FieldPhaseType type);

  /// <summary>
  /// GetFieldPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  FieldPhaseType GetFieldPhaseType();

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

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

private:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseInitialize(float time);

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseUpdate(float time);

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //マップの種類
  /// </summary>
  MapType map_type_;

  /// </summary>
  //フェーズの種類
  /// </summary>
  FieldPhaseType field_phase_type_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  FieldPhaseType now_phase_;

  /// <summary>
  /// 壁のグラフィックハンドル
  /// </summary>
  int wall_handle_;

  /// <summary>
  /// 部屋のグラフィックハンドル
  /// </summary>
  int room_handle_;

  /// <summary>
  /// 部屋と部屋の繋ぎ目のグラフィックハンドル
  /// </summary>
  int joint_handle_;

  /// <summary>
  /// BattleLevelの背景のグラフィックハンドル
  /// </summary>
  int battle_back_handle_;

  /// <summary>
  /// 蜂蜜のグラフィックハンドル
  /// </summary>
  int honey_handle_;

  /// <summary>
  /// ゲームクリアの画像のグラフィックハンドル
  /// </summary>
  int clear_handle_;

  /// <summary>
  /// キー操作情報の画像のグラフィックハンドル
  /// </summary>
  int key_info_handle_;

  /// <summary>
  /// 光の画像のグラフィックハンドル
  /// </summary>
  std::array<int, kLightElementNumber> light_handle_;

  /// <summary>
  /// フィールド情報
  /// </summary>
  MapType mapdata_[ROW][COLUMN];

  /// <summary>
  /// 登録されたキャラのリスト
  /// </summary>
  std::map<int, Character*> character_list_;

  /// <summary>
  /// フィールドのキャラクター情報
  /// </summary>
  MapType field_character_info_[ROW][COLUMN];

  /// <summary>
  /// フィールドの敵キャラクター情報
  /// </summary>
  MapType field_red_bee_info_[ROW][COLUMN];

  /// <summary>
  /// 幅優先探索で使うフィールド情報
  /// </summary>
  MapType map_for_search_[ROW][COLUMN];

  /// </summary>
  //調べる方向の種類
  /// </summary>
  DirectionType direction_type_;

  /// </summary>
  //赤いハチのX位置を複数格納する配列
  /// </summary>
  std::vector <int> red_bee_x_positions_;

  /// </summary>
  //赤いハチのY位置を複数格納する配列
  /// </summary>
  std::vector <int> red_bee_y_positions_;

  /// </summary>
  //敵が右上方向に進める場合に右上方向の座標を格納する配列
  /// </summary>
  int up_right_position_[kElementXY];

  /// </summary>
  //敵が右下方向に進める場合に右下方向の座標を格納する配列
  /// </summary>
  int down_right_position_[kElementXY];

  /// </summary>
  //敵が左上方向に進める場合に左上方向の座標を格納する配列
  /// </summary>
  int up_left_position_[kElementXY];

  /// </summary>
  //敵が左下方向に進める場合に左下方向の座標を格納する配列
  /// </summary>
  int down_left_position_[kElementXY];

  /// </summary>
  //敵が右方向に進める場合に右方向の座標を格納する配列
  /// </summary>
  int right_position_[kElementXY];

  /// </summary>
  //敵が左方向に進める場合に左方向の座標を格納する配列
  /// </summary>
  int left_position_[kElementXY];

  /// </summary>
  //クマがゴールしたかの有無を受け取る変数
  /// </summary>
  bool is_bear_goal;

  /// </summary>
  //アヒルがゴールしたかの有無を受け取る変数
  /// </summary>
  bool is_duck_goal;

  /// </summary>
  //Queue構造体型の変数
  /// </summary>
  Queue queue_;

  /// </summary>
  //幅優先探索で通過したルートを保存する配列
  /// </summary>
  Pos route_[ROW * COLUMN];

  /// </summary>
  //幅優先探索の最短経路を保存する配列
  /// </summary>
  Pos back_trace_[ROW * COLUMN];

  /// </summary>
  //一番目の行き止まりの幅優先探索で通過したルートを保存する配列
  /// </summary>
  Pos route_first_deadend_[ROW * COLUMN];

  /// </summary>
  //二番目の行き止まりの幅優先探索で通過したルートを保存する配列
  /// </summary>
  Pos route_second_deadend_[ROW * COLUMN];

  /// </summary>
  //三番目の行き止まりの幅優先探索で通過したルートを保存する配列
  /// </summary>
  Pos route_third_deadend_[ROW * COLUMN];

  /// <summary>
  /// もう一匹のハチのX位置
  /// </summary>
  int another_bee_x_;

  /// <summary>
  /// もう一匹のハチのY位置
  /// </summary>
  int another_bee_y_;

  /// </summary>
  //1番近い行き止まりにハチがいるので2番目に近い行き止まりに行くように示す変数
  /// </summary>
  bool second_route_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 一番目の行き止まりに行くまでにかかる歩数
  /// </summary>
  int first_route_count_;

  /// <summary>
  /// 二番目の行き止まりに行くまでにかかる歩数
  /// </summary>
  int second_route_count_;

  /// <summary>
  /// 三番目の行き止まりに行くまでにかかる歩数
  /// </summary>
  int third_route_count_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;
};
