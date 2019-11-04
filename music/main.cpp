#include <iostream>
#include <irrKlang.h>
#include <queue>
#include <vector>

using namespace irrklang;
using namespace std;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

int main(int argc, const char** argv) {
	// start the sound engine with default parameters
	vector<vector<ISoundEngine *>> music(16, vector<ISoundEngine *>(14, NULL));
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 14; j++) {
			music[i][j] = createIrrKlangDevice();
		}
	}

	vector<queue<int>> note;


	music[0][0]->play2D("./music/Do.wav", false);
	music[0][1]->play2D("./music/Mi.wav", false);
	music[0][2]->play2D("./music/Sol.wav", false);
	int i;
	cin >> i;
	//music[0][0]->drop();
	return 0;
}