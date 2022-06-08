#pragma once
#include <windows.h>

#define WK_COLOR	RGB(255, 255, 255)	// �׼���ɫ
#define WK_HITCOLOR RGB(200, 200, 200)	// �׼�������ɫ
#define WK_RATIO	6					// �׼������

#define BK_COLOR	RGB(  0,   0,   0)	// �ڼ���ɫ
#define BK_HITCOLOR RGB(100, 100, 100)	// �ڼ�������ɫ
#define BK_RATIO	3					// �ڼ������

class BaseKey
{
protected:
	int index;							// keysound �ļ��кڰ׼������ļ�����

public:
	//static const LONG KEY_RATIO;		// �ټ��ĳ����

	RECT keyRc;							// �ټ��ڴ�������ռ����
	bool keyDown;						// �ټ��Ƿ񱻰���

	BaseKey(int index);

	void KeyDown(POINT* pt, HDC hdc, HBRUSH hbr);
	void KeyUp();

	void SetKeyRc(POINT* position, LONG width, LONG height);
	bool IsHit(POINT* pt);
	// �û��ټ����� ÿ��������ͬ
	virtual void OnHit() = 0;
	// ���������Ҫpiano�ഫ������ˢ
	void OnPaint(HDC hdc, HBRUSH hbr);
};

class WhiteKey : public BaseKey
{
public:
	WhiteKey(int index);
	void OnHit();
};

class BlackKey : public BaseKey
{
public:
	BlackKey(int index);
	void OnHit();
};