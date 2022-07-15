#pragma once
#include <windows.h>

#define WK_COLOR	RGB(255, 255, 255)	// 白键颜色
#define WK_HITCOLOR RGB(200, 200, 200)	// 白键反馈颜色
#define WK_RATIO	6					// 白键长宽比

#define BK_COLOR	RGB(  0,   0,   0)	// 黑键颜色
#define BK_HITCOLOR RGB(100, 100, 100)	// 黑键反馈颜色
#define BK_RATIO	3					// 黑键长宽比

class BaseKey
{
protected:
	int index;							// keysound 文件夹黑白键声音文件索引

public:
	//static const LONG KEY_RATIO;		// 琴键的长宽比
		
	RECT keyRc;							// 琴键在窗口中所占区域
	bool keyDown;						// 琴键是否被按下

	BaseKey(int index);
	virtual void StartPlaySound() = 0;
	virtual void StopPlaySound() = 0;

	void OnKeyDown();
	void OnKeyUp();

	void SetKeyRc(POINT* position, LONG width, LONG height);
	bool IsHit(POINT* pt);
	// 敲击琴键发声 每个键都不同
	// 这个方法需要piano类传给他笔刷
	void Paint(HDC hdc, HBRUSH hbr);
};

class WhiteKey : public BaseKey
{
private:
public:
	void StartPlaySound();
	void StopPlaySound();
	WhiteKey(int index);

};

class BlackKey : public BaseKey
{
private:
public:
	void StartPlaySound();
	void StopPlaySound();
	BlackKey(int index);

};