//
//  DungeonScene.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Scenes/baseScene.h"

class TiledMapLayer;

class DungeonScene : public baseScene
{
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(DungeonScene);
	
	// インスタンスメソッド
private:
	DungeonScene();
	~DungeonScene();
	virtual bool init();
	void onPreloadFinished();
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener { nullptr };
	TiledMapLayer* mapLayer { nullptr };
};


#endif // __DUNGEON_SCENE_H__
