#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_status status = Init; // ���� ���� ǥ��
	std::thread thread_recording(Record, &status); // ������ ������
	
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");

	
	do {
		status = Start;
		
		play_game();

		status = GameOver;
	} while (game_over());//���ӿ��� ���Ҷ�����
	
	status = End;
	thread_recording.join(); // ������ ������� ���

	return 0;
}