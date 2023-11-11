#include <iostream>
#include <map>
#include <vector>
#include "DxLib.h"
#include "Game/Field.h"
#include "Game/Level/BattleLevel.h"
#include "Game/Character/Player/Player.h"
#include "System/LogConsole.h"
#include "Game/GameInfo.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 部屋と部屋の繋ぎ目の描画開始X位置を定数kStartJointXに格納する
  /// </summary>
  static const int kStartJointX = 80;

  /// <summary>
  /// 部屋と部屋の繋ぎ目の描画開始Y位置を定数kStartJointYに格納する
  /// </summary>
  static const int kStartJointY = 50;

  /// <summary>
  /// マップサイズの幅がマップチップ一つのドットサイズMAP_SIZEの何倍かを表す定数kMapSizeX
  /// </summary>
  static const int kMapSizeX = 18;

  /// <summary>
  /// マップサイズの長さがマップチップ一つのドットサイズMAP_SIZEの何倍かを表す定数kMapSizeY
  /// </summary>
  static const int kMapSizeY = 15;

  /// <summary>
  /// 蜂蜜の描画開始X位置を定数kHoneyXに格納する
  /// </summary>
  static const int kHoneyX = 569;

  /// <summary>
  /// 蜂蜜の描画開始Y位置を定数kHoneyYに格納する
  /// </summary>
  static const int kHoneyY = 498;

  /// <summary>
  /// 光の描画開始X位置を定数kLightXに格納する
  /// </summary>
  static const int kLightX = 527;

  /// <summary>
  /// 光の描画開始Y位置を定数kLightYに格納する
  /// </summary>
  static const int kLightY = 415;

  /// <summary>
  /// 光の2つ目の要素の描画開始Y位置を定数kSecondLightYに格納する
  /// </summary>
  static const int kSecondLightY = 412;

  /// <summary>
  /// アヒルがゴールした画像のX位置を定数kClearXに格納する
  /// </summary>
  static const int kClearX = 350;

  /// <summary>
  /// アヒルがゴールした画像のY位置を定数kClearYに格納する
  /// </summary>
  static const int kClearY = 525;

  /// <summary>
  /// キー操作情報の画像のX位置を定数kKeyInfoXに格納する
  /// </summary>
  static const int kKeyInfoX = 0;

  /// <summary>
  /// キー操作情報の画像のY位置を定数kKeyInfoYに格納する
  /// </summary>
  static const int kKeyInfoY = 570;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 255;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.8f;

  /// <summary>
  /// 配列の2つ目の要素に切り替える時間を定数kTimeFirstに格納する
  /// </summary>
  static const float kTimeFirst = 0.2f;

  /// <summary>
  /// 配列の3つ目の要素に切り替える時間を定数kTimeSecondに格納する
  /// </summary>
  static const float kTimeSecond = 0.4f;

  /// <summary>
  /// 配列の4つ目の要素に切り替える時間を定数kTimeThirdに格納する
  /// </summary>
  static const float kTimeThird = 0.6f;

  /// <summary>
  /// 配列の5つ目の要素に切り替える時間を定数kTimeFourthsに格納する
  /// </summary>
  static const float kTimeFourths = 0.4f;

  /// <summary>
  /// 配列の6つ目の要素に切り替える時間を定数kTimeFifthに格納する
  /// </summary>
  static const float kTimeFifth = 0.5f;

  /// <summary>
  /// 配列の7つ目の要素に切り替える時間を定数kTimeSixthに格納する
  /// </summary>
  static const float kTimeSixth = 0.6f;

  /// <summary>
  /// 配列の8つ目の要素に切り替える時間を定数kTimeSeventhに格納する
  /// </summary>
  static const float kTimeSeventh = 0.7f;

  /// <summary>
  /// 配列の1つ目の要素番号を定数kFirstElementに格納する
  /// </summary>
  static const int kFirstElement = 0;

  /// <summary>
  /// 配列の2つ目の要素番号を定数kSecondElementに格納する
  /// </summary>
  static const int kSecondElement = 1;

  /// <summary>
  /// 配列の3つ目の要素番号を定数kThirdElementに格納する
  /// </summary>
  static const int kThirdElement = 2;

  /// <summary>
  /// 配列の4つ目の要素番号を定数kFourthElementに格納する
  /// </summary>
  static const int kFourthElement = 3;

  /// <summary>
  /// 配列の5つ目の要素番号を定数kFifthElementに格納する
  /// </summary>
  static const int kFifthElement = 4;

  /// <summary>
  /// 配列の6つ目の要素番号を定数kSixthElementに格納する
  /// </summary>
  static const int kSixthElement = 5;

  /// <summary>
  /// 配列の7つ目の要素番号を定数kSeventhElementに格納する
  /// </summary>
  static const int kSeventhElement = 6;

  /// <summary>
  /// 配列の8つ目の要素番号を定数kEighthElementに格納する
  /// </summary>
  static const int kEighthElement = 7;

  /// <summary>
  /// 行き止まりまでの歩数の最大値を定数kMaxRouteCountに格納する
  /// </summary>
  static const int kMaxRouteCount = 14;

  /// <summary>
  /// アヒルが進んだ音のサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/Move42.mp3";
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field()
  : task_manager_(0)
  , map_type_(kRoom)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , wall_handle_(0)
  , room_handle_(0)
  , joint_handle_(0)
  , battle_back_handle_(0)
  , direction_type_(kMax)
  , is_bear_goal(false)
  , is_duck_goal(false)
  , another_bee_x_(0)
  , another_bee_y_(0)
  , second_route_(false)
  , accumulation_time_(0.0f)
  , first_route_count_(0)
  , second_route_count_(0)
  , third_route_count_(0)
  , key_info_handle_(0)
  , clear_handle_(0)
  , honey_handle_(0)
{
  DEBUG_PRINT(Fieldのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field(TaskId task_id, TaskManager* task_manager)
  : Task(task_id)
  , task_manager_(task_manager)
  , map_type_(kRoom)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , wall_handle_(0)
  , room_handle_(0)
  , joint_handle_(0)
  , battle_back_handle_(0)
  , direction_type_(kMax)
  , is_bear_goal(false)
  , is_duck_goal(false)
  , another_bee_x_(0)
  , another_bee_y_(0)
  , second_route_(false)
  , accumulation_time_(0.0f)
  , first_route_count_(0)
  , second_route_count_(0)
  , third_route_count_(0)
  , key_info_handle_(0)
  , clear_handle_(0)
  , honey_handle_(0)
{
  DEBUG_PRINT(Fieldのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::~Field() {
  DEBUG_PRINT(Fieldのデストラクタ);
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Field::UpdateFrame(float time) {
  //DEBUG_PRINT(Fieldクラスの毎フレーム更新処理);
  if (now_phase_ != kStop) {

    bool result = false;

    switch (field_phase_type_) {

      //フェーズが初期化フェーズの場合
    case kFieldInitialized: {
      //mapdata_の初期化を行う
      result = PhaseInitialize(time);
      //初期化処理が終わったら、キャラクター初期化フェーズに遷移する
      if (result) {
        field_phase_type_ = kPlayerEnemyInitialized;
        DEBUG_PRINT(Fieldのキャラクター初期化フェーズに遷移);
      }
      break;
    }
                          //フェーズがキャラクター初期化フェーズの場合
    case FieldPhaseType::kPlayerEnemyInitialized: {
      //キャラクター初期化フェーズが終わったら、処理フェーズに遷移する
      result = CharacterPhaseInitialize(time);
      if (result) {
        field_phase_type_ = kProcessing;
        DEBUG_PRINT(Fieldの処理フェーズに遷移);
      }
      break;
    }
                                                //フェーズが処理フェーズの場合
    case FieldPhaseType::kProcessing: {
      //処理フェーズが終わったら、終了フェーズに遷移する
      result = PhaseUpdate(time);
      if (result) {
        field_phase_type_ = kEnding;
        DEBUG_PRINT(Fieldの終了フェーズに遷移);
      }
      break;
    }
                                    //フェーズが終了フェーズの場合
    case FieldPhaseType::kEnding: {
      //終了フェーズが終わったら、終了済みフェーズに遷移する
      result = PhaseFinalize(time);
      if (result) {
        field_phase_type_ = kEnded;
        DEBUG_PRINT(Fieldの終了済みフェーズに遷移);
      }
      break;
    }
                                //フェーズが終了済みの場合
    case FieldPhaseType::kEnded: {
      DEBUG_PRINT(Fieldのフェーズが終了済み);
      break;
    }
    }
  }
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Field::RenderFrame() {
  //DEBUG_PRINT(Fieldクラスの毎フレーム描画処理);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲーム情報からマップの左上の座標を取得する
  int map_left_x = game_info->GetMapLeftX();
  int map_left_y = game_info->GetMapLeftY();

  // 処理中の状態であれば、マップを描く
  if (field_phase_type_ == kProcessing) {
    DrawGraph(0, 0, battle_back_handle_, TRUE);
    for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < COLUMN; j++)
      {
        if (mapdata_[i][j] == kJoint)
        {
          DrawGraph((map_left_x - MAP_SIZE * 3) + kStartJointX + (j * MAP_SIZE), map_left_y + (i * MAP_SIZE_Y), joint_handle_, TRUE);
        }
        else if (mapdata_[i][j] == kRoom)
        {
          DrawGraph((map_left_x - MAP_SIZE * 3) + (j * MAP_SIZE), (map_left_y - kStartJointY) + (i * MAP_SIZE_Y), room_handle_, TRUE);
        }
      }
    }

    //蜂蜜を描画する
    DrawGraph(kHoneyX, kHoneyY, honey_handle_, TRUE);
    DrawGraph(kKeyInfoX, kKeyInfoY, key_info_handle_, TRUE);

  }
}

/// <summary>
/// SetWallGrHandle関数の定義
/// </summary>
/// <param = "wall_handle">壁のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetWallGrHandle(int wall_handle) {
  wall_handle_ = wall_handle;
}

/// <summary>
/// GetWallGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>壁のグラフィックハンドル</returns>
int Field::GetWallGrHandle() {
  return wall_handle_;
}

/// <summary>
/// SetRoomGrHandle関数の定義
/// </summary>
/// <param = "room_handle">部屋のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetRoomGrHandle(int room_handle) {
  room_handle_ = room_handle;
}

/// <summary>
/// GetRoomGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>部屋のグラフィックハンドル</returns>
int Field::GetRoomGrHandle() {
  return room_handle_;
}

/// <summary>
/// SetJointGrHandle関数の定義
/// </summary>
/// <param = "joint_handle">部屋のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetJointGrHandle(int joint_handle) {
  joint_handle_ = joint_handle;
}

/// <summary>
/// GetJointGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>部屋のグラフィックハンドル</returns>
int Field::GetJointGrHandle() {
  return joint_handle_;
}

/// <summary>
/// SetBattleBackGrHandle関数の定義
/// </summary>
/// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBattleBackGrHandle(int battle_back_handle) {
  battle_back_handle_ = battle_back_handle;
}

