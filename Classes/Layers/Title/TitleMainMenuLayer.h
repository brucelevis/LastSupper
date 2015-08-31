//
//  TitleMainMenuLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#ifndef __TITLE_MAIN_MENU_LAYER_H__
#define __TITLE_MAIN_MENU_LAYER_H__

#include "Layers/baseMenuLayer.h"

class TitleMainMenuLayer : public baseMenuLayer
{
	// 列挙型、構造他
public:
	enum struct MenuType
	{
		START,
		CONTINUE,
		EXIT,
		
		SIZE
	};
	
	// クラスメソッド
public:
	CREATE_FUNC(TitleMainMenuLayer);
	
	// クラス変数
private:
	static const map<MenuType, string> menu;
	
	// インスタンスメソッド
private:
	TitleMainMenuLayer();
	~TitleMainMenuLayer();
	virtual bool init();
	void onIndexChanged(bool sound);
	void onSpacePressed();
public:
	void show();
	void hide();
	
	// インスタンス変数
public:
	function<void()> onStartSelected { nullptr };
	function<void()> onContinueSelected { nullptr};
	function<void()> onExitSelected { nullptr };
};

#endif // __TITLE_MAIN_MENU_LAYER_H__
