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

void musicStart(vector<vector<int> > & note, ISoundEngine * music, int bpm, bool & playing);
void musicChanger(vector<vector<int> > & note, int length);
void notePush(vector<int> & note, int sound);
void clearNote(vector<vector<int> > & note, int nesting);

#endif