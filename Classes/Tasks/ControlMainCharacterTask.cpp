//
//  ControlMainCharacterTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#include "Tasks/ControlMainCharacterTask.h"

#include "Scenes/DungeonScene.h"

#include "Layers/Dungeon/TiledMapLayer.h"

#include "MapObjects/Character.h"

#include "MapObjects/MapObjectList.h"

// コンストラクタ
ControlMainCharacterTask::ControlMainCharacterTask(){FUNCLOG}

// デストラクタ
ControlMainCharacterTask::~ControlMainCharacterTask(){FUNCLOG}

// 初期化
bool ControlMainCharacterTask::init(DungeonScene* dungeonScene)
{
    this->scene = dungeonScene;
    
    return true;
}

// 向きを変える
void ControlMainCharacterTask::turn(const Direction& direction)
{
    Character* mainCharacter {this->scene->mapLayer->getMapObjectList()->getMainCharacter()};
    if(!mainCharacter->isMoving()) mainCharacter->setDirection(direction);
}

// 目の前を調べる
void ControlMainCharacterTask::search()
{
    MapObjectList* objectList {this->scene->mapLayer->getMapObjectList()};
    Character* mainCharacter {objectList->getMainCharacter()};
    
    Vector<MapObject*> objs { objectList->getMapObjects(mainCharacter->getCollisionRect(mainCharacter->getDirection()))};
    
    // 現状イベントスクリプトに実行待ちを実装していないため現状はこんな感じで
    for(MapObject* obj : objs)
    {
        if(obj && obj->getTrigger() == Trigger::SEARCH)
        {
            this->scene->runEvent(obj->getEventId());
            return;
        }
    }
}

// 歩行中、あたり判定を行い次に向かう位置を決定する
void ControlMainCharacterTask::walking(vector<Direction> directions)
{
    TiledMapLayer* mapLayer {this->scene->mapLayer};
    Character* mainCharacter {mapLayer->getMapObjectList()->getMainCharacter()};
    
    mainCharacter->setDirection(directions.back());
    
    int directionCount {(directions.size() >= 2 && directions.back() != directions.at(directions.size() - 2) && static_cast<int>(directions.back()) + static_cast<int>(directions.at(directions.size() - 2)) != 3)?static_cast<int>(directions.size()):1};
    
    bool isHit {(directionCount > 1)?mainCharacter->isHit({directions.back(), directions.at(directionCount - 2)}):false};
    
    Point movement {Point::ZERO};
    
    for(int i {static_cast<int>(directions.size()) - 1}; i >= static_cast<int>(directions.size()) - directionCount; i--)
    {
        if((!isHit && !mainCharacter->isHit(directions.at(i))) || (isHit && !mainCharacter->isHit(directions.at(i)) && movement == Point::ZERO))
        {
            movement += MapUtils::getGridVector(directions.at(i));
        }
    }
    
    if(movement == Point::ZERO) return;
    mainCharacter->setMoving(true);
    this->scene->runAction(Sequence::createWithTwoActions(mainCharacter->createWalkByAction(movement), CallFunc::create([this](){this->onCharacterWalkedOneGrid();})));
    this->scene->runAction(Sequence::createWithTwoActions(DelayTime::create(Character::DURATION_FOR_ONE_STEP), CallFunc::create([mainCharacter](){mainCharacter->setMoving(false);})));
}

// 一マス分移動し終えた時
void ControlMainCharacterTask::onCharacterWalkedOneGrid()
{
    TiledMapLayer* mapLayer {this->scene->mapLayer};

    // 衝突判定用Rectの中心座標にあるイベントを呼ぶ
    Rect collisionRect {mapLayer->getMapObjectList()->getMainCharacter()->getCollisionRect()};
    Point checkPosition {Point(collisionRect.getMidX(), collisionRect.getMidY())};
    MapObject* obj { mapLayer->getMapObjectList()->getMapObject(checkPosition)};
    
    if(!obj)
    {
        this->riddenEventID = static_cast<int>(EventID::UNDIFINED);
        return;
    }
    
    // 現在乗っているマスのイベントを発動しないようにして、イベントを呼ぶ
    if(obj && obj->getTrigger() == Trigger::RIDE && obj->getEventId() != this->riddenEventID)
    {
        this->riddenEventID = obj->getEventId();
        this->scene->runEvent(obj->getEventId());
    }
}