/// <summary>
/// GetBattleBackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BattleLevelの背景のグラフィックハンドル</returns>
int Field::GetBattleBackGrHandle() {
  return battle_back_handle_;
}

/// <summary>
/// SetHoneyGrHandle関数の定義
/// </summary>
/// <param = "honey_handle">蜂蜜のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetHoneyGrHandle(int honey_handle) {
  honey_handle_ = honey_handle;
}

/// <summary>
/// GetHoneyGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>蜂蜜のグラフィックハンドル</returns>
int Field::GetHoneyGrHandle() {
  return honey_handle_;
}

/// <summary>
/// SetClearGrHandle関数の定義
/// </summary>
/// <param = "clear_handle">アヒルがゴールした画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetClearGrHandle(int clear_handle) {
  clear_handle_ = clear_handle;
}

/// <summary>
/// GetClearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルがゴールした画像のグラフィックハンドル</returns>
int Field::GetClearGrHandle() {
  return clear_handle_;
}

/// <summary>
/// SetKeyInfoGrHandle関数の定義
/// </summary>
/// <param = "key_info_handle">アヒルがゴールした画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetKeyInfoGrHandle(int key_info_handle) {
  key_info_handle_ = key_info_handle;
}

/// <summary>
/// GetKeyInfoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルがゴールした画像のグラフィックハンドル</returns>
int Field::GetKeyInfoGrHandle() {
  return key_info_handle_;
}

