#pragma once

#include <iostream>

// ��Ƶ��������㷨
// ��������

typedef long Pitch;
#define C 100L

class Key
{
private:
	std::string m_name;
	Pitch m_pitch;				// ����
public:
	static void MakeSound(Pitch m_pitch);
	// no allowed to create a key without specify
	Key(std::string m_name, Pitch m_pitch);
	void MakeSound();
};
