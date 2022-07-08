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
	virtual void PlayKeySound() = 0;

public:
	//static const LONG KEY_RATIO;		// �ټ��ĳ����
		
	RECT keyRc;							// �ټ��ڴ�������ռ����
	bool keyDown;						// �ټ��Ƿ񱻰���

	BaseKey(int index);

	void OnKeyUp();

	void SetKeyRc(POINT* position, LONG width, LONG height);
	bool IsHit(POINT* pt);
	// �û��ټ����� ÿ��������ͬ
	void OnHit();
	// ���������Ҫpiano�ഫ������ˢ
	void Paint(HDC hdc, HBRUSH hbr);
};

class WhiteKey : public BaseKey
{
private:
	void PlayKeySound();
public:
	WhiteKey(int index);

};

class BlackKey : public BaseKey
{
private:
	void PlayKeySound();
public:
	BlackKey(int index);

};