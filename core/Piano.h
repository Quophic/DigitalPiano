#pragma once
#define MAXKEYNUM 88
//#include <windows.h>

class Key {
public:
	virtual void SetNoteOn() = 0;
	virtual void SetNoteOff() = 0;
};
class TestKey : public Key {
public:
	TestKey(int idx);
	virtual void SetNoteOn();
	virtual void SetNoteOff();
private:
	int pitchIndex;
};

class PitchParser {
public:
	virtual int ParseAPitch(char** pitch) { return 0; };
};


class TestKeyboard {
public:
	TestKeyboard();
	void PlayNotes(char* notes);
	void SetParser(PitchParser* pParser);
private:
	void PlayNoteWithIdx(int noteIdx);
	PitchParser* pParser;
	Key* keys[MAXKEYNUM];
};


class TestParser : public PitchParser {
public:
	int ParseAPitch(char** pitch);
private:
	int ParseN(char** c);
	int ParseO(char** c);
	
};