#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <windows.h>
#include <irrKlang.h>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <thread>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;
using namespace std;

void music_start(vector<vector<int> > & note, ISoundEngine * music, int & bpm, bool & playing);
void music_changer(vector<vector<int> > & note, int length);
void note_push(vector<int> & note, int sound);
void clear_note(vector<vector<int> > & note, int nesting);

#endif
