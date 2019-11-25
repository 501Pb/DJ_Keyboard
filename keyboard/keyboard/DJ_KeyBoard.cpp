#include "DJ.h"
#include "word.h"
/********************************전역변수*****************************************/
clock_t g_start_time;                           // 기준 시각(게임 시작)
clock_t g_end_time;								// 게임 종료 시간
double g_falling_speed = 2.0;                   // 단어 낙하 시각(초 단위)

Word wd[WORD_NUM];
// : txt 파일에서 모든 Word를 추출해내 저장한 배열
vector<Word> word;
// : 생성된 단어들을 저장하는 vector
vector<string> v(MAP_Y, "│                                                                          │");
//출력할 단어들을 string으로 가지고 있는 vector 기본값으로 |    | 출력값을 가지고 있음.(맵 사이드)

int ph; //체력 저장
char input_word[1024]; // 사용자 입력 값 저장
const char* EXIT = "exit"; // exit 문자열을 저장 (사용자가 exit를 입력했을 때 게임이 끝남)
int word_len; //사용자가 입력한 단어 중 정확하게 입력한 단어의 길이 저장할 변수

const char* AllWord[10] //산성비 게임에서 출력될 단어
= {
	"girugi",
	"tiger",
	"DJ_keyboard",
	"rabbit",
	"flower",
	"box",
	"ball",
	"","","" };


typedef struct { //단어 구조체
	int x; //단어의 x좌표
	char words[20]; //단어 저장 공간
} rain_word;
rain_word rain_words[21]; //20번째 rains는 판정선(0~19까지만 화면 출력 가능)

static pthread_t p_thread1; // 스레드 이름
static int thr_id1; // 스레드의 아이디
static pthread_t p_thread2; // 스레드 이름
static int thr_id2; // 스레드의 아이디
static int thr_exit = 1; // 스레드 종료 여부 상태

/********************************초기화*****************************************/
void InitData(void)
{
	int i;
	for (i = 0; i < 21; i++)
	{
		rain_words[i].x = 0;
		strcpy(rain_words[i].words, " ");
	}
}

void game_init(void) {
	//g_start_time = clock(); 
	//시드
	srand((unsigned int)time(NULL));
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	//지정된 콘솔 스크린 버퍼에 대하여 커서의 형태 (두께 or 노출여부) 를 설정하는 역할을 함 
	//매개변수로 콘솔 스크린 버퍼에 대한 핸들과 CONSOLE_CURSUR_INFO 구조체를 넘겨줌
}
//게임들의 초기설정들을 지정해준다.



/********************************화면*******************************************/

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

	do { //키 입력받으면 다음 화면으로 넘어감.
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		puts("");
		_getch(); //입력은 받지만 무엇을 입력했는지 보여주지 않는 함수
		Sleep(ONE_SECOND);
	} while (_kbhit()); //키보드가 입력된 상태인지 확인하는 함수

	system("cls");
}
//타이틀화면

void display(void) {

	int len; // 출력하는 단어 길이
	
	GotoXY(0, 0);
	printf("exit입력시 게임오버 \t\t [체력] %.1d \n", ph); //현재 체력 출력
	GotoXY(1, 1);
	printf("────────────────────────────────────────────────────────────────────────────\n");//상단
	GotoXY(1, 23);
	printf("────────────────────────────────────────────────────────────────────────────\n");//하단
	GotoXY(1, 25);
	cout << ">>";

	for (int i = 3; i <= 23; i++) {

		GotoXY(rain_words[i-3].x, i); cout << rain_words[i-3].words;      // 현재 위치에 단어 출력

		len = strlen(rain_words[i - 3].words); //출력한 단어 길이 구함
		
		if (i > 3) {
			GotoXY(rain_words[i - 3].x, i - 1);
			for (int i = 0; i < len; i++) cout << " "; // 이전 위치의 단어 출력을 지움
		
		}
		Sleep(100);                                // 0.1초간 시간을 끈다.

	}
	
	if ((strlen(rain_words[20].words) >1) && (strcmp(rain_words[20].words, " "))) // 20번째 줄에 단어가 있는 경우
		ph -= 1; // 단어 입력 못할때마다 체력이 1씩 감소됨
}

bool game_over(void) {

	system("cls");

	cout << "\n\n\n\n";
	cout << "\t┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬┌─┐┬─┐" << endl;
	cout << "\t│ ┬├─┤│││├┤   │ │└┐┌┘├┤ ├┬┘" << endl;
	cout << "\t└─┘┴ ┴┴ ┴└─┘  └─┘ └┘ └─┘┴└─" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	/*y나 Y를 입력하면 메뉴화면으로 넘어가고 n이나 N을 입력하면 종료됨.
	 *그 외의 다른 입력은 무시함 */

	GotoXY(5, 25); //사용자에게 입력받을 위치로 이동
	string s;
	cout << ">> ";
//	fflush(stdin);
//	cin.ignore(1000);
	//while (getchar() != '\n');


	while (1)
	{
		s = _getch();

		if (s == "y" | s == "Y") {
			cout << s;
			system("cls");
			return true;
			break;
		}
		else if (s == "n" | s == "N") {
			cout << s;
			system("cls");
			return false;
			break;
		}
	}

}

//게임오버화면

/********************************단어생성*******************************************/
void random_word(void) {

	for (int i = 20; i > 0; i--) {
		strcpy(rain_words[i].words, rain_words[i - 1].words); // 기존 단어는 한 줄씩 밀고
		rain_words[i].x = rain_words[i - 1].x;
		rain_words[i - 1].x = 0;
		strcpy(rain_words[i - 1].words, " "); // 뒷 줄은 공백처리
	}
	rain_words[0].x = rand() % 53;
	srand(time(NULL));
	strcpy(rain_words[0].words, AllWord[rand() % 10]); // 새로운 단어를 무작위로 배치
}

