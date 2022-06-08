#pragma once

#include "Key.h"

#define KEY_NUM 88 							// 钢琴有88个键
#define WK_NUM 52
#define BK_NUM 36

class Piano
{
private:
	WhiteKey* wKeyboard[WK_NUM];		// 白键数组
	BlackKey* bKeyboard[BK_NUM];		// 黑键数组
	RECT kbArea;							// 键盘区域
	// 颜色笔刷 先创建好
	HBRUSH WKChbr;							// white key color
	HBRUSH WKHChbr;							// white key hit color
	HBRUSH BKChbr;
	HBRUSH BKHChbr;
	// 黑键位置计算 先假设所有位置都有黑键
	// 这个数组表示那个位置有黑键
	bool bk[WK_NUM - 1];

public:
	Piano();
	Piano(RECT* area);
	~Piano();

	// 响应窗口变化 不会填充整个区域
	void SetSize(RECT* area);
	// 分级处理点击
	bool IsHit(POINT* pt);
	void OnHit(POINT* pt);

	void KeyDown(POINT* pt, HDC hdc);
	void KeyUp(HDC hdc);
	// 琴键的绘制
	void OnPaint(HDC hdc);

};

