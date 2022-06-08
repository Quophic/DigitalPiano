#pragma once

#include "Key.h"

#define KEY_NUM 88 							// ������88����
#define WK_NUM 52
#define BK_NUM 36

class Piano
{
private:
	WhiteKey* wKeyboard[WK_NUM];		// �׼�����
	BlackKey* bKeyboard[BK_NUM];		// �ڼ�����
	RECT kbArea;							// ��������
	// ��ɫ��ˢ �ȴ�����
	HBRUSH WKChbr;							// white key color
	HBRUSH WKHChbr;							// white key hit color
	HBRUSH BKChbr;
	HBRUSH BKHChbr;
	// �ڼ�λ�ü��� �ȼ�������λ�ö��кڼ�
	// ��������ʾ�Ǹ�λ���кڼ�
	bool bk[WK_NUM - 1];

public:
	Piano();
	Piano(RECT* area);
	~Piano();

	// ��Ӧ���ڱ仯 ���������������
	void SetSize(RECT* area);
	// �ּ�������
	bool IsHit(POINT* pt);
	void OnHit(POINT* pt);

	void KeyDown(POINT* pt, HDC hdc);
	void KeyUp(HDC hdc);
	// �ټ��Ļ���
	void OnPaint(HDC hdc);

};

