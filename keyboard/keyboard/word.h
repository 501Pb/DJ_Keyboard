#pragma once
#include <string>
using namespace std;
class Word {
	string name;
	//�ܾ��
	//����

public:
	Word() {}
	Word(string name) {
		this->name = name;
	}
	string get_name() { return name; }
	//����Ȱ��ȭ �Լ�
};
