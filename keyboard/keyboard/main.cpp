#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_status status = game_status::Init; // ���� ���� ǥ��
	string filename = "music";	// filename ����
	thread thread_recording(Record, &status, &filename); // ������ ������
	
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");
			
	while (1) {
		status = game_status::Start;

		if (menu_function() == 1) break; //menu_function()�Լ��� 1�� ��ȯ�ϸ� ���� ������.
		
		status = game_status::GameOver;
	}

	status = game_status::End;
	thread_recording.join(); // ������ ������� ���

	return 0;
}