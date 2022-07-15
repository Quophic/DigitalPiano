#pragma once

#include "Key.h"

#define KEY_NUM 88 							// ������88����
#define WK_NUM 52
#define BK_NUM 36

typedef struct
{
	UINT8	keyIdx;		// 0����/0���ֺڰ׼�/000000������
	size_t	delay;		// ����һ�����ļ��ʱ�� ����
} Note, * PNote;


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

	void NoteProc(PNote notes, size_t n);
public:
	Piano();
	Piano(RECT* area);
	~Piano();

	// ��Ӧ���ڱ仯 ���������������
	void SetSize(RECT* area);
	// ������
	bool IsHit(POINT* pt);
	void OnKeyDown();
	void OnWKDown(size_t idx);
	void OnWKUp(size_t idx);
	void OnBKDown(size_t idx);
	void OnBKUp(size_t idx);

	void OnHit(POINT* pt, HDC hdc);
	void OnKeyUp(HDC hdc);
	// �ټ��Ļ���
	void Paint(HDC hdc);

	void AutoPlay(PNote notes, size_t n);

};


