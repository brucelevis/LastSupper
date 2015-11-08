//
//  ItemMenuLayer.hpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/01.
//
//

#ifndef ItemMenuLayer_h
#define ItemMenuLayer_h

#include "Layers/Menu/MenuLayer.h"

class MiniSelector;

class ItemMenuLayer : public MenuLayer
{
    // クラスメソッド
public:
    CREATE_FUNC(ItemMenuLayer)
    virtual bool init();
    
    // クラス変数
private:
    static const float INNER_H_MARGIN_RATIO;
    static const float INNER_V_MARGIN_RATIO;
    
    // インスタンスメソッド
private:
    virtual void onIndexChanged(int newIdx, bool sound);
    virtual void onSpacePressed(int idx);
    virtual void onMenuKeyPressed();
    void changeItemDiscription(const int idx);
    void createMiniSelector();
    void onMiniSelectorCanceled();
    void onMiniIndexSelected(const int idx);
protected:
    ItemMenuLayer();
    ~ItemMenuLayer();
public:
    virtual void show() override;
    virtual void hide() override;
    
    // インスタンス変数
private:
    vector<int> items {};
    MiniSelector* miniSelector {nullptr};
public:
    function<void()> onItemMenuCanceled { nullptr };
    //function<void()> onSaveDataSelectCancelled { nullptr };
};
#endif /* ItemMenuLayer_h */
