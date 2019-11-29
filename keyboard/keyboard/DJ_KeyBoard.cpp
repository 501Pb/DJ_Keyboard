#include "DJ.h"
#include "word.h"
#include "music.h"
/********************************?�역변??****************************************/
Music music = Music();
clock_t g_start_time;                           // 기�? ?�각(게임 ?�작)
clock_t g_end_time;								// 게임 종료 ?�간
double g_falling_speed = 2.0;                   // ?�어 ?�하 ?�각(�??�위)

int ph; //체력 ?�??
char input_word[1024]; // ?�용???�력 �??�??
const char* EXIT = "exit"; // exit 문자?�을 ?�??(?�용?��? exit�??�력?�을 ??게임???�남)
int word_len; //?�용?��? ?�력???�어 �??�확?�게 ?�력???�어??길이 ?�?�할 변??
bool playing;
const char* AllWord[10] //?�성�?게임?�서 출력???�어
= {
	"DJ",
	"tiger",
	"key",
	"rabbit",
	"flower",
	"box",
	"ball",
	"board","","" };


typedef struct { //?�어 구조�?
	int x; //?�어??x좌표
	char words[20]; //?�어 ?�??공간
} rain_word;
rain_word rain_words[21]; //20번째 rains???�정??0~19까�?�??�면 출력 가??

static pthread_t p_thread1; // ?�레???�름
static int thr_id1; // ?�레?�의 ?�이??
static int thr_exit = 1; // ?�레??종료 ?��? ?�태

/********************************초기??****************************************/
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
	//?�드
	//srand((unsigned int)time(NULL));
	//커서 ?�기�?
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	//지?�된 콘솔 ?�크�?버퍼???�?�여 커서???�태 (?�께 or ?�출?��?) �??�정?�는 ??��????
	//매개변?�로 콘솔 ?�크�?버퍼???�???�들�?CONSOLE_CURSUR_INFO 구조체�? ?�겨�?
}
//게임?�의 초기?�정?�을 지?�해준??

/********************************?�면*******************************************/

void title(void) {

	//PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	textcolor(LIGHTBLUE,BLACK); //?�면?� 블랙, 글?�는 블루�?출력
	/*
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
	*/textcolor(YELLOW, BLACK); //?�면?� 블랙, 글?�는 ?�로?�로 출력
	do { //???�력받으�??�음 ?�면?�로 ?�어�?
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		puts("");
		_getch(); //?�력?� 받�?�?무엇???�력?�는지 보여주�? ?�는 ?�수
		Sleep(ONE_SECOND);
	} while (_kbhit()); //?�보?��? ?�력???�태?��? ?�인?�는 ?�수

	system("cls");
}
//?�?��??�면

void display(void) {

	int len; // ����ϴ� �ܾ� ����

	GotoXY(0, 0);
	printf("\t exit �Է½� ���ӿ��� \t\t\t [ü��] %.1d \n", ph); //���� ü�� ���
	GotoXY(1, 1);
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//���
	GotoXY(1, 23);
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//�ϴ�
	GotoXY(5, 25); //����� �Էºκ�
	cout << ">>                                                                             ";                                             

	int pos = 7;
	for (int i = 3; i <= 23; i++) {
			
			GotoXY(rain_words[i - 3].x, i);       //무작???�치�??�어 ?�동 
			cout << rain_words[i - 3].words;      // ?�재 ?�치???�어 출력

			len = strlen(rain_words[i - 3].words); //출력???�어 길이�?len변?�에 ?�??
			
			if (i > 3) {

				
				GotoXY(rain_words[i - 3].x, i - 1); //���� ��ġ�� �ܾ�� �̵�

				for (int i = 0; i < len; i++) cout << " "; // ?�전 ?�치???�어 출력 지?�
			}

			
			GotoXY(pos, 25); //����� �Էºκ�

			printf("%s", input_word);

		Sleep(60000 / (130 * 16));
		// ?�어가 ?�어지???�도 조절
	}
	
	if ((strlen(rain_words[20].words) >1) && (strcmp(rain_words[20].words, " "))) // 20번째 줄에 ?�어가 ?�는 경우
		ph -= 1; // ?�어 ?�력 못할?�마??체력??1??감소??
}

