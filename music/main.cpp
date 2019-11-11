#include <iostream>
#include <windows.h>
#include <irrKlang.h>
#include <queue>
#include <vector>
#include <stdlib.h>

using namespace irrklang;
using namespace std;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

int main(int argc, const char** argv) {
	// start the sound engine with default parameters
	ISoundEngine * music = createIrrKlangDevice();
	system("cls");
	music->play2D("./music/Do.wav", false);
	music->play2D("./music/Mi.wav", false);
	music->play2D("./music/Sol.wav", false);
	Sleep(500);
	music->play2D("./music/Le.wav", false);
	music->play2D("./music/Sol.wav", false);
	Sleep(500);
	music->play2D("./music/Si.wav", false);
	music->play2D("./music/Fa.wav", false);
	Sleep(500);
	music->play2D("./music/Do.wav", false);
	Sleep(500);

	int i;
	cin >> i;
	music->drop();
	return 0;
}
