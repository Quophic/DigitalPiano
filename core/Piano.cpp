#include "piano.h"
#include <windows.h>
#include <iostream>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

TestKey::TestKey(int idx):pitchIndex(idx){
}

void TestKey::SetNoteOn() {
	std::cout << pitchIndex << " ";
}

void TestKey::SetNoteOff() {
}

TestKeyboard::TestKeyboard() : pParser(nullptr) {
	for (int i = 0; i < MAXKEYNUM; i++) {
		keys[i] = new TestKey(i);
	}
}

void TestKeyboard::PlayNotes(char* notes){
	int idx = 0;
	if (*notes == '\0' || this->pParser == nullptr) return;
	while (*notes == ' ') notes++;
	while (*notes != '\0') {
		if ((idx = pParser->ParseAPitch(&notes)) < 0) return;
		PlayNoteWithIdx(idx);
		while (*notes == ' ') notes++;
	}
	std::cout << std::endl;
}

void TestKeyboard::SetParser(PitchParser* pParser) {
	this->pParser = pParser;
}

void TestKeyboard::PlayNoteWithIdx(int noteIdx) {
	if (noteIdx < 0 || noteIdx >= MAXKEYNUM) return;
	if (keys[noteIdx] == nullptr) return;
	keys[noteIdx]->SetNoteOn();
}

int TestParser::ParseAPitch(char** pitch) {
	int noteIdx = 0, N = 0, O = 0;
	if (*pitch == nullptr) return -1;
	if((N = ParseN(pitch)) == -100) return -1;
	if((O = ParseO(pitch)) < 0) return -1;
	if (N < 0) O = -O;
	noteIdx = N + O * 12 + 26;
	noteIdx = MIN(noteIdx, MAXKEYNUM - 1);
	noteIdx = MAX(noteIdx, 0);
	return noteIdx;
}

int TestParser::ParseN(char** c) {
	int N = 0;
	if (*c == nullptr || **c == ' ' || **c == '\0') return -1;
	if (**c == '#') {
		N += 1;
		(*c)++;
	}
	switch (**c) {
	case 'C':
		N -= 12;
		break;
	case 'D':
		N -= 10;
		break;
	case 'E':
		N -= 8;
		break;
	case 'F':
		N -= 7;
		break;
	case 'G':
		N -= 5;
		break;
	case 'A':
		N -= 3;
		break;
	case 'B':
		N -= 1;
		break;
	case 'c':
		N += 0;
		break;
	case 'd':
		N += 2;
		break;
	case 'e':
		N += 4;
		break;
	case 'f':
		N += 5;
		break;
	case 'g':
		N += 7;
		break;
	case 'a':
		N += 9;
		break;
	case 'b':
		N += 11;
		break;
	default:
		return -100; // ´íÎó·µ»ØÒª³¬³ö¼üÎ»·¶Î§
	}
	(*c)++;
	if (**c == '#') {
		N += 1;
		(*c)++;
	}
	return N;
}

int TestParser::ParseO(char** c) {
	int O = 0;
	if (*c == nullptr) return -1;
	if (**c == ' ' || **c == '\0') return 0;
	O = **c - '0';
	if (O < 0 || O > 9) return 0;
	(*c)++;
	return O;
}