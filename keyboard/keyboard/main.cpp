#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_status status = game_status::Init; // ���� ���� ǥ��
	string filename = "music";	// filename ����
	thread thread_recording(Record, &status, &filename); // ������ ������
	
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");
		
	
	do {
		status = game_status::Start;
		
		play_game();

		status = game_status::GameOver;
	} while (game_over());//���ӿ��� ���Ҷ�����
	
	status = game_status::End;
	thread_recording.join(); // ������ ������� ���

	return 0;
}