/// <summary>
/// RegisterCharacter関数の定義
/// </summary>
/// <param>キャラクターのポインタ</param>
/// <returns>なし</returns>
void Field::RegisterCharacter(int task_id, Character* character) {
  character_list_.emplace(task_id, character);
}

/// <summary>
/// GetLightGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetLightGrHandle(int element_num) {
  return light_handle_[element_num];
}

/// <summary>
/// キャラクター初期化フェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::CharacterPhaseInitialize(float time) {
  DEBUG_PRINT(キャラクター初期化フェーズ処理);
  // character_list_に登録されている全てのキャラクターを取り出す
  for (auto character_element : character_list_) {
    Character* character = character_element.second;

    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COLUMN; j++) {

        if (character->GetCharacterType() == Character::kPlayer) {
          //フィールドマップの中からプレイヤーのスタート位置を探し、プレイヤーのX座標とY座標にセットする

          if (mapdata_[i][j] == kPlayerStartPosition) {
            std::cout << "プレイヤーのスタート位置座標: (" << j << ", " << i << ")" << std::endl;
            SetCharacterStartPos(character, j, i);
          }
          //キャラクター用のフィールド情報の該当座標にプレイヤーキャラをセットする
          if (j == character->GetXPosition() && i == character->GetYPosition()) {
            field_character_info_[i][j] = kPlayerStartPosition;
            SetCharacterStartDisplayPos(character, j, i);
          }
        }

        if (character->GetCharacterType() == Character::kBear) {
          //フィールドマップの中からクマのスタート位置を探し、クマのX座標とY座標にセットする

          if (mapdata_[i][j] == kBearStartPosition) {
            std::cout << "クマのスタート位置座標: (" << j << ", " << i << ")" << std::endl;
            SetCharacterStartPos(character, j, i);
          }
          //キャラクター用のフィールド情報の該当座標にクマをセットする
          if (j == character->GetXPosition() && i == character->GetYPosition()) {
            field_character_info_[i][j] = kBearStartPosition;
            SetCharacterStartDisplayPos(character, j, i);
          }
        }

        if (character->GetCharacterType() == Character::kRedBee) {
          //フィールドマップの中からハチのスタート位置を探し、ハチのX座標とY座標にセットする

          if (mapdata_[i][j] == kRedBee) {
            std::cout << "ハチのスタート位置座標: (" << j << ", " << i << ")" << std::endl;
            SetCharacterStartPos(character, j, i);
          }
          //キャラクター用のフィールド情報の該当座標にハチをセットする
          if (j == character->GetXPosition() && i == character->GetYPosition()) {
            field_character_info_[i][j] = kRedBee;
            SetCharacterStartDisplayPos(character, j, i);
          }
        }

        if (character->GetCharacterType() == Character::kYellowBee) {
          //フィールドマップの中からハチのスタート位置を探し、ハチのX座標とY座標にセットする

          if (mapdata_[i][j] == kYellowBee) {
            std::cout << "ハチのスタート位置座標: (" << j << ", " << i << ")" << std::endl;
            SetCharacterStartPos(character, j, i);
          }
          //キャラクター用のフィールド情報の該当座標にハチをセットする
          if (j == character->GetXPosition() && i == character->GetYPosition()) {
            field_character_info_[i][j] = kYellowBee;
            SetCharacterStartDisplayPos(character, j, i);
          }
        }
      }
    }

    //現在のフェーズをプレイ中に設定する
    character->SetPhaseType(Character::kPlaying);
  }
  DEBUG_PRINT(キャラクターを初期化した);

  return true;
}

