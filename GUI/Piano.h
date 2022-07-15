#pragma once

#include "Key.h"

#define KEY_NUM 88 							// 钢琴有88个键
#define WK_NUM 52
#define BK_NUM 36

typedef struct
{
	UINT8	keyIdx;		// 0保留/0区分黑白键/000000建索引
	size_t	delay;		// 与下一个音的间隔时间 毫秒
} Note, * PNote;


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

	void NoteProc(PNote notes, size_t n);
public:
	Piano();
	Piano(RECT* area);
	~Piano();

	// 响应窗口变化 不会填充整个区域
	void SetSize(RECT* area);
	// 处理点击
	bool IsHit(POINT* pt);
	void OnKeyDown();
	void OnWKDown(size_t idx);
	void OnWKUp(size_t idx);
	void OnBKDown(size_t idx);
	void OnBKUp(size_t idx);

	void OnHit(POINT* pt, HDC hdc);
	void OnKeyUp(HDC hdc);
	// 琴键的绘制
	void Paint(HDC hdc);

	void AutoPlay(PNote notes, size_t n);

};


