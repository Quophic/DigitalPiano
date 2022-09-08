#include "MusicScoreParse.h"

#define FBIT(byte) (byte & 0x80)
#define SBIT(byte) (byte & 0x40)
#define LBIT(byte) (byte & 0x3f)
#define ABSO(byte) ((byte ^ 0xff) + 1)

void MSParser(BYTE* mScore, size_t s)
{
	bool isPitch = true;
	if (mScore == NULL || s == 0)
	{
		return;
	}
	for(size_t i = 0; i < s; i++)
	{
		if (isPitch)
		{
			if (FBIT(mScore[i]))
			{
				isPitch = false;
			}

			if (SBIT(mScore[i]))
			{
				// TODO
			}
			else
			{
				// TODO
			}
		}
		else
		{
			isPitch = true;
			if (FBIT(mScore[i]))
			{
				Sleep(BEAT / ABSO(mScore[i]));
			}
			else
			{
				Sleep(BEAT * mScore[i]);
			}
		}
		
	}
}

void MSLoad(BYTE* mScore, size_t* s, char* str)
{
	
}