/// <summary>
/// キャラクターが移動できるかどうか確認する処理
/// </summary>
/// <param name>移動するキャラクターのポインタ </param>
/// <param name>向かう方向 </param>
/// <param name>移動先のX位置 </param>
/// <param name>移動先のY位置 </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::MoveCharacter(Character* character, DirectionType direction_type, int& x_pos, int& y_pos) {
  DEBUG_PRINT(MoveCharacter);
  //歩ける位置を初期化する
  x_pos = 0;
  y_pos = 0;

  //進めるか確認するために、プレイヤーから見て向かう先の手前にある座標を格納するための変数を用意する
  int x_middle_pos = 0;
  int y_middle_pos = 0;

  //現在のキャラクターの位置を取得する
  int x = character->GetXPosition();
  int y = character->GetYPosition();
  DEBUG_PRINT(現在のキャラクターの位置を取得する);
  DEBUG_PRINT_VAR(x);
  DEBUG_PRINT_VAR(y);

  //フィールド情報の移動前のキャラクターを消す
  if (mapdata_[y][x] == MapType::kPlayerStartPosition || mapdata_[y][x] == MapType::kBearStartPosition || mapdata_[y][x] == MapType::kRedBee) {
    mapdata_[y][x] = MapType::kWall;
  }

  //調べる方向の種類に応じて、座標を更新する
  UpdatePos(direction_type, x, y, x_middle_pos, y_middle_pos);

  //向かう先の手前にある座標が歩ける場合、移動先のx_pos位置とy_pos位置に更新後のxとyを設定する
  bool can_walk = CheckIsCanGoForward(x_middle_pos, y_middle_pos);
  if (can_walk) {
    x_pos = x;
    y_pos = y;

    DEBUG_PRINT(歩ける);
  }

  //該当位置が歩けるかの有無を返す
  return can_walk;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseInitialize(float time) {

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  //マップのサイズを設定する
  game_info->SetMapSize(kMapSizeX * MAP_SIZE, kMapSizeY * MAP_SIZE);

  //mapdata_を初期化するための一時的な二次元配列を用意する
  int temp_initialdata[ROW][COLUMN] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 4, 3, 2, 2, 2, 1, 2, 2, 5, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 1, 2, 6, 2, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

  //temp_initialdataの要素をmapdata_にコピーし、mapdata_を初期化する
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COLUMN; j++) {
      int element_value = temp_initialdata[i][j];
      switch (element_value) {
      case 0:
        mapdata_[i][j] = MapType::kWall;
        break;
      case 1:
        mapdata_[i][j] = MapType::kRoom;
        break;
      case 2:
        mapdata_[i][j] = MapType::kJoint;
        break;
      case 3:
        mapdata_[i][j] = MapType::kPlayerStartPosition;
        break;
      case 4:
        mapdata_[i][j] = MapType::kBearStartPosition;
        break;
      case 5:
        mapdata_[i][j] = MapType::kRedBee;
        break;
      case 6:
        mapdata_[i][j] = MapType::kYellowBee;
        break;
      }
    }
  }
  DEBUG_PRINT(mapdata_を初期化した);

  //field_character_info_を初期化するための一時的な二次元配列を用意する
  MapType temp_character_initialdata[ROW][COLUMN] = {
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
  };

  //temp_character_initialdataの要素をfield_character_info_にコピーし、field_character_info_を初期化する
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COLUMN; j++) {
      field_character_info_[i][j] = temp_character_initialdata[i][j];
    }
  }
  DEBUG_PRINT(field_character_info_を初期化した);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseUpdate(float time) {
  return false;
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseFinalize(float time) {
  //mapdata_をクリアするための一時的な二次元配列を用意する

  MapType temp_finalizedata[ROW][COLUMN] = {
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
    {kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone, kNone},
  };

  //temp_initialdataの要素をmapdata_にコピーし、mapdata_を初期化する
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COLUMN; j++) {
      mapdata_[i][j] = temp_finalizedata[i][j];
    }
  }
  DEBUG_PRINT(mapdata_をクリアした);

  //サウンドのリソースを破棄する
  int bgm_handle = DeleteSoundMem(GetBgmHandle());

  return true;
}

