#include "DJ.h"
#include "word.h"
#include "music.h"
/********************************��������*****************************************/
Music music = Music();
clock_t g_start_time;                           // ���� �ð�(���� ����)
clock_t g_end_time;								// ���� ���� �ð�
double g_falling_speed = 2.0;                   // �ܾ� ���� �ð�(�� ����)

int ph; //ü�� ����
char input_word[1024]; // ����� �Է� �� ����
const char* EXIT = "exit"; // exit ���ڿ��� ���� (����ڰ� exit�� �Է����� �� ������ ����)
int word_len; //����ڰ� �Է��� �ܾ� �� ��Ȯ�ϰ� �Է��� �ܾ��� ���� ������ ����
bool playing;
const char* AllWord[10] //�꼺�� ���ӿ��� ��µ� �ܾ�
= {
	"DJ",
	"tiger",
	"keyboard",
	"rabbit",
	"flower",
	"box",
	"ball",
	"","","" };


typedef struct { //�ܾ� ����ü
	int x; //�ܾ��� x��ǥ
	char words[20]; //�ܾ� ���� ����
} rain_word;
rain_word rain_words[21]; //20��° rains�� ������(0~19������ ȭ�� ��� ����)

static pthread_t p_thread1; // ������ �̸�
static int thr_id1; // �������� ���̵�
static int thr_exit = 1; // ������ ���� ���� ����

/********************************�ʱ�ȭ*****************************************/
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
	//�õ�
	srand((unsigned int)time(NULL));
	//Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	//������ �ܼ� ��ũ�� ���ۿ� ���Ͽ� Ŀ���� ���� (�β� or ���⿩��) �� �����ϴ� ������ �� 
	//�Ű������� �ܼ� ��ũ�� ���ۿ� ���� �ڵ�� CONSOLE_CURSUR_INFO ����ü�� �Ѱ���
}
//���ӵ��� �ʱ⼳������ �������ش�.

/********************************ȭ��*******************************************/

void title(void) {

	//PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	textcolor(LIGHTBLUE,BLACK); //ȭ���� ��, ���ڴ� ���� ���
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
	*/textcolor(YELLOW, BLACK); //ȭ���� ��, ���ڴ� ���ο�� ���
	do { //Ű �Է¹����� ���� ȭ������ �Ѿ.
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		puts("");
		_getch(); //�Է��� ������ ������ �Է��ߴ��� �������� �ʴ� �Լ�
		Sleep(ONE_SECOND);
	} while (_kbhit()); //Ű���尡 �Էµ� �������� Ȯ���ϴ� �Լ�

	system("cls");
}
//Ÿ��Ʋȭ��

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
			
			GotoXY(rain_words[i - 3].x, i);       //������ ��ġ�� �ܾ� �̵� 
			cout << rain_words[i - 3].words;      // ���� ��ġ�� �ܾ� ���

			len = strlen(rain_words[i - 3].words); //����� �ܾ� ���̸� len������ ����
			
			if (i > 3) {
				GotoXY(rain_words[i - 3].x, i - 1); //���� ��ġ�� �ܾ�� �̵�
				
				for (int i = 0; i < len; i++) cout << " "; // ���� ��ġ�� �ܾ� ��� ����
			}
			GotoXY(pos, 25); //����� �Էºκ�
			printf("%s", input_word);

		Sleep(100);
		// 0.1�ʰ� �ð��� ����.
	}
	
	if ((strlen(rain_words[20].words) >1) && (strcmp(rain_words[20].words, " "))) // 20��° �ٿ� �ܾ �ִ� ���
		ph -= 1; // �ܾ� �Է� ���Ҷ����� ü���� 1�� ���ҵ�
}

