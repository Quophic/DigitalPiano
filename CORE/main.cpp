#include "Piano.h"
#include <iostream>
//#pragma comment (lib, "winmm.lib")
using namespace std;
int main() {
	char buf[128];
	TestKeyboard tk = TestKeyboard();
	tk.SetParser(new TestParser());
	cin >> buf;
	while (*buf != 'q')
	{
		tk.PlayNotes(buf);
		cin >> buf;
	}
}