/// <summary>
/// 指定位置が歩ける状態かを確認する処理
/// </summary>
/// <param name>移動するキャラクターのポインタ </param>
/// <param name>向かう方向 </param>
/// <param name>移動先のX位置 </param>
/// <param name>移動先のY位置 </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::CheckIsCanGoForward(int x, int y) {
  //DEBUG_PRINT(指定位置が歩ける状態かを確認する処理);
  if (mapdata_[y][x] == kWall || map_for_search_[y][x] == kWall) {
    //壁であれば、進めない
    //DEBUG_PRINT(座標が壁なので、進めない);
    return false;
  }
  if (mapdata_[y][x] == kRoom || map_for_search_[y][x] == kRoom) {
    //座標が蜂の巣の部屋であれば、進める
    //DEBUG_PRINT(座標が部屋なので、進める);
    return true;
  }
  if (mapdata_[y][x] == kJoint || map_for_search_[y][x] == kJoint) {
    //座標が部屋と部屋の繋ぎ目であれば、進める
    //DEBUG_PRINT(座標が繋ぎ目なので、進める);
    return true;
  }
  if (mapdata_[y][x] == kRedBee || map_for_search_[y][x] == kRedBee) {
    //座標が敵であれば、進める
    //DEBUG_PRINT(座標が敵なので、進める);
    return true;
  }
  if (mapdata_[y][x] == kYellowBee || map_for_search_[y][x] == kYellowBee) {
    //座標が敵であれば、進める
    //DEBUG_PRINT(座標が敵なので、進める);
    return true;
  }
  if (map_for_search_[y][x] == kPassed) {
    //探索済みであれば、進めない
    //DEBUG_PRINT(探索済みなので、進めない);
    return false;
  }
  return false;
}

/// <summary>
/// 移動範囲をチェックする
/// </summary>
/// <param name = "character">キャラクターの参照</param>
/// <param name = "walk_distances">歩ける範囲のリストの参照</param>
/// <returns>なし</returns>
void Field::CheckWalkingDistance(Character& character, std::vector<Field::DirectionType>& walk_distances) {

}

/// <summary>
/// キャラクターの開始時の位置を設定する
/// </summary>
/// <param name = "character">キャラクターのポインタ</param>
/// <param name>X位置 </param>
/// <param name>Y位置 </param>
/// <returns>なし</returns>
void Field::SetCharacterStartPos(Character* character, int x, int y) {
  character->SetXPosition(x);
  character->SetYPosition(y);
}

/// <summary>
/// キャラクターの開始時の表示位置を設定する
/// </summary>
/// <param name = "character">キャラクターのポインタ</param>
/// <param name>X位置 </param>
/// <param name>Y位置 </param>
/// <returns>なし</returns>
void Field::SetCharacterStartDisplayPos(Character* character, int x, int y) {
  int x_start = x * character->GetWidth();
  int y_start = y * character->GetHeight();
  character->SetDisplayXPosition(static_cast<float>(x_start));
  character->SetDisplayYPosition(static_cast<float>(y_start));
}

/// <summary>
/// 幅優先探索で使う迷路情報を初期化する
/// </summary>
/// <param name = ""></param>
/// <param name = ""> </param>
/// <param name = ""> </param>
/// <returns>なし</returns>
void Field::SearchMapInitialize() {
  //mapdata_を初期化するための一時的な二次元配列を用意する
  int temp_initialdata[ROW][COLUMN] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 5, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 3, 0, 0},
    {0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 1, 2, 2, 2, 4, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

  //temp_initialdataの要素をmap_for_search_にコピーし、map_for_search_を初期化する
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COLUMN; j++) {
      int element_value = temp_initialdata[i][j];
      switch (element_value) {
      case 0:
        map_for_search_[i][j] = MapType::kWall;
        break;
      case 1:
        map_for_search_[i][j] = MapType::kRoom;
        break;
      case 2:
        map_for_search_[i][j] = MapType::kJoint;
        break;
      case 3:
        map_for_search_[i][j] = MapType::kFirstDeadEnd;
        break;
      case 4:
        map_for_search_[i][j] = MapType::kSecondDeadEnd;
        break;
      case 5:
        map_for_search_[i][j] = MapType::kThirdDeadEnd;
        break;
      }
    }
  }
  DEBUG_PRINT(map_for_search_を初期化した);
}

/// <summary>
/// 幅優先探索で使うキューを初期化する
/// </summary>
/// <param name = "queue">Queue構造体型のqueue</param>
/// <returns>なし</returns>
void Field::InitQueue(Queue* queue) {

  //キューの先頭と末尾を空の状態に初期化する
  queue->head = 0;
  queue->tail = -1;
}

