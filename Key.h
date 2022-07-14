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
	virtual void StartPlaySound() = 0;
	virtual void StopPlaySound() = 0;

	void OnKeyDown();
	void OnKeyUp();

	void SetKeyRc(POINT* position, LONG width, LONG height);
	bool IsHit(POINT* pt);
	// �û��ټ����� ÿ��������ͬ
	// ���������Ҫpiano�ഫ������ˢ
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