//
//  SceneEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#ifndef __LastSupper__SceneEvent__
#define __LastSupper__SceneEvent__

#include "Event/GameEvent.h"

// マップ移動イベント
class ChangeMapEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(ChangeMapEvent, rapidjson::Value&)
private:
    Location location {};
    int initEventId { etoi(EventID::UNDIFINED) };
private:
    ChangeMapEvent() {FUNCLOG};
    ~ChangeMapEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run();
};

// カメラ生成イベント
class CreateCameraEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CreateCameraEvent, rapidjson::Value&)
private:
    Location location {};
    int objId { etoi(ObjectID::UNDIFINED) };
    GameEvent* event { nullptr };
private:
    CreateCameraEvent() { FUNCLOG };
    ~CreateCameraEvent() { FUNCLOG };
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// カメラ移動イベント
class MoveCameraEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(MoveCameraEvent, rapidjson::Value&)
private:
    Point toPosition { Point::ZERO };
    float duration { 0.f };
private:
    MoveCameraEvent() {FUNCLOG};
    ~MoveCameraEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// waitイベント
class WaitEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(WaitEvent, rapidjson::Value&)
private:
    float duration {0.f};
private:
    WaitEvent() {FUNCLOG};
    ~WaitEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// FadeOutイベント
class FadeOutEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(FadeOutEvent, rapidjson::Value&)
private:
    Color3B color { Color3B::BLACK };
    float duration { 0.5f };
private:
    FadeOutEvent() {FUNCLOG};
    ~FadeOutEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// FadeInイベント
class FadeInEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(FadeInEvent, rapidjson::Value&)
private:
    float duration { 0.5f };
private:
    FadeInEvent() {FUNCLOG};
    ~FadeInEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// CountDownイベント
class CountDownEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CountDownEvent, rapidjson::Value&)
private:
    float second { 5.f };
    int sEventId { static_cast<int>(EventID::UNDIFINED) };
    int fEventId { static_cast<int>(EventID::UNDIFINED) };
    //rapidjson::Document doc { nullptr };
    int equip {0};
    bool checkEquip {false};
    GameEvent* sEvent { nullptr };
    GameEvent* fEvent { nullptr };
    GameEvent* event { nullptr };
private:
    CountDownEvent() {FUNCLOG};
    ~CountDownEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// StopCountイベント
class StopCountEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(StopCountEvent, rapidjson::Value&);
private:
    StopCountEvent() {FUNCLOG};
    ~StopCountEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};


#endif /* defined(__LastSupper__SceneEvent__) */