bool game_over(void) {
	textcolor(RED, WHITE); //?�면?� ?�이?? 글?�는 ?�드�?출력
	system("cls");
	music.note_clear();
	cout << "\n\n\n\n";
	cout << "\t������������������������  ��������  ��������������" << endl;
	cout << "\t�� ������������������     �� �������������� ������" << endl;
	cout << "\t�������� ���� ��������    ������ ���� ������������" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ../saveMusic/music.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	/*y??Y�??�력?�면 메뉴?�면?�로 ?�어가�?n?�나 N???�력?�면 종료??
	 *�??�의 ?�른 ?�력?� 무시??*/

	GotoXY(5, 25); //?�용?�에�??�력받을 ?�치�??�동
	string s;
	cout << ">> ";

	while (1)
	{
		s = _getch(); //?�용?�에�?y??n???�력받음
		
		if (s == "y" | s == "Y") {
			return true;
			break;
		}
		else if (s == "n" | s == "N") {
			return false;
			break;
		}
	}
}

//게임?�버?�면

/********************************?�어?�성*******************************************/
void random_word(void) { //?�어 ?�성 ?�수

	for (int i = 20; i > 0; i--) {
		
		strcpy(rain_words[i].words, rain_words[i - 1].words); // ���� �ܾ ���� �迭�� �ѱ�
		rain_words[i].x = rain_words[i - 1].x; //���� �ܾ��� x��ǥ�� ���� �迭 ��ġ�� �ѱ�
		rain_words[i - 1].x = 0; 
		strcpy(rain_words[i - 1].words, " "); // �� ���� ����ó��


	}

	rain_words[0].x = rand() % 12 * 6; //���� ���� 6�� ��� ���� ����)
	srand(time(NULL));
	if (rain_words[0].x == rain_words[1].x) rain_words[0].x = rand() % 12 * 6; //�ܾ��� x��ǥ�� ������ ���� �ٽ� ����
	strcpy(rain_words[0].words, AllWord[rand() % 10]); // ���ο� �ܾ �������� ��ġ

}

void play_game() { //게임 진행 ?�수

	textcolor(LIGHTBLUE, BLACK); //?�면?� ?�이?? 글?�는 블루�?출력
	ph = 3; //체력 3?�로 초기??
	system("cls"); //콘솔�?초기??
	InitData(); //?�어 배열 초기??
	g_start_time = clock();
	start_thread(); //?�레???�작
	playing = true;
	while (1) {

		display(); //ȭ�� ���
		//�ܾ� ���
		random_word();//�ܾ� �������ְ�
		g_end_time = clock(); //�ش� �ܾ ������ �ð� ���

		if (!playing)	break; //exit �Է½� ����
		if (ph <= 0) break; // ü���� 0 �̸� ���� �����

	}

	end_thread(); //?�레??중�?
}

void* t_function(void* data) // ?�레??처리???�어 ?�력 ?�수
{
	while (!thr_exit) // ?�레?��? 중�????�까지 ?�력??계속 받음
	{
		char c = 0;
		if (_kbhit())
		{
			c = _getch();
			int input_word_len = strlen(input_word);
			if (c == 13)
			{
				system("cls");
			} //?�어 ?�력?�고 ?�터치면 ?�면 초기?�시켜줌
			else if (c == 8)
			{
				input_word[input_word_len - 1] = '\0';
			}
			else {
				input_word[input_word_len] = c;
				input_word[input_word_len + 1] = '\0';
			}
		}

		if (c == 13) {
			for (int i = 19; i >= 0; i--)
			{
				if (strstr(rain_words[i].words, input_word)) {// ?�력???�어?� ?�력값이 같�? 경우 
					strcpy(rain_words[i].words, ""); // ?�당 ?�어 ?�거
					word_len = strlen(input_word); //?�악 ?�로?�스 부�??�수???�길 ?�어 길이�?구함
					music.note_adder(word_len);
					break;
				}
			}
			if (strcmp(input_word, EXIT) == 0)
				playing = false;
			input_word[0] = '\0';
		}
	
	}
	return 0;
}

void start_thread() // ?�레???�작 ?�수
{
	thr_exit = 0;
	thr_id1 = pthread_create(&p_thread1, NULL, t_function, NULL); // ?�레???�성
}

void end_thread() // ?�레??중�? ?�수
{
	thr_exit = 1;
	pthread_cancel(p_thread1); // ?�레??종료
}

