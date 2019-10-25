/*
	DJ_Keyboard
	나성 : 음악 파일 구조체
	현빈 : 음악 파일 재생
	수빈 : 게임 틀 제작
	광호 : 파일 저장
*/
#include "DJ.h"
#include "word.h"

#define KEY_ENTER '\n'
#define KEY_BS '\b'

#define MAX_WORD_LENGTH 24
#define MAX_SCREEN_WORD_COUNT 19
#define WORD_COUNT 11

//int g_word_count = 11;
char** g_word;
//string* g_word;
//int g_fail_count = 0;                           // 실패한 개수
//int g_score = 0;                                // 정수
char g_input_word[MAX_WORD_LENGTH + 1];         // 입력 단어 저장


Word g_screen_word[100];// 화면에 나타난 단어들(g_words의 원소 index 저장)
int g_screen_word_count = 0;                    // 화면에 나타난 단어 개수
clock_t g_start_time;                           // 기준 시각
double g_falling_speed = 2.0;                   // 단어 낙하 시각(초 단위)

void create_word(void) {
	//파일에서 단어 이름과 음계를 추출해온다??
	//알파벳에 맞는 멜로디?
}



//////////////////////////////////////////////////////////////////////////////////////////

void game_init(void) {
	g_start_time = clock();
	//시드
	srand((unsigned int)time(NULL));
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void title(void) {
	//PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cout << "\n\n\n\n";
	cout << "\t ______       ___          ___   _  _______  __   __  _______  _______  _______  ______    ______  \t" << endl;
	cout << "\t |      |     |   |        |   | | ||       ||  | |  ||  _    ||       ||   _   ||    _ |  |      | \t" << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |\t" << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |\t" << endl;
	cout << "\t | | |   |    |   |        |      _||   |___ |       ||       ||  | |  ||       ||   |_||_ | | |   |\t" << endl;
	cout << "\t | |_|   | ___|   |        |     |_ |    ___||_     _||  _   | |  |_|  ||       ||    __  || |_|   |\t" << endl;
	cout << "\t |       ||       | _____  |    _  ||   |___   |   |  | |_|   ||       ||   _   ||   |  | ||       |\t" << endl;
	cout << "\t |______| |_______||_____| |___| |_||_______|  |___|  |_______||_______||__| |__||___|  |_||______| \t" << endl;
	cout << "\n\n\n\n";

	while (1) {
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(1000);
		cout << "\r\t \t \t \t \t \t                 ";
		Sleep(1000);
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	system("cls");
}


void play_game(void) {
	printf("┌──────────────────────────────────────────────────────────────────────────┐\n");
	for (int i = 0; i < 19; i++)
		printf("│                                                                          │\n");
	printf("└──────────────────────────────────────────────────────────────────────────┘\n");
	//cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "____________________________________________________________________________" << endl;
	string s;	cout << ">> ";	cin >> s;
	if (s == "subin") {
		system("cls");
		return;
	}
	else {
		system("cls");
		return play_game();
	}
}
bool game_over(void) {
	cout << "\n\n\n\n";
	cout << "\t┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬┌─┐┬─┐" << endl;
	cout << "\t│ ┬├─┤│││├┤   │ │└┐┌┘├┤ ├┬┘" << endl;
	cout << "\t└─┘┴ ┴┴ ┴└─┘  └─┘ └┘ └─┘┴└─" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) "<<endl;

	string s;	cout << "\t>> ";	cin >> s;
	if (s == "y"||s=="Y") {
		system("cls");
		return true;
	}
	else {
		system("cls");
		return false;
	}
}
void make_random(void) {
	cout << "random 10 number make : ";
	for (int i = 0; i < 10; i++) {
		cout << rand() % 17 << " ";
	}
}
#define WORD_NUM 4
void InitData(void)
{
	int cnt = 0;
	Word wd[WORD_NUM];
	string filePath = "g_words.txt";
	
	ifstream openFile(filePath.data());
	if (openFile.is_open()) {
		string line;
		while (getline(openFile, line)){
			wd[cnt]=Word(line);
			cout << line << endl;
			cnt++;
		}
		openFile.close();
	}
	cout << endl << endl;
	cout << "word array" << endl << endl;
	for (auto i : wd) {
		cout << i.get_name() << " ";
	}
	cout << endl<<endl;

	////g_words = new string[cnt];
	//g_words = (char**)malloc(sizeof(char*) * (WORD_COUNT + 1));

	//for (int i = 0; i < WORD_COUNT; i++)
	//{
	//	g_words[i] = (char*)malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
	//	fgets(g_words[i], sizeof(char) * MAX_WORD_LENGTH, fp);
	//	g_words[i][strlen(g_words[i]) - 1] = '\0';
	//}

	////g_words[WORD_COUNT] = " ";

	//fclose(fp);
}