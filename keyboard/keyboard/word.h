#pragma once
#include <string>
using namespace std;
class Word {
	string name;
	//단어내용
	//음계

public:
	Word() {}
	Word(string name) {
		this->name = name;
	}
	string get_name() { return name; }
	//음계활성화 함수
};