void play_game(void) {

	ph = 3; //체력 3으로 초기화
	system("cls"); //콘솔창 초기화
	InitData(); //단어 배열 초기화
	g_start_time = clock();
	start_thread1(); //입력 스레드 시작

	while (1) {
		display(); //화면 출력
		//단어 출력
		random_word();//단어 생성해주고
		//Sleep(100); //지정한 시간만큼 단어 생성 지연
		g_end_time = clock(); //해당 단어가 생성된 시간 기록

		if (strcmp(input_word, EXIT) == 0)	break; //exit 입력시 종료
		if (ph <= 0) break; // 체력이 0 이면 게임 종료됨

	}
	end_thread1(); // 입력 스레드 중지
}

void* t_function1(void* data) // 스레드 처리할 단어 입력 함수
{
	while (!thr_exit) // 스레드가 중지될 때까지 입력을 계속 받음
	{
		if (gets_s(input_word)) system("cls");
		//gets_s(input_word);
		
		for (int i = 19; i >= 0; i--)
		{
			if (strstr(rain_words[i].words, input_word)) {// 입력한 단어와 입력값이 같은 경우 
				strcpy(rain_words[i].words, ""); // 해당 단어 제거
				word_len = strlen(input_word); //음악 프로세스 부분 함수에 넘길 단어 길이를 구함
				break;
			}
		}
	}
	return 0;
}

void start_thread1() // 스레드 시작 함수
{
	thr_exit = 0;
	thr_id1 = pthread_create(&p_thread1, NULL, t_function1, NULL); // 스레드 생성
}

void end_thread1() // 스레드 중지 함수
{
	thr_exit = 1;
	pthread_cancel(p_thread1); // 스레드 종료
}

void* t_function2(void* data) // 스레드 단어 출력 함수
{
	while (!thr_exit) // 스레드가 중지될 때까지 입력을 계속 받음
	{
		for (int i = 2; i <= 22; i++) {

			GotoXY(rain_words[i - 2].x, i); cout << rain_words[i - 2].words;      // 현재 위치에 단어 출력

			GotoXY(rain_words[i - 2].x, i - 1); cout << "   "; // 이전 위치의 단어 지움

			Sleep(100);
		}
	}
	return 0;
}

void start_thread2() // 스레드 시작 함수
{
	thr_exit = 0;
	thr_id2 = pthread_create(&p_thread2, NULL, t_function2, NULL); // 스레드 생성
}

void end_thread2() // 스레드 중지 함수
{
	thr_exit = 1;
	pthread_cancel(p_thread2); // 스레드 종료
}

void help_function() // 도움말 함수
{
	system("cls");
	cout << "단어를 입력하면 음이 재생되어 노래가 완성됩니다!" << endl;
	cout << "체력이 0이 되면 게임이 종료됩니다! " << endl;
	cout << "메뉴로 돌아가고 싶다면 아무 키나 눌러주세요!" << endl;
	_getch(); //아무키나 입력받음

}

bool menu_function() { //메인메뉴 함수

	int choice = 0; //사용자가 메뉴에서 선택한 값을 저장하는 변수

	system("cls"); // 콘솔창 초기화

	//MENU
	cout << "\n\n\n\n";
	cout << "\t\t\t\t ___   ___  _________   _      _   ___   ___ " << endl;
	cout << "\t\t\t\t |  | |  |  | ______|  | |*   | |  |  |  |  | " << endl;
	cout << "\t\t\t\t |   v   |  | ______   | | *  | |  |  |__|  |" << endl;
	cout << "\t\t\t\t |__| |__|  |_______|  |_|  * |_|  |________|" << endl;
	cout << "\n\n\n";

	cout << "\t\t\t\t\t\t 1. GAME START " << endl << endl << endl;
	cout << "\t\t\t\t\t\t 2. HELP " << endl << endl << endl;
	cout << "\t\t\t\t\t\t 3. GAME END " << endl << endl << endl << endl << endl;

	cout << "\t\t\t\t\t\t MENU NUMBER >> ";

	fflush(stdin);
	// 메뉴 선택할 번호 1,2,3 중 하나를 입력받음 (나머지 입력은 무시함)
	while (1)
	{
		choice = _getch();

		if (choice == 49) { //사용자가 1을 입력한 경우
			cout << "1";
			system("cls");
			break;
		}
		else if (choice == 50) { //사용자가 2를 입력한 경우
			cout << "2";
			system("cls");
			break;
		}
		else if (choice == 51) { //사용자가 3을 입력한 경우
			cout << "3";
			system("cls");
			break;
		}
	}

	switch (choice)
	{
	case 49: //사용자가 1을 입력한 경우
		play_game(); // 게임 시작 함수 호출
		if (!game_over()) return false;   //만약 사용자가 continue?(Y/N) 질문에서 n을 입력한 경우 false을 반환하여 게임 종료시킴
		break;
	case 50: //사용자가 2를 입력한 경우
		help_function(); // 도움말 출력 함수 호출
		break;
	case 51: //사용자가 3을 입력한 경우
		system("cls"); // 콘솔창 초기화
		return false; // 1을 반환하고 게임 종료
		break;
	default: // 그외 입력 무시
		break;
	}
	return true;
}

void GotoXY(int x, int y)		// 커서 위치 이동
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}