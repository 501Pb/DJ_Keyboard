#include "DJ.h"
#include "word.h"
#define  ONE_SECOND 1000 //1�ʿ� �ش��ϴ� 1000ms = 1s  

/********************************��������*****************************************/
clock_t g_start_time;                           // ���� �ð�(���� ����)
clock_t g_end_time;								// ���� ���� �ð�
double g_falling_speed = 2.0;                   // �ܾ� ���� �ð�(�� ����)

Word wd[WORD_NUM];
// : txt ���Ͽ��� ��� Word�� �����س� ������ �迭
vector<Word> word;
// : ������ �ܾ���� �����ϴ� vector
vector<string> v(MAP_Y, "��                                                                          ��");
//����� �ܾ���� string���� ������ �ִ� vector �⺻������ |    | ��°��� ������ ����.(�� ���̵�)

int ph; //ü�� ����
char input_word[50]; // ����� �Է� �� ����
const char* EXIT = "exit"; // exit ���ڿ��� ���� (����ڰ� exit�� �Է����� �� ������ ����)

const char* AllWord[10] //�꼺�� ���ӿ��� ��µ� �ܾ�
= {
	"girugi",
	"tiger",
	"DJ_keyboard",
	"rabbit",
	"flower",
	"box",
	"attention",
	"","",""};


typedef struct { //�ܾ� ����ü
	int x; //�ܾ��� x��ǥ
	char words[20]; //�ܾ� ���� ����
} rain_word;
rain_word rain_words[21]; //20��° rains�� ������(0~19������ ȭ�� ��� ����)

static pthread_t p_thread; // ������ �̸�
static int thr_id; // �������� ���̵�
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
	/*
	���Ͽ�� �迭�� ����
	int position = 0;
	char* allWord = new char[1024];

	ifstream fin("g_words.txt"); //opening an input stream for file test.txt

	if (fin.is_open())
	{
		while (!fin.eof() && position < 1024)
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
	*/
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

	system("cls"); //�ܼ�â �ʱ�ȭ

	printf("exit�Է½� ���ӿ��� \t\t [ü��] %.1d \n", ph); //���� ü�� ���

	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//���

	for (int i = 0; i < 20; i++)
	{
		printf("%*s%s\n", rain_words[i].x, "", rain_words[i].words); // x��ǥ�� ���缭 ���� �ܾ� ���

	}
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//�ϴ�
	//cout << "____________________________________________________________________________" << endl;
	if (strcmp(rain_words[20].words, " ")) // 20��° �ٿ� �ܾ �ִ� ���
		ph -= 1; // �ܾ� �Է� ���Ҷ����� ü���� 1�� ���ҵ�

	GotoXY(1, 23); //����ڿ��� �Է¹��� ��ġ�� �̵�
	cout << ">>";
}

bool game_over(void) {
	system("cls");

	cout << "\n\n\n\n";
	cout << "\t������������������������  ��������  ��������������" << endl;
	cout << "\t�� ������������������   �� �������������� ������" << endl;
	cout << "\t�������� ���� ��������  ������ ���� ������������" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;
	
	/*y�� Y�� �Է��ϸ� �޴�ȭ������ �Ѿ�� n�̳� N�� �Է��ϸ� �����.
	 *�� ���� �ٸ� �Է��� ������ */

	GotoXY(5, 25); //����ڿ��� �Է¹��� ��ġ�� �̵�
	string s;
	fflush(stdin);
	cout << ">> ";

	while (1) 
	{
		s = _getch();
		cout << s;
		if (s == "y" | s == "Y") {
			system("cls");
			return true; 
			break;
		}
		else if (s == "n" | s == "N") {
			system("cls");
			return false;
			break;
		}
	}

}

//���ӿ���ȭ��

/********************************�ܾ����*******************************************/
void random_word(void) {

	for (int i = 20; i >= 0; i--) {
		strcpy(rain_words[i].words, rain_words[i - 1].words); // ���� �ܾ�� �� �پ� �а�
		rain_words[i].x = rain_words[i - 1].x;
		rain_words[i - 1].x = 0;
		strcpy(rain_words[i - 1].words, " "); // �� ���� ����ó��
	}
	rain_words[0].x = rand() % 53;
	srand(time(NULL));
	strcpy(rain_words[0].words, AllWord[rand() % 10]); // ���ο� �ܾ �������� ��ġ
}

void play_game(void) {

	ph = 3; //ü�� 3���� �ʱ�ȭ
	system("cls"); //�ܼ�â �ʱ�ȭ
	InitData(); //�ܾ� �迭 �ʱ�ȭ
	g_start_time = clock();
	start_thread(); //�Է� ������ ����

	while (1) {

		Sleep(SPEED); //������ �ð���ŭ �ܾ� ���� ����
		display(); //ȭ�� ���
		random_word();//�ܾ� �������ְ�
		g_end_time = clock(); //�ش� �ܾ ������ �ð� ���

		if (strcmp(input_word, EXIT) == 0)	break; //exit �Է½� ����
		if (ph <= 0) break; // ü���� 0 �̸� ���� �����

	}
	end_thread(); // �Է� ������ ����
}

void* t_function(void* data) // ������ ó���� �ܾ� �Է� �Լ�
{
	int word_len; //����ڰ� �Է��� �ܾ� �� ��Ȯ�ϰ� �Է��� �ܾ��� ���� ������ ����
	
	while (!thr_exit) // �����尡 ������ ������ �Է��� ��� ����
	{
		gets_s(input_word);

		for (int i = 20; i >= 0; i--)
		{
			if (strstr(rain_words[i].words, input_word)) {// �Է��� �ܾ�� �Է°��� ���� ��� 
				word_len = strlen(input_word); //���� ���μ��� �κ� �Լ��� �ѱ� �ܾ� ���̸� ����
				strcpy(rain_words[i].words, " "); // �ش� �ܾ� ����
				break;
			}
		}
	}
	return 0;
}

void start_thread() // ������ ���� �Լ�
{
	thr_exit = 0;
	thr_id = pthread_create(&p_thread, NULL, t_function, NULL); // ������ ����
}

void end_thread() // ������ ���� �Լ�
{
	thr_exit = 1;
	pthread_cancel(p_thread); // ������ ����
}

void help_function() // ���� �Լ�
{
	system("cls");
	cout << "�ܾ �Է��ϸ� ���� ����Ǿ� �뷡�� �ϼ��˴ϴ�!" << endl;
	cout << "ü���� 0�� �Ǹ� ������ ����˴ϴ�! " << endl;
	cout << "�޴��� ���ư��� �ʹٸ� �ƹ� Ű�� �����ּ���!" << endl;
	_getch(); //�ƹ�Ű�� �Է¹���
}

bool menu_function() { //���θ޴� �Լ�

	int choice = 0; //����ڰ� �޴����� ������ ���� �����ϴ� ����

	system("cls"); // �ܼ�â �ʱ�ȭ

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
		play_game(); // ���� ���� �Լ� ȣ��
		if (!game_over()) return false;   //���� ����ڰ� continue?(Y/N) �������� n�� �Է��� ��� 1�� ��ȯ�Ͽ� ���� �����Ŵ
		break;
	case 2:
		help_function(); // ���� ��� �Լ� ȣ��
		break;
	case 3:
		system("cls"); // �ܼ�â �ʱ�ȭ
		return false; // 1�� ��ȯ�ϰ� ���� ����
		break;
	default: // �׿� �Է� ����
		break;
	}
	return true;
}

void GotoXY(int x, int y)		// Ŀ�� ��ġ �̵�
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