void help_function() // ?��?�??�수
{
	textcolor(CYAN, WHITE); //?�면�?글???�상 변�?
	system("cls");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t ___   ___  _________   _          __________ " << endl;
	cout << "\t\t\t\t |  | |  |  | ______|  | |         |     __  | " << endl;
	cout << "\t\t\t\t |   -   |  | ______   | |_______  |     ____|" << endl;
	cout << "\t\t\t\t |__| |__|  |_______|  |_|______|  |____|" << endl;
	cout << "\n\n\n";
	textcolor(BROWN, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t ?�늘?�서 비처???�려?�는 ?�어�??�보?�로 ?�력?�주?�요!" << endl << endl;
	cout << "\t\t\t\t ?�어�??�력?�면 ?�어??길이만큼 ?�이 ?�생?�니??" << endl << endl;
	cout << "\t\t\t\t 체력??0???�면 게임??종료?�니?? " << endl << endl;
	cout << "\t\t\t\t 게임??종료?�면 ?�만???�악???�성?�니?? " << endl << endl<<endl;
	textcolor(MAGENTA, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t메뉴�??�아가�??�다�??�무 ?�나 ?�러주세??" << endl << endl;
	_getch(); //?�무?�나 ?�력받음
	fflush(stdin);
}

bool menu_function() { //메인메뉴 ?�수
	textcolor(BROWN, WHITE); //?�면�?글???�상 변�?

	int choice = 0; //?�용?��? 메뉴?�서 ?�택??값을 ?�?�하??변??

	system("cls"); // 콘솔�?초기??
	cout << "\n\n\n\n";
	cout << "\t ______       ___          ___   _  _______  __   __  _______  _______  _______  ______    ______  \t" << endl;
	cout << "\t |      |     |   |        |   | | ||       ||  | |  ||  _    ||       ||   _   ||    _ |  |      | \t" << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |\t" << endl;
	cout << "\t |  _    |    |   |        |   |_| ||    ___||  |_|  || |_|   ||   _   ||  |_|  ||   | ||  |  _    |\t" << endl;
	cout << "\t | | |   |    |   |        |      _||   |___ |       ||       ||  | |  ||       ||   |_||_ | | |   |\t" << endl;
	cout << "\t | |_|   | ___|   |        |     |_ |    ___||_     _||  _   | |  |_|  ||       ||    __  || |_|   |\t" << endl;
	cout << "\t |       ||       | _____  |    _  ||   |___   |   |  | |_|   ||       ||   _   ||   |  | ||       |\t" << endl;
	cout << "\t |______| |_______||_____| |___| |_||_______|  |___|  |_______||_______||__| |__||___|  |_||______| \t" << endl;
	cout << "\n\n" << endl;
	//MENU
	textcolor(BLUE, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t\t\t 1. GAME START " << endl << endl << endl;
	textcolor(GREEN, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t\t\t 2. HELP " << endl << endl << endl;
	textcolor(RED, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t\t\t 3. GAME END " << endl << endl << endl << endl << endl;
	textcolor(BROWN, WHITE); //?�면�?글???�상 변�?
	cout << "\t\t\t\t\t\t MENU NUMBER >> ";
	fflush(stdin);
	// 메뉴 ?�택??번호 1,2,3 �??�나�??�력받음 (?�머지 ?�력?� 무시??
	while (1)
	{
		choice = _getch();

		if (choice == 49) { //?�용?��? 1???�력??경우
			cout << "1";
			system("cls");
			break;
		}
		else if (choice == 50) { //?�용?��? 2�??�력??경우
			cout << "2";
			system("cls");
			break;
		}
		else if (choice == 51) { //?�용?��? 3???�력??경우
			cout << "3";
			system("cls");
			break;
		}
	}

	switch (choice)
	{
	case 49: //?�용?��? 1???�력??경우
		play_game(); // 게임 ?�작 ?�수 ?�출
		if (!game_over()) return false;   //만약 ?�용?��? continue?(Y/N) 질문?�서 n???�력??경우 false??반환?�여 게임 종료?�킴
		break;
	case 50: //?�용?��? 2�??�력??경우
		help_function(); // ?��?�?출력 ?�수 ?�출
		break;
	case 51: //?�용?��? 3???�력??경우
		system("cls"); // 콘솔�?초기??
		return false; // 1??반환?�고 게임 종료
		break;
	default: // 그외 ?�력 무시
		break;
	}
	return true;
}

void GotoXY(int x, int y)		// 커서 ?�치 ?�동?�는 ?�수
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background)  //글???�상 출력 ?�수
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
