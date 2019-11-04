#include "DJ.h"
#include "word.h"
#define ONE_SECOND 1000 //1000ms=1s
/********************************��������*****************************************/
clock_t g_start_time;                           // ���� �ð�
double g_falling_speed = 2.0;                   // �ܾ� ���� �ð�(�� ����)
//���� ������ �ΰ�//


Word wd[WORD_NUM];
// : txt ���Ͽ��� ��� Word�� �����س� ������ �迭
vector<Word> word;
// : ������ �ܾ���� �����ϴ� vector
vector<string> v(MAP_Y, "��                                                                          ��");
//����� �ܾ���� string���� ������ �ִ� vector �⺻������ |    | ��°��� ������ ����.(�� ���̵�)



/********************************�ʱ�ȭ*****************************************/
void InitData(void)
{
	int cnt = 0;
	string filePath = "g_words.txt";

	ifstream openFile(filePath.data());
	if (openFile.is_open()) {
		string line;
		while (getline(openFile, line)) {
			wd[cnt] = Word(line);
			cnt++;
		}
		openFile.close();
	}
	cout << endl << endl;
	//cout << "word array" << endl;
	//for (auto i : wd) {
	//	cout << i.get_name() << " ";
	//}
	//cout << endl<<endl;
}
//�ؽ�Ʈ���Ͽ��� wd�迭�� �����͸� �����Ѵ�.

void game_init(void) {
	g_start_time = clock();
	//�õ�
	srand((unsigned int)time(NULL));
	//Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	InitData();
}
//���ӵ��� �ʱ⼳������ �������ش�.



/********************************ȭ��*******************************************/
bool is_ch(void)
{
	if (_kbhit()) {
		_getch();
		return true;
	}
	return false;
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

	do { //�ƹ� Ű�� �Է��ϸ� ����ȭ������ ��ȯ�� 
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		_getch();
		puts("");
		Sleep(ONE_SECOND);
	} while (_kbhit());

	/*while (1) {//Ű�Է��� ������ �� ���� �����δ�
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(1000);
		if (is_ch) break;
		cout << "\r\t \t \t \t \t \t                 ";
		Sleep(1000);
		if (is_ch) break;
	}*/
	system("cls");
}
//Ÿ��Ʋȭ��

void display(void) {
	cout<<"exit�Է½� ���ӿ���"<<endl;
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//���
	for (auto str : v)
		cout << str << endl;																																			//�ܾ�ε�
	printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");//�ϴ�
	cout << "____________________________________________________________________________" << endl;

}
//����displays ����ؼ� ���ŵǸ�, �ܾ���� �����ǰ� ��������

bool game_over(void) {
	
	word.clear();//������ �ܾ� clear
	fill(v.begin(), v.begin() + MAP_Y, "��                                                                          ��");

	cout << "\n\n\n\n";
	cout << "\t������������������������  ��������  ��������������" << endl;
	cout << "\t�� ������������������   �� �������������� ������" << endl;
	cout << "\t�������� ���� ��������  ������ ���� ������������" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ./filePath.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	string s;	cout << "\t>> ";	cin >> s;
	if (s == "y" || s == "Y") {
		system("cls");
		return true;
	}
	else {
		system("cls");
		return false;
	}
}
//���ӿ���ȭ��



/********************************�ܾ����*******************************************/
void make_word(void) {
	v.pop_back();
	string s;
	vector<string>::iterator iter=v.begin();
	
	int idx = rand() % WORD_NUM;// ������ �� �ִ� �ܾ� ���� ������ ����index ����
	word.push_back(wd[idx]); // ������ �ܾ��Ͽ� �־��ش�.

	s=make_string(wd[idx]); // �ܾ ���ڿ��� �ٲ㼭
	v.insert(iter,s); // ������ ���ڿ��� MAP�� ǥ���� ���Ϳ� �־��ش�.
}
//�������� wd�迭���� �ܾ��ϳ��� ������ ����display�� ǥ���� �� �ֵ��� ������ش�.

string make_string(Word wd) {
	int len = wd.get_name().length();
	string s;
	if (len > 0) {//�������� ��ĭ�� ���� ������ش�.
		int r = MAP_X - len;
		int a = rand() % r;
		int b = r - a;
		s = "��";	s += print_space(a);	s += wd.get_name();		s += print_space(b);		s += "��";
	}
	else {
		s = "��";	s += print_space(MAP_X);	s += "��";
	}
	return s;
}
//display�� ǥ���� �� �ֵ��� ���ڿ��� ������ش�.

string print_space(int a) {
	string s = "";
	for (int i = 0; i < a; i++) {
		s += " ";
	}
	return s;
}
//�����ȼ���ŭ �����̽��ٸ� ������ش�. ���������ڵ����



void play_game(void) {
	vector<Word>::iterator witer;

	display();// TODO : �̰� �ʴ����� ���Ž��������

	string s;	cout << ">> ";	cin >> s;
	if (s == "exit") { system("cls"); return; }

	for (witer = word.begin(); witer != word.end();++witer) {//���� ���¼������ �˻�
		if ((*witer).get_name() == s) {//���ڿ��� ã�Ҵٸ�
			for (int i = MAP_Y-1; i >= 0; i--) {//�� ���ʺ��� �´´ܾ� Ž��
				if (v[i].find(s) != -1) {
					word.erase(witer);//������ �ܾ� ��Ͽ��� ����
					v[i] = make_string(Word());//���ڿ��� �ٲ�
					break;
				}
			}
			break;
		}
	}
	make_word();//�ܾ� �������ְ�

	system("cls");
	return play_game();//�� ��ε�
}

