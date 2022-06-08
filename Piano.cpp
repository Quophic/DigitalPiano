#include "Piano.h"
#include "Key.h"
#include <windows.h>

Piano::Piano() :
	WKChbr(CreateSolidBrush(WK_COLOR)),
	WKHChbr(CreateSolidBrush(WK_HITCOLOR)),
	BKChbr(CreateSolidBrush(BK_COLOR)),
	BKHChbr(CreateSolidBrush(BK_HITCOLOR)),
	bk{
		true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
		true , true , false, true , true , true , false,
}
{
	for (int i = 0; i < WK_NUM; i++)
	{
		wKeyboard[i] = new WhiteKey(i);
	}
	for (int i = 0; i < BK_NUM; i++)
	{
		bKeyboard[i] = new BlackKey(i);
	}
}

Piano::Piano(RECT* area)
{
	Piano();
	SetSize(area);
}

Piano::~Piano()
{
	DeleteObject(WKChbr);
	DeleteObject(WKHChbr);
	DeleteObject(BKChbr);
	DeleteObject(BKHChbr);
}

void Piano::SetSize(RECT* area)
{
	LONG w = area->right - area->left;
	LONG h = area->bottom - area->top;

	LONG kw = (w - WK_NUM + 1) / WK_NUM;
	LONG kh = kw * WK_RATIO;
	// 保证琴键在范围内
	if (kh > h)
	{
		kw = h / WK_RATIO;
	}
	kh = kw * WK_RATIO;
	LONG kbw = kw * WK_NUM + WK_NUM - 1;
	LONG kbh = kh;
	// 置底居中
	kbArea.left = area->left + (w - kbw) / 2;
	kbArea.right = kbArea.left + kbw;
	kbArea.bottom = area->bottom;
	kbArea.top = kbArea.bottom - kbh;
	// 白键之间间隔一像素
	// 黑键根据间隔来绘制
	POINT pt;
	pt.x = kbArea.left;
	pt.y = kbArea.bottom - kbh;
	wKeyboard[0]->SetKeyRc(&pt, kw, kh);
	int j = 0;
	for (int i = 1; i < WK_NUM; i++)
	{
		pt.x += kw + 1;
		wKeyboard[i]->SetKeyRc(&pt, kw, kh);
		if (bk[i - 1])
		{
			pt.x -= kw / 2;
			bKeyboard[j++]->SetKeyRc(&pt, kw, kw * BK_RATIO);
			pt.x += kw / 2;
		}
	}
	pt.x = kbArea.left + kw / 2;

}

bool Piano::IsHit(POINT* pt)
{
	if (pt->x <= kbArea.right && pt->x >= kbArea.left && pt->y <= kbArea.bottom && pt->y >= kbArea.top)
	{
		return true;
	}
	return false;
}

void Piano::OnHit(POINT* pt)
{
	
	for (int i = 0; i < BK_NUM; i++)
	{
		if (bKeyboard[i]->keyDown)
		{
			bKeyboard[i]->OnHit();
		}
	}
	for (int i = 0; i < WK_NUM; i++)
	{
		if (wKeyboard[i]->keyDown)
		{
			wKeyboard[i]->OnHit();
		}
	}
}

void Piano::KeyDown(POINT* pt, HDC hdc)
{
	if (!IsHit(pt))
	{
		return;
	}
	
	bool bkHit = false;
	// 所有琴键检测鼠标点击
	for (int i = 0; i < BK_NUM; i++)
	{
		if (bKeyboard[i]->IsHit(pt))
		{
			bkHit = true;
		}
	}
	// 黑键在白键上面， 点击黑键就不触发白键了 
	if (!bkHit) {
		for (int i = 0; i < WK_NUM; i++)
		{
			wKeyboard[i]->IsHit(pt);
		}
	}
	OnPaint(hdc);
	OnHit(pt);
}

void Piano::KeyUp(HDC hdc)
{
	for (int i = 0; i < WK_NUM; i++)
	{
		wKeyboard[i]->KeyUp();
	}
	for (int i = 0; i < BK_NUM; i++)
	{
		bKeyboard[i]->KeyUp();
	}
	OnPaint(hdc);
}

void Piano::OnPaint(HDC hdc)
{
	for (int i = 0; i < WK_NUM; i++)
	{
		if (wKeyboard[i]->keyDown)
		{
			wKeyboard[i]->OnPaint(hdc, WKHChbr);
		}
		else
		{
			wKeyboard[i]->OnPaint(hdc, WKChbr);
		}
	}
	for (int i = 0; i < BK_NUM; i++)
	{
		if (bKeyboard[i]->keyDown)
		{
			bKeyboard[i]->OnPaint(hdc, BKHChbr);
		}
		else
		{
			bKeyboard[i]->OnPaint(hdc, BKChbr);
		}
	}
}