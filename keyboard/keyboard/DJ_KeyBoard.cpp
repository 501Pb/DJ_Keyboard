#include "DJ.h"
#include "word.h"
#define  ONE_SECOND 1000 //1초에 해당하는 1000ms = 1s  

/********************************전역변수*****************************************/
clock_t g_start_time;                           // 기준 시각(게임 시작)
clock_t g_end_time;								// 게임 종료 시간
double g_falling_speed = 2.0;                   // 단어 낙하 시각(초 단위)
//아직 사용못한 두개//

Word wd[WORD_NUM];
// : txt 파일에서 모든 Word를 추출해내 저장한 배열
vector<Word> word;
// : 생성된 단어들을 저장하는 vector
vector<string> v(MAP_Y, "│                                                                          │");
//출력할 단어들을 string으로 가지고 있는 vector 기본값으로 |    | 출력값을 가지고 있음.(맵 사이드)

int ph; //체력
char input_word[50]; // 사용자 입력 버퍼
int AllWord_size = 1024;
const char* AllWord[10]
= {
	"girugi",
	"tiger",
	"DJ_keyboard",
	"rabbit",
	"flower",
	"box",
	"attention",
	"","",""};

//파일에 있는 단어들이 저장될 배열

typedef struct { //단어 구조체
	int x; //단어의 x좌표
	char words[20]; //단어 저장 공간
} rain;

rain rains[21]; //20번째 rains는 판정선(0~19까지만 화면 출력 가능)
static pthread_t p_thread; // 스레드 이름
static int thr_id; // 스레드의 아이디
static int thr_exit = 1; // 스레드 종료 여부 상태

void* t_function(void* data); // 스레드화 할 사용자 입력 함수
void start_thread(); // 스레드 시작 함수
void end_thread(); // 스레드 중지 함수

/********************************초기화*****************************************/
void InitData(void)
{
	int position = 0;
	char* allWord = new char[1024];

	ifstream fin("g_words.txt"); //opening an input stream for file test.txt

	if (fin.is_open())
	{
		while (!fin.eof() && position < AllWord_size)
		{
			fin.get(allWord[position]);
			position++;
		}
		AllWord[position - 1] = '\0';
	}
	else
	{
		cout << "File could not be opened." << endl;
	}

	int i;
	for (i = 0; i < 21; i++)
	{
		rains[i].x = 0;
		strcpy(rains[i].words, " ");
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
	//매개변수로 콘솔 스크린 버퍼에 대한 핸들과 CONSOLE_CURSUR_INFO 구조체를 넘겨줌g
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

	system("cls"); //콘솔창 초기화

	printf("exit입력시 게임오버 \t\t [체력] %.1d \n", ph); //현재 체력과 총 시간 출력

	printf("────────────────────────────────────────────────────────────────────────────\n");//상단

	for (int i = 0; i < 20; i++)
	{
		printf("%*s%s\n", rains[i].x, "", rains[i].words); // x좌표에 맞추어 가변적으로 단어 출력

	}
	printf("────────────────────────────────────────────────────────────────────────────\n");//하단
	//cout << "____________________________________________________________________________" << endl;
	if (strcmp(rains[20].words, " ")) // 20번째 줄에 단어가 있는 경우
		ph -= 1; // 단어 입력 못할때마다 체력이 1씩 감소됨

	cout << ">>"; // 사용자의 입력부
}
//게임displays 계속해서 갱신되며, 단어들이 생성되고 지워진다

int game_over(void) {
	system("cls");
	//word.clear();//생성된 단어 clear
	fill(v.begin(), v.begin() + MAP_Y, "│                                                                          │");

	cout << "\n\n\n\n";
	cout << "\t┌─┐┌─┐┌┬┐┌─┐  ┌─┐┬  ┬┌─┐┬─┐" << endl;
	cout << "\t│ ┬├─┤│││├┤   │ │└┐┌┘├┤ ├┬┘" << endl;
	cout << "\t└─┘┴ ┴┴ ┴└─┘  └─┘ └┘ └─┘┴└─" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	string s;	cout << "\t>> ";	cin >> s;
	if (s == "y" || s == "Y") {
		system("cls");
		return 2;
	}
	else {
		system("cls");
		return 3;
	}
}

//게임오버화면

/********************************단어생성*******************************************/
void make_word(void) {

	for (int i = 20; i >= 0; i--) {
		strcpy(rains[i].words, rains[i - 1].words); // 기존 단어는 한 줄씩 밀고
		rains[i].x = rains[i - 1].x;
		rains[i - 1].x = 0;
		strcpy(rains[i - 1].words, " "); // 뒷 줄은 공백처리
	}
	rains[0].x = rand() % 53;
	srand(time(NULL));
	strcpy(rains[0].words, AllWord[rand() % 10]); // 새로운 단어를 무작위로 배치
}

void play_game(void) {

	ph = 3; //체력 3으로 초기화
	system("cls"); //콘솔창 초기화
	InitData(); //단어 배열 초기화
	g_start_time = clock();

	while (1) {
		start_thread();
		Sleep(SPEED); //지정한 시간만큼 단어 생성 지연

		make_word();//단어 생성해주고

		g_end_time = clock(); //해당 단어가 생성된 시간 기록

		if (ph <= 0) // 체력이 0 이면
			break; // 게임 종료됨
	}
	end_thread(); // 입력 스레드 중지
}

void* t_function(void* data) // 스레드 처리할 단어 입력 함수
{
	int word_len; //올바르게 입력된 단어 길이
	display(); //화면 출력

	while (!thr_exit) // 스레드가 중지될 때까지 입력을 계속 받음
	{
		gets_s(input_word);
		;
		for (int i = 20; i >= 0; i--)
		{
			if (strstr(rains[i].words, input_word)) {// 입력한 단어와 입력값이 같으면 
				word_len = strlen(input_word); //음악 프로세스 부분 함수에 넘길 단어 길이
				strcpy(rains[i].words, " "); // 해당 단어 제거
				break;
			}
		}
	}
	return 0;
}

void start_thread() // 스레드 시작 함수
{
	thr_exit = 0;
	thr_id = pthread_create(&p_thread, NULL, t_function, NULL); // 스레드 생성
}

void end_thread() // 스레드 중지 함수
{
	thr_exit = 1;
	pthread_cancel(p_thread); // 스레드 종료
}

void help_function() // 도움말 함수
{
	system("cls");
	cout << "단어를 입력하면 음이 재생되어 노래가 완성됩니다!" << endl;
	cout << "체력이 0이 되면 게임이 종료됩니다! " << endl;
	cout << "메뉴로 돌아가고 싶다면 아무 키나 눌러주세요!" << endl;
	_getch(); //아무키나 입력받음
}

int menu_function() { //메인메뉴 함수

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

	cin >> choice;

	switch (choice)
	{
	case 1:
		play_game(); // 게임 시작 함수 호출
		if (game_over() == 3) return 1; //만약 사용자가 continue?(Y/N) 질문에서 n을 입력한 경우 1을 반환하여 게임 종료시킴
		break;
	case 2:
		help_function(); // 도움말 출력 함수 호출
		break;
	case 3:
		system("cls"); // 콘솔창 초기화
		return 1; // 1을 반환하고 게임 종료
		break;
	default: // 그외 입력 무시
		break;
	}
	return 0;
}