/// <summary>
/// キューに要素を追加する
/// </summary>
/// <param name = "queue">Queue構造体型のポインタ</param>
/// <param name = "input">Pos構造体型のポインタ</param>
/// <returns>なし</returns>
void Field::Enqueue(Queue* queue, Pos* input) {
  // データをデータの最後尾の１つ後ろに格納
  queue->queue_data[(queue->tail + 1) % QUEUE_SIZE] = *input;

  // データの最後尾を１つ後ろに移動
  queue->tail = (queue->tail + 1) % QUEUE_SIZE;
}

/// <summary>
/// キューから要素を取り出す
/// </summary>
/// <param name = "queue">Queue構造体のポインタ</param>
/// <returns>キューから取り出したPos構造体型の要素</returns>
Field::Pos* Field::Dequeue(Queue* queue) {
  //返す値であるPos構造体型のポインタreturn_dataを定義する
  Pos* return_data;

  //キューが空である場合
  if ((queue->tail + 1) % QUEUE_SIZE == queue->head) {
    DEBUG_PRINT(キューが空);
    return NULL;
  }

    // 先頭からデータを取得する
    return_data = &(queue->queue_data[queue->head]);

    // データの先頭を１つ後ろにずらす 
    queue->head = (queue->head + 1) % QUEUE_SIZE;

    // 取得したデータを返す
    return return_data;
}

/// <summary>
/// クマさんがハチとぶつかった地点から一番近い行き止まりを特定する
/// </summary>
/// <param name = "start_x">クマさんがハチとぶつかった地点のX位置</param>
/// <param name = "start_y">クマさんがハチとぶつかった地点のY位置</param>
/// <param = "another_bee_x">もう一匹のハチのX位置</param>
/// <param = "another_bee_y">もう一匹のハチのY位置</param>
/// <returns>なし</returns>
void Field::SearchNarestDeadEnd(int start_x, int start_y, MapType maptype) {

  //探索用のマップを初期化する
  SearchMapInitialize();
  //キューを初期化する
  InitQueue(&queue_);

  //Pos構造体の宣言
  Pos pos;

  //route_配列の要素番号の整数を用意する
  int element_num = 0;

  //探索するX位置とY位置に、クマさんがハチとぶつかった位置を格納する
  pos.x = start_x;
  pos.y = start_y;

  //back_trace_配列内の座標にもう1匹のハチがいた場合にback_trace_配列の要素番号を保存する変数
  int found_another_bee = 0;

  //もう一匹のハチの位置を取得する
  int another_bee_x = GetAnotherBeeX();
  int another_bee_y = GetAnotherBeeY();

  //スタート時は1つ前の探索位置が無いため、-1にする
  pos.before_x = -1;
  pos.before_y = -1;

  //Queue構造体と探索位置の情報をキューに追加する
  Enqueue(&queue_, &pos);

  while (true) {
    //探索するX位置
    int x_pos;
    //探索するY位置
    int y_pos;

    //キューから要素を取り出し、次の探索位置とする
    Pos* next = Dequeue(&queue_);

    //キューから取り出した次の探索候補の要素のX位置とY位置を探索する位置にする
    x_pos = next->x;
    y_pos = next->y;

    //キューから取り出した次の探索候補の要素をroute配列に保存してから、route配列の要素番号を増やす
    route_[element_num] = *next;
    element_num++;

    //行き止まりに着いたら、処理を終了する
    if (map_for_search_[y_pos][x_pos] == maptype) {
      DEBUG_PRINT_VAR(x_pos);
      DEBUG_PRINT_VAR(y_pos);
      //最短経路を保存する
      //最短経路までの歩数も保存する
      int route_count = SaveNarestRoute(element_num, maptype);

      //該当する行き止まりに向かう途中に別のハチがいた場合、その行き止まりには逃げられないものとするため、route_countを最大値にする
      if (FindBeeInRoute(another_bee_x, another_bee_y, route_count, found_another_bee)) {
        route_count = kMaxRouteCount;
      }

      SetRouteCount(route_count, maptype);

      break;
    }

    //既に探索した位置のMapTypeをkPassedに変更する
    map_for_search_[y_pos][x_pos] = kPassed;

    //右上方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos, COLUMN - 1)),((std::max)(y_pos - 1, 0)))) {

      pos.x = (std::min)(x_pos + 2, COLUMN - 1);
      pos.y = (std::max)(y_pos - 2, 0);
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //右上方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }

    //右下方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos, COLUMN - 1)),((std::max)(y_pos + 1, 0)))) {

      pos.x = (std::min)(x_pos + 2, COLUMN - 1);
      pos.y = (std::min)(y_pos + 2, ROW - 1);
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //右下方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }

    //左上方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos - 2, COLUMN - 1)),((std::max)(y_pos - 1, 0)))) {
      
      pos.x = (std::max)(x_pos - 2, 0);
      pos.y = (std::max)(y_pos - 2, 0);
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //左上方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }

    //左下方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos - 2, COLUMN - 1)),((std::max)(y_pos + 1, 0)))) {

      pos.x = (std::max)(x_pos - 2, 0);
      pos.y = (std::min)(y_pos + 2, ROW - 1);
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //左下方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }

    //右方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos + 2, COLUMN - 1)),((std::max)(y_pos, 0)))) {
      
      pos.x = (std::min)(x_pos + 4, COLUMN - 1);
      pos.y = y_pos;
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //右方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }

    //左方向に進める場合
    if (CheckIsCanGoForward(((std::min)(x_pos - 2, COLUMN - 1)),((std::max)(y_pos, 0)))) {

      pos.x = (std::max)(x_pos - 4, 0);
      pos.y = y_pos;
      pos.before_x = x_pos;
      pos.before_y = y_pos;

      //左方向の位置をキューに追加する
      Enqueue(&queue_, &pos);
    }
  }
}

  /// <summary>
  /// 座標を更新する処理
  /// </summary>
  /// <param name = "x">X位置</param>
  /// <param name = "y">Y位置</param>
  /// <param name = "middle_x">中間地点のX位置</param>
  /// <param name = "middle_y">中間地点のY位置</param>
  /// <returns>なし</returns>