bool game_over(void) {
	textcolor(RED, WHITE); //ȭ���� ȭ��Ʈ, ���ڴ� ����� ���
	system("cls");

	cout << "\n\n\n\n";
	cout << "\t������������������������  ��������  ��������������" << endl;
	cout << "\t�� ������������������     �� �������������� ������" << endl;
	cout << "\t�������� ���� ��������    ������ ���� ������������" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	/*y�� Y�� �Է��ϸ� �޴�ȭ������ �Ѿ�� n�̳� N�� �Է��ϸ� �����.
	 *�� ���� �ٸ� �Է��� ������ */

	GotoXY(5, 25); //����ڿ��� �Է¹��� ��ġ�� �̵�
	string s;
	cout << ">> ";

	while (1)
	{
		s = _getch(); //����ڿ��� y�� n�� �Է¹���
		
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

//���ӿ���ȭ��

/********************************�ܾ����*******************************************/
void random_word(void) { //�ܾ� ���� �Լ�

	for (int i = 20; i > 0; i--) {
		strcpy(rain_words[i].words, rain_words[i - 1].words); // ���� �ܾ�� �� �پ� �а�
		rain_words[i].x = rain_words[i - 1].x;
		rain_words[i - 1].x = 0;
		strcpy(rain_words[i - 1].words, " "); // �� ���� ����ó��
	}
	rain_words[0].x = rand() % 53;
	srand(time(NULL));
	strcpy(rain_words[0].words, AllWord[rand() % 10]); // ���ο� �ܾ �������� ��ġ
}

void play_game() { //���� ���� �Լ�

	textcolor(LIGHTBLUE, BLACK); //ȭ���� ȭ��Ʈ, ���ڴ� ���� ���
	ph = 3; //ü�� 3���� �ʱ�ȭ
	system("cls"); //�ܼ�â �ʱ�ȭ
	InitData(); //�ܾ� �迭 �ʱ�ȭ
	g_start_time = clock();
	start_thread(); //������ ����
	playing = true;
	while (1) {
		display(); //ȭ�� ���
		//�ܾ� ���
		random_word();//�ܾ� �������ְ�
		//Sleep(200); //������ �ð���ŭ �ܾ� ���� ����
		g_end_time = clock(); //�ش� �ܾ ������ �ð� ���

		if (!playing)	break; //exit �Է½� ����
		if (ph <= 0) break; // ü���� 0 �̸� ���� �����
	}

	end_thread(); //������ ����
}

void* t_function(void* data) // ������ ó���� �ܾ� �Է� �Լ�
{
	while (!thr_exit) // �����尡 ������ ������ �Է��� ��� ����
	{
		char c = 0;
		if (_kbhit())
		{
			c = _getch();
			int input_word_len = strlen(input_word);
			if (c == 13)
			{
				system("cls");
			} //�ܾ� �Է��ϰ� ����ġ�� ȭ�� �ʱ�ȭ������
			else if (c == 8)
			{
				input_word[input_word_len] = '\0';
			}
			else {
				input_word[input_word_len] = c;
				input_word[input_word_len + 1] = '\0';
			}
		}

		if (c == 13) {
			for (int i = 19; i >= 0; i--)
			{
				if (strstr(rain_words[i].words, input_word)) {// �Է��� �ܾ�� �Է°��� ���� ��� 
					strcpy(rain_words[i].words, ""); // �ش� �ܾ� ����
					word_len = strlen(input_word); //���� ���μ��� �κ� �Լ��� �ѱ� �ܾ� ���̸� ����
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

void start_thread() // ������ ���� �Լ�
{
	thr_exit = 0;
	thr_id1 = pthread_create(&p_thread1, NULL, t_function, NULL); // ������ ����
}

void end_thread() // ������ ���� �Լ�
{
	thr_exit = 1;
	pthread_cancel(p_thread1); // ������ ����
}

void help_function() // ���� �Լ�
{
	textcolor(CYAN, WHITE); //ȭ��� ���� ���� ����
	system("cls");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t ___   ___  _________   _          __________ " << endl;
	cout << "\t\t\t\t |  | |  |  | ______|  | |         |     __  | " << endl;
	cout << "\t\t\t\t |   -   |  | ______   | |_______  |     ____|" << endl;
	cout << "\t\t\t\t |__| |__|  |_______|  |_|______|  |____|" << endl;
	cout << "\n\n\n";
	textcolor(BROWN, WHITE); //ȭ��� ���� ���� ���� 
	cout << "\t\t\t\t �ϴÿ��� ��ó�� �������� �ܾ Ű����� �Է����ּ���!" << endl << endl;
	cout << "\t\t\t\t �ܾ �Է��ϸ� �ܾ��� ���̸�ŭ ���� ����˴ϴ�!" << endl << endl;
	cout << "\t\t\t\t ü���� 0�� �Ǹ� ������ ����˴ϴ�! " << endl << endl;
	cout << "\t\t\t\t ������ ����Ǹ� ������ ������ �ϼ��˴ϴ�! " << endl << endl<<endl;
	textcolor(MAGENTA, WHITE); //ȭ��� ���� ���� ����
	cout << "\t\t\t\t�޴��� ���ư��� �ʹٸ� �ƹ� Ű�� �����ּ���!" << endl << endl;
	_getch(); //�ƹ�Ű�� �Է¹���
	fflush(stdin);
}

bool menu_function() { //���θ޴� �Լ�
	textcolor(BROWN, WHITE); //ȭ��� ���� ���� ����

	int choice = 0; //����ڰ� �޴����� ������ ���� �����ϴ� ����

	system("cls"); // �ܼ�â �ʱ�ȭ
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
	textcolor(BLUE, WHITE); //ȭ��� ���� ���� ����
	cout << "\t\t\t\t\t\t 1. GAME START " << endl << endl << endl;
	textcolor(GREEN, WHITE); //ȭ��� ���� ���� ����
	cout << "\t\t\t\t\t\t 2. HELP " << endl << endl << endl;
	textcolor(RED, WHITE); //ȭ��� ���� ���� ����
	cout << "\t\t\t\t\t\t 3. GAME END " << endl << endl << endl << endl << endl;
	textcolor(BROWN, WHITE); //ȭ��� ���� ���� ����
	cout << "\t\t\t\t\t\t MENU NUMBER >> ";
	fflush(stdin);
	// �޴� ������ ��ȣ 1,2,3 �� �ϳ��� �Է¹��� (������ �Է��� ������)
	while (1)
	{
		choice = _getch();

		if (choice == 49) { //����ڰ� 1�� �Է��� ���
			cout << "1";
			system("cls");
			break;
		}
		else if (choice == 50) { //����ڰ� 2�� �Է��� ���
			cout << "2";
			system("cls");
			break;
		}
		else if (choice == 51) { //����ڰ� 3�� �Է��� ���
			cout << "3";
			system("cls");
			break;
		}
	}

	switch (choice)
	{
	case 49: //����ڰ� 1�� �Է��� ���
		play_game(); // ���� ���� �Լ� ȣ��
		if (!game_over()) return false;   //���� ����ڰ� continue?(Y/N) �������� n�� �Է��� ��� false�� ��ȯ�Ͽ� ���� �����Ŵ
		break;
	case 50: //����ڰ� 2�� �Է��� ���
		help_function(); // ���� ��� �Լ� ȣ��
		break;
	case 51: //����ڰ� 3�� �Է��� ���
		system("cls"); // �ܼ�â �ʱ�ȭ
		return false; // 1�� ��ȯ�ϰ� ���� ����
		break;
	default: // �׿� �Է� ����
		break;
	}
	return true;
}

void GotoXY(int x, int y)		// Ŀ�� ��ġ �̵��ϴ� �Լ�
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background)  //���� ���� ��� �Լ�
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}