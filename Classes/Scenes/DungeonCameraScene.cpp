//
//  DungeonCameraScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#include "Scenes/DungeonCameraScene.h"

// コンストラクタ
DungeonCameraScene::DungeonCameraScene() { FUNCLOG };

// デストラクタ
DungeonCameraScene::~DungeonCameraScene() { FUNCLOG };

// 初期化
bool DungeonCameraScene::init(DungeonSceneData* data, Vector<GameEvent*> events)
{
    return true;
}

// シーン切り替え終了時
void DungeonCameraScene::onEnter()
{
    baseScene::onEnter();
}

// プリロード終了時
void DungeonCameraScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    
}