void Field::UpdatePos(DirectionType direction_type, int& x, int& y, int& x_middle_pos, int& y_middle_pos) {
  //調べる方向の種類に応じて、座標を更新する
  switch (direction_type) {

  case DirectionType::kRightUp:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x, COLUMN - 1);
    y_middle_pos = (std::max)(y - 1, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でxとyを更新する
    x = (std::min)(x + 2, COLUMN - 1);
    y = (std::max)(y - 2, 0);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kRightUp);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  case DirectionType::kRightDown:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x, COLUMN - 1);
    y_middle_pos = (std::max)(y + 1, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でxとyを更新する
    x = (std::min)(x + 2, COLUMN - 1);
    y = (std::min)(y + 2, ROW - 1);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kRightDown);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  case DirectionType::kLeftUp:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x - 2, COLUMN - 1);
    y_middle_pos = (std::max)(y - 1, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でxとyを更新する
    x = (std::max)(x - 2, 0);
    y = (std::max)(y - 2, 0);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kLeftUp);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  case DirectionType::kLeftDown:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x - 2, COLUMN - 1);
    y_middle_pos = (std::max)(y + 1, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でxとyを更新する
    x = (std::max)(x - 2, 0);
    y = (std::min)(y + 2, ROW - 1);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kLeftDown);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  case DirectionType::kRight:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x + 2, COLUMN - 1);
    y_middle_pos = (std::max)(y, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でxを更新する
    x = (std::min)(x + 4, COLUMN - 1);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kRight);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  case DirectionType::kLeft:
    //向かう先の手前にある座標を更新する
    x_middle_pos = (std::min)(x - 2, COLUMN - 1);
    y_middle_pos = (std::max)(y, 0);
    DEBUG_PRINT_VAR(x_middle_pos);
    DEBUG_PRINT_VAR(y_middle_pos);

    //フィールドをはみ出さない範囲でyを更新する
    x = (std::max)(x - 4, 0);
    DEBUG_PRINT_VAR(x);
    DEBUG_PRINT_VAR(y);

    //character->SetDirectionType(Character::kLeft);
    //DEBUG_PRINT_VAR(character->GetDirectionType());

    break;
  }
}

/// <summary>
/// 行き止まりに向かう途中の道にハチがいたら見つける処理
/// </summary>
/// <param name = "x">ぶつかっていない方のハチのX位置</param>
/// <param name = "y">ぶつかっていない方のハチのY位置</param>
/// <param name = "element_num">route_配列の要素数</param>
/// <returns>なし</returns>
bool Field::FindBeeInRoute(int x, int y, int element_num, int& found_another_bee) {
  for (int i = 0; i < element_num; ++i) {
    if (back_trace_[i].x == x && back_trace_[i].y == y) {
      if (map_for_search_[back_trace_[i].y][back_trace_[i].x] == kFirstDeadEnd) {
        second_route_ = true;
        DEBUG_PRINT(1番目の行き止まりはハチがいるので行けない);
        return true;
      }
      if (map_for_search_[back_trace_[i].y][back_trace_[i].x] == kSecondDeadEnd) {
        second_route_ = true;
        DEBUG_PRINT(2番目の行き止まりはハチがいるので行けない);
        return true;
      }
      if (map_for_search_[back_trace_[i].y][back_trace_[i].x] == kThirdDeadEnd) {
        second_route_ = true;
        DEBUG_PRINT(3番目の行き止まりはハチがいるので行けない);
        return true;
      }
    }
  }
  return false;
}

