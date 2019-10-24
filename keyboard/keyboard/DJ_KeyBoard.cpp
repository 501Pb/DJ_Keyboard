/*
	DJ_Keyboard
	���� : ���� ���� ����ü
	���� : ���� ���� ���
	���� : ���� Ʋ ����
	��ȣ : ���� ����
*/
#include "DJ.h"
#include "word.h"

#define KEY_ENTER '\n'
#define KEY_BS '\b'

#define MAX_WORD_LENGTH 24
#define MAX_SCREEN_WORD_COUNT 19
#define WORD_COUNT 11       

int SPEED = 0;
int g_word_count = 11;
char** g_words;
int g_fail_count = 0;                           // ������ ����
int g_score = 0;                                // ����
char g_input_word[MAX_WORD_LENGTH + 1];         // �Է� �ܾ� ����
int g_input_word_length = 0;                    // �Է� �ܾ� ����
int stage = 1;

//�ұ��
void new_block(void);							//���ο� ����� �ϳ� ���� 
void check_key(void);							//Ű����� Ű�� �Է¹��� 
void drop_block(void);							//����� �Ʒ��� ����Ʈ�� 
void DrawWord(int i);                           // ȭ�鿡 ��Ÿ�� i��° �ܾ� ���
void EraseWord(int i);                          // ȭ�鿡 ��Ÿ�� i��° �ܾ� �����

Word g_screen_word[100];// ȭ�鿡 ��Ÿ�� �ܾ��(g_words�� ���� index ����)
int g_screen_word_count = 0;                    // ȭ�鿡 ��Ÿ�� �ܾ� ����
clock_t g_start_time;                           // ���� �ð�
double g_falling_speed = 2.0;                   // �ܾ� ���� �ð�(�� ����)

void create_word(void) {
	//���Ͽ��� �ܾ� �̸��� ���踦 �����ؿ´�??
	//���ĺ��� �´� ��ε�?
}


//�ұ��
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 


//////////////////////////////////////////////////////////////////////////////////////////

void game_init(void) {
	g_start_time = clock();
	//�õ�
	srand((unsigned int)time(NULL));
	//Ŀ�� �����
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
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	for (int i = 0; i < 19; i++)
		printf("��                                                                          ��\n");
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");
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
	cout << "\t������������������������  ��������  ��������������" << endl;
	cout << "\t�� ������������������   �� �������������� ������" << endl;
	cout << "\t�������� ���� ��������  ������ ���� ������������" << endl;
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

void InitData(void)
{
	int i;
	FILE* fp;
	fp = fopen("g_words.txt", "rt");

	g_words = (char**)malloc(sizeof(char*) * (WORD_COUNT + 1));

	for (i = 0; i < WORD_COUNT; i++)
	{
		g_words[i] = (char*)malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
		fgets(g_words[i], sizeof(char) * MAX_WORD_LENGTH, fp);
		g_words[i][strlen(g_words[i]) - 1] = '\0';
	}

	//g_words[WORD_COUNT] = " ";

	fclose(fp);
}