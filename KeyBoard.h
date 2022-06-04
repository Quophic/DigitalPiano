#pragma once

#include <iostream>

// 音频变调混音算法
// 计算音乐

typedef long Pitch;
#define C 100L

class Key
{
private:
	std::string m_name;
	Pitch m_pitch;				// 音高
public:
	static void MakeSound(Pitch m_pitch);
	// no allowed to create a key without specify
	Key(std::string m_name, Pitch m_pitch);
	void MakeSound();
};