/// <summary>
/// SetAnotherBeeX関数の定義
/// </summary>
/// <param = "another_bee_x">もう一匹のハチのX位置<</param>
/// <returns>なし</returns>
void Field::SetAnotherBeeX(int another_bee_x) {
  another_bee_x_ = another_bee_x;
}

/// <summary>
/// GetAnotherBeeX関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>もう一匹のハチのX位置</returns>
int Field::GetAnotherBeeX() {
  return another_bee_x_;
}

/// <summary>
/// SetAnotherBeeY関数の定義
/// </summary>
/// <param = "another_bee_y">もう一匹のハチのX位置<</param>
/// <returns>なし</returns>
void Field::SetAnotherBeeY(int another_bee_y) {
  another_bee_y_ = another_bee_y;
}

/// <summary>
/// GetAnotherBeeY関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>もう一匹のハチのY位置</returns>
int Field::GetAnotherBeeY() {
  return another_bee_y_;
}

/// <summary>
/// 行き止まりまでの最短経路を保存する
/// </summary>
/// <param = "element_num"></param>
/// <returns>なし</returns>
int Field::SaveNarestRoute(int element_num, MapType maptype) {

  //back_trace_の要素番号として使う整数を用意する
  int count = 0;

  //最後に通った位置の要素番号
  int element = element_num - 1;

  while (true) {

    //route_配列内の、要素番号に対応する通過した位置の情報をpos変数に格納する
    Pos pos = route_[element];
    //back_trace_配列のcount番目の要素に通過した位置の情報posを格納する
    back_trace_[count] = pos;

    count++;

    //前に通過した位置が無ければ、処理を終了する
    if (pos.before_x == -1 && pos.before_y == -1) {
      break;
    }

    //現在の探索位置の前に通過した位置の要素番号before_element
    int before_element = element - 1;

    //現在の位置の前に通過した位置と一致する位置がroute_配列内にあったら、その位置をelementに設定する
    for (before_element; before_element >= 0; before_element--) {
      if (route_[before_element].x == pos.before_x && route_[before_element].y == pos.before_y) {
        element = before_element;
        break;
      }
    }
  }

  for (int element_number = count - 1; element_number >= 0; element_number--) {
    //ゴールからスタートまでの経路を表示する
    DEBUG_PRINT_VAR(back_trace_[element_number].x);
    DEBUG_PRINT_VAR(back_trace_[element_number].y);

    //行き止まりの種類ごとに、それぞれに進む場合の最短経路を保存する
    switch (maptype) {

    case kFirstDeadEnd:
      route_first_deadend_[element_number].x = back_trace_[element_number].x;
      route_first_deadend_[element_number].y = back_trace_[element_number].y;
      break;

    case kSecondDeadEnd:
      route_second_deadend_[element_number].x = back_trace_[element_number].x;
      route_second_deadend_[element_number].y = back_trace_[element_number].y;
      break;

    case kThirdDeadEnd:
      route_third_deadend_[element_number].x = back_trace_[element_number].x;
      route_third_deadend_[element_number].y = back_trace_[element_number].y;
      break;
    }
  }

  return count;

}

/// <summary>
/// SetRouteCount関数の宣言
/// </summary>
/// <param = "route_count">最短経路でかかる歩数</param>
/// <param = "maptype">行き止まりの種類</param>
/// <returns>なし</returns>
void Field::SetRouteCount(int route_count, MapType maptype) {

  switch (maptype) {

  case kFirstDeadEnd:
    first_route_count_ = route_count;
    break;

  case kSecondDeadEnd:
    second_route_count_ = route_count;
    break;

  case kThirdDeadEnd:
    third_route_count_ = route_count;
    break;
  }
}

/// <summary>
/// GetRouteCount関数の宣言
/// </summary>
/// <param = "maptype">行き止まりの種類</param>
/// <returns>最短経路でかかる歩数/returns>
int Field::GetRouteCount(MapType maptype) {

  switch (maptype) {

  case kFirstDeadEnd:
    return first_route_count_;
    break;

  case kSecondDeadEnd:
    return second_route_count_;
    break;

  case kThirdDeadEnd:
    return third_route_count_;
    break;

  default:
    return kMaxRouteCount;
    break;
  }
}

/// <summary>
/// GetRoute関数の定義
/// </summary>
/// <param = "maptype">行き止まりの種類</param>
/// <returns>最短経路に含まれる座標/returns>
Field::Pos* Field::GetRoute(MapType maptype) {

  switch (maptype) {

  case kFirstDeadEnd:
    return route_first_deadend_;
    break;

  case kSecondDeadEnd:
    return route_second_deadend_;
    break;

  case kThirdDeadEnd:
    return route_third_deadend_;
    break;

  default:
    return nullptr;
    break;
  }

}

/// <summary>
/// SetFieldPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Field::SetFieldPhaseType(FieldPhaseType type) {
  field_phase_type_ = type;
}

/// <summary>
/// GetFieldPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Field::FieldPhaseType Field::GetFieldPhaseType() {
  return field_phase_type_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void Field::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int Field::GetBgmHandle() {
  return bgm_handle_;
}