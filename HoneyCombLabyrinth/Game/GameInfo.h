﻿#pragma once
#include "System/LogConsole.h"

/// <summary>
/// GameInfoクラス
/// </summary>
class GameInfo {

private:
  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  GameInfo();

public:

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~GameInfo();

  /// <summary>
  /// インスタンスを生成する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void CreateInstance();

  /// <summary>
  /// インスタンスを取得する
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲーム情報のインスタンス</returns>
  static GameInfo* GetInstance();

  /// <summary>
  /// インスタンスを解放する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void ReleaseInstance();

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void InitGameInfo();

  /// <summary>
  /// GetResolutionXSize関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>解像度のXサイズ</returns>
  int GetResolutionXSize();

  /// <summary>
  /// GetResolutionYSize関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>解像度のYサイズ</returns>
  int GetResolutionYSize();

  /// <summary>
  /// GetCenterX関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画面の中心のX座標</returns>
  int GetCenterX();

  /// <summary>
  /// GetCenterY関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画面の中心のY座標</returns>
  int GetCenterY();

  /// <summary>
  /// SetMapSize関数の宣言
  /// </summary>
  /// <param>mapのXサイズ、Yサイズ</param>
  /// <returns>なし</returns>
  void SetMapSize(int x, int y);

  /// <summary>
  /// GetMapLeftX関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>マップの左上のX座標</returns>
  int GetMapLeftX();

  /// <summary>
  /// GetMapLeftY関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>マップの左上のY座標</returns>
  int GetMapLeftY();

  /// <summary>
  /// SetIsGameClear関数の宣言
  /// </summary>
  /// <param="game_clear">ゲームクリアかの有無</param>
  /// <returns>なし</returns>
  void SetIsGameClear(bool game_clear);

  /// <summary>
  /// GetIsGameClear関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームクリアかの有無</returns>
  bool GetIsGameClear();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //インスタンス
  /// </summary>
  static GameInfo* game_info_;

  /// <summary>
  /// 解像度のXサイズ
  /// </summary>
  int resolution_x_size_;

  /// <summary>
  /// 解像度のYサイズ
  /// </summary>
  int resolution_y_size_;

  /// <summary>
  /// 画像の中心のX座標
  /// </summary>
  int center_x_;

  /// <summary>
  /// 画像の中心のY座標
  /// </summary>
  int center_y_;

  /// <summary>
  /// マップのXサイズ
  /// </summary>
  int map_x_size_;

  /// <summary>
  /// マップのYサイズ
  /// </summary>
  int map_y_size_;

  /// <summary>
  /// マップの左のX座標
  /// </summary>
  int map_left_x_;

  /// <summary>
  /// マップの左のY座標
  /// </summary>
  int map_left_y_;

  /// <summary>
  /// ゲームクリアかの有無
  /// </summary>
  bool game_clear_;
};