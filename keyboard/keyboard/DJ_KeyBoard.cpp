#include "DJ.h"
#include "word.h"
#define ONE_SECOND 1000 //1000ms=1s
/********************************전역변수*****************************************/
clock_t g_start_time;                           // 기준 시각
double g_falling_speed = 2.0;                   // 단어 낙하 시각(초 단위)
//아직 사용못한 두개//


Word wd[WORD_NUM];
// : txt 파일에서 모든 Word를 추출해내 저장한 배열
vector<Word> word;
// : 생성된 단어들을 저장하는 vector
vector<string> v(MAP_Y, "│                                                                          │");
//출력할 단어들을 string으로 가지고 있는 vector 기본값으로 |    | 출력값을 가지고 있음.(맵 사이드)



/********************************초기화*****************************************/
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
//텍스트파일에서 wd배열로 데이터를 추출한다.

void game_init(void) {
	g_start_time = clock();
	//시드
	srand((unsigned int)time(NULL));
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	InitData();
}
//게임들의 초기설정들을 지정해준다.



/********************************화면*******************************************/
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

	do { //아무 키나 입력하면 다음화면으로 전환함 
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		_getch();
		puts("");
		Sleep(ONE_SECOND);
	} while (_kbhit());

	/*while (1) {//키입력이 감지될 때 까지 깜빡인다
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(1000);
		if (is_ch) break;
		cout << "\r\t \t \t \t \t \t                 ";
		Sleep(1000);
		if (is_ch) break;
	}*/
	system("cls");
}
//타이틀화면

void display(void) {
	cout<<"exit입력시 게임오버"<<endl;
	printf("┌──────────────────────────────────────────────────────────────────────────┐\n");//상단
	for (auto str : v)
		cout << str << endl;																																			//단어로딩
	printf("└──────────────────────────────────────────────────────────────────────────┘\n");//하단
	cout << "____________________________________________________________________________" << endl;

}
//게임displays 계속해서 갱신되며, 단어들이 생성되고 지워진다

bool game_over(void) {
	
	word.clear();//생성된 단어 clear
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
		return true;
	}
	else {
		system("cls");
		return false;
	}
}
//게임오버화면



/********************************단어생성*******************************************/
void make_word(void) {
	v.pop_back();
	string s;
	vector<string>::iterator iter=v.begin();
	
	int idx = rand() % WORD_NUM;// 생성할 수 있는 단어 종류 내에서 랜덤index 생성
	word.push_back(wd[idx]); // 생성된 단어목록에 넣어준다.

	s=make_string(wd[idx]); // 단어를 문자열로 바꿔서
	v.insert(iter,s); // 생성된 문자열을 MAP에 표시할 벡터에 넣어준다.
}
//랜덤으로 wd배열에서 단어하나를 추출해 게임display에 표시할 수 있도록 만들어준다.

string make_string(Word wd) {
	int len = wd.get_name().length();
	string s;
	if (len > 0) {//랜덤으로 빈칸을 만들어서 출력해준다.
		int r = MAP_X - len;
		int a = rand() % r;
		int b = r - a;
		s = "│";	s += print_space(a);	s += wd.get_name();		s += print_space(b);		s += "│";
	}
	else {
		s = "│";	s += print_space(MAP_X);	s += "│";
	}
	return s;
}
//display에 표시할 수 있도록 문자열로 만들어준다.

string print_space(int a) {
	string s = "";
	for (int i = 0; i < a; i++) {
		s += " ";
	}
	return s;
}
//지정된수만큼 스페이스바를 출력해준다. 지저분한코드방지



void play_game(void) {
	vector<Word>::iterator witer;

	display();// TODO : 이걸 초단위로 갱신시켜줘야함

	string s;	cout << ">> ";	cin >> s;
	if (s == "exit") { system("cls"); return; }

	for (witer = word.begin(); witer != word.end();++witer) {//먼저 들어온순서대로 검사
		if ((*witer).get_name() == s) {//문자열을 찾았다면
			for (int i = MAP_Y-1; i >= 0; i--) {//맵 및쪽부터 맞는단어 탐색
				if (v[i].find(s) != -1) {
					word.erase(witer);//생성된 단어 목록에서 삭제
					v[i] = make_string(Word());//빈문자열로 바꿈
					break;
				}
			}
			break;
		}
	}
	make_word();//단어 생성해주고

	system("cls");
	return play_game();//맵 재로딩
}

