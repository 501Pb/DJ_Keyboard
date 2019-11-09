#include "DJ.h"
#include "Recording.h"

int main(void) {
	game_init();//���� �ʱ⼳��
	title();//Ÿ��Ʋ
	system("cls");

	game_status status = game_status::Start;

	do {
		std::thread thread_recording(Record, &status);
		
		play_game();

		status = game_status::End;
	} while (game_over());//���ӿ��� ���Ҷ�����
	thread_recording.join();

	return 0;
}