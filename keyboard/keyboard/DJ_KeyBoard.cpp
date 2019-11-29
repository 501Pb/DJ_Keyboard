#include "DJ.h"
#include "word.h"
#include "music.h"
/********************************?„ì—­ë³€??****************************************/
Music music = Music();
clock_t g_start_time;                           // ê¸°ì? ?œê°(ê²Œì„ ?œì‘)
clock_t g_end_time;								// ê²Œì„ ì¢…ë£Œ ?œê°„
double g_falling_speed = 2.0;                   // ?¨ì–´ ?™í•˜ ?œê°(ì´??¨ìœ„)

int ph; //ì²´ë ¥ ?€??
char input_word[1024]; // ?¬ìš©???…ë ¥ ê°??€??
const char* EXIT = "exit"; // exit ë¬¸ì?´ì„ ?€??(?¬ìš©?ê? exitë¥??…ë ¥?ˆì„ ??ê²Œì„???ë‚¨)
int word_len; //?¬ìš©?ê? ?…ë ¥???¨ì–´ ì¤??•í™•?˜ê²Œ ?…ë ¥???¨ì–´??ê¸¸ì´ ?€?¥í•  ë³€??
bool playing;
const char* AllWord[10] //?°ì„±ë¹?ê²Œì„?ì„œ ì¶œë ¥???¨ì–´
= {
	"DJ",
	"tiger",
	"key",
	"rabbit",
	"flower",
	"box",
	"ball",
	"board","","" };


typedef struct { //?¨ì–´ êµ¬ì¡°ì²?
	int x; //?¨ì–´??xì¢Œí‘œ
	char words[20]; //?¨ì–´ ?€??ê³µê°„
} rain_word;
rain_word rain_words[21]; //20ë²ˆì§¸ rains???ì •??0~19ê¹Œì?ë§??”ë©´ ì¶œë ¥ ê°€??

static pthread_t p_thread1; // ?¤ë ˆ???´ë¦„
static int thr_id1; // ?¤ë ˆ?œì˜ ?„ì´??
static int thr_exit = 1; // ?¤ë ˆ??ì¢…ë£Œ ?¬ë? ?íƒœ

/********************************ì´ˆê¸°??****************************************/
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
	//?œë“œ
	//srand((unsigned int)time(NULL));
	//ì»¤ì„œ ?¨ê¸°ê¸?
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	//ì§€?•ëœ ì½˜ì†” ?¤í¬ë¦?ë²„í¼???€?˜ì—¬ ì»¤ì„œ???•íƒœ (?ê»˜ or ?¸ì¶œ?¬ë?) ë¥??¤ì •?˜ëŠ” ??• ????
	//ë§¤ê°œë³€?˜ë¡œ ì½˜ì†” ?¤í¬ë¦?ë²„í¼???€???¸ë“¤ê³?CONSOLE_CURSUR_INFO êµ¬ì¡°ì²´ë? ?˜ê²¨ì¤?
}
//ê²Œì„?¤ì˜ ì´ˆê¸°?¤ì •?¤ì„ ì§€?•í•´ì¤€??

/********************************?”ë©´*******************************************/

void title(void) {

	//PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	textcolor(LIGHTBLUE,BLACK); //?”ë©´?€ ë¸”ë™, ê¸€?ëŠ” ë¸”ë£¨ë¡?ì¶œë ¥
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
	*/textcolor(YELLOW, BLACK); //?”ë©´?€ ë¸”ë™, ê¸€?ëŠ” ?ë¡œ?°ë¡œ ì¶œë ¥
	do { //???…ë ¥ë°›ìœ¼ë©??¤ìŒ ?”ë©´?¼ë¡œ ?˜ì–´ê°?
		cout << "\r\t \t \t \t \t \t Press Any Key...";
		Sleep(ONE_SECOND);
		puts("");
		_getch(); //?…ë ¥?€ ë°›ì?ë§?ë¬´ì—‡???…ë ¥?ˆëŠ”ì§€ ë³´ì—¬ì£¼ì? ?ŠëŠ” ?¨ìˆ˜
		Sleep(ONE_SECOND);
	} while (_kbhit()); //?¤ë³´?œê? ?…ë ¥???íƒœ?¸ì? ?•ì¸?˜ëŠ” ?¨ìˆ˜

	system("cls");
}
//?€?´í??”ë©´

void display(void) {

	int len; // Ãâ·ÂÇÏ´Â ´Ü¾î ±æÀÌ

	GotoXY(0, 0);
	printf("\t exit ÀÔ·Â½Ã °ÔÀÓ¿À¹ö \t\t\t [Ã¼·Â] %.1d \n", ph); //ÇöÀç Ã¼·Â Ãâ·Â
	GotoXY(1, 1);
	printf("¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n");//»ó´Ü
	GotoXY(1, 23);
	printf("¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡\n");//ÇÏ´Ü
	GotoXY(5, 25); //»ç¿ëÀÚ ÀÔ·ÂºÎºĞ
	cout << ">>                                                                             ";                                             

	int pos = 7;
	for (int i = 3; i <= 23; i++) {
			
			GotoXY(rain_words[i - 3].x, i);       //ë¬´ì‘???„ì¹˜ë¡??¨ì–´ ?´ë™ 
			cout << rain_words[i - 3].words;      // ?„ì¬ ?„ì¹˜???¨ì–´ ì¶œë ¥

			len = strlen(rain_words[i - 3].words); //ì¶œë ¥???¨ì–´ ê¸¸ì´ë¥?lenë³€?˜ì— ?€??
			
			if (i > 3) {

				
				GotoXY(rain_words[i - 3].x, i - 1); //ÀÌÀü À§Ä¡ÀÇ ´Ü¾î·Î ÀÌµ¿

				for (int i = 0; i < len; i++) cout << " "; // ?´ì „ ?„ì¹˜???¨ì–´ ì¶œë ¥ ì§€?€
			}

			
			GotoXY(pos, 25); //»ç¿ëÀÚ ÀÔ·ÂºÎºĞ

			printf("%s", input_word);

		Sleep(60000 / (130 * 16));
		// ?¨ì–´ê°€ ?¨ì–´ì§€???ë„ ì¡°ì ˆ
	}
	
	if ((strlen(rain_words[20].words) >1) && (strcmp(rain_words[20].words, " "))) // 20ë²ˆì§¸ ì¤„ì— ?¨ì–´ê°€ ?ˆëŠ” ê²½ìš°
		ph -= 1; // ?¨ì–´ ?…ë ¥ ëª»í• ?Œë§ˆ??ì²´ë ¥??1??ê°ì†Œ??
}

bool game_over(void) {
	textcolor(RED, WHITE); //?”ë©´?€ ?”ì´?? ê¸€?ëŠ” ?ˆë“œë¡?ì¶œë ¥
	system("cls");
	music.note_clear();
	cout << "\n\n\n\n";
	cout << "\t¦£¦¡¦¤¦£¦¡¦¤¦£¦¨¦¤¦£¦¡¦¤  ¦£¦¡¦¤¦¨  ¦¨¦£¦¡¦¤¦¨¦¡¦¤" << endl;
	cout << "\t¦¢ ¦¨¦§¦¡¦©¦¢¦¢¦¢¦§¦©     ¦¢ ¦¢¦¦¦¤¦£¦¥¦§¦© ¦§¦¨¦¥" << endl;
	cout << "\t¦¦¦¡¦¥¦ª ¦ª¦ª ¦ª¦¦¦¡¦¥    ¦¦¦¡¦¥ ¦¦¦¥ ¦¦¦¡¦¥¦ª¦¦¦¡" << endl;
	cout << "\n\n\n";
	cout << "\tSave Successfully to ../saveMusic/music.mp3" << endl;
	cout << "\n\n\n\n";
	cout << "\r\tcontinue?(Y/N) " << endl;

	/*y??Yë¥??…ë ¥?˜ë©´ ë©”ë‰´?”ë©´?¼ë¡œ ?˜ì–´ê°€ê³?n?´ë‚˜ N???…ë ¥?˜ë©´ ì¢…ë£Œ??
	 *ê·??¸ì˜ ?¤ë¥¸ ?…ë ¥?€ ë¬´ì‹œ??*/

	GotoXY(5, 25); //?¬ìš©?ì—ê²??…ë ¥ë°›ì„ ?„ì¹˜ë¡??´ë™
	string s;
	cout << ">> ";

	while (1)
	{
		s = _getch(); //?¬ìš©?ì—ê²?y??n???…ë ¥ë°›ìŒ
		
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

//ê²Œì„?¤ë²„?”ë©´

/********************************?¨ì–´?ì„±*******************************************/
void random_word(void) { //?¨ì–´ ?ì„± ?¨ìˆ˜

	for (int i = 20; i > 0; i--) {
		
		strcpy(rain_words[i].words, rain_words[i - 1].words); // ±âÁ¸ ´Ü¾î¸¦ ´ÙÀ½ ¹è¿­·Î ³Ñ±è
		rain_words[i].x = rain_words[i - 1].x; //±âÁ¸ ´Ü¾îÀÇ xÁÂÇ¥¸¦ ´ÙÀ½ ¹è¿­ À§Ä¡·Î ³Ñ±è
		rain_words[i - 1].x = 0; 
		strcpy(rain_words[i - 1].words, " "); // µŞ ÁÙÀº °ø¹éÃ³¸®


	}

	rain_words[0].x = rand() % 12 * 6; //³­¼ö »ı¼º 6ÀÇ ¹è¼ö ³­¼ö »ı¼º)
	srand(time(NULL));
	if (rain_words[0].x == rain_words[1].x) rain_words[0].x = rand() % 12 * 6; //´Ü¾îÀÇ xÁÂÇ¥°¡ °°À¸¸é ³­¼ö ´Ù½Ã »ı¼º
	strcpy(rain_words[0].words, AllWord[rand() % 10]); // »õ·Î¿î ´Ü¾î¸¦ ¹«ÀÛÀ§·Î ¹èÄ¡

}

void play_game() { //ê²Œì„ ì§„í–‰ ?¨ìˆ˜

	textcolor(LIGHTBLUE, BLACK); //?”ë©´?€ ?”ì´?? ê¸€?ëŠ” ë¸”ë£¨ë¡?ì¶œë ¥
	ph = 3; //ì²´ë ¥ 3?¼ë¡œ ì´ˆê¸°??
	system("cls"); //ì½˜ì†”ì°?ì´ˆê¸°??
	InitData(); //?¨ì–´ ë°°ì—´ ì´ˆê¸°??
	g_start_time = clock();
	start_thread(); //?¤ë ˆ???œì‘
	playing = true;
	while (1) {

		display(); //È­¸é Ãâ·Â
		//´Ü¾î Ãâ·Â
		random_word();//´Ü¾î »ı¼ºÇØÁÖ°í
		g_end_time = clock(); //ÇØ´ç ´Ü¾î°¡ »ı¼ºµÈ ½Ã°£ ±â·Ï

		if (!playing)	break; //exit ÀÔ·Â½Ã Á¾·á
		if (ph <= 0) break; // Ã¼·ÂÀÌ 0 ÀÌ¸é °ÔÀÓ Á¾·áµÊ

	}

	end_thread(); //?¤ë ˆ??ì¤‘ì?
}

void* t_function(void* data) // ?¤ë ˆ??ì²˜ë¦¬???¨ì–´ ?…ë ¥ ?¨ìˆ˜
{
	while (!thr_exit) // ?¤ë ˆ?œê? ì¤‘ì????Œê¹Œì§€ ?…ë ¥??ê³„ì† ë°›ìŒ
	{
		char c = 0;
		if (_kbhit())
		{
			c = _getch();
			int input_word_len = strlen(input_word);
			if (c == 13)
			{
				system("cls");
			} //?¨ì–´ ?…ë ¥?˜ê³  ?”í„°ì¹˜ë©´ ?”ë©´ ì´ˆê¸°?”ì‹œì¼œì¤Œ
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
				if (strstr(rain_words[i].words, input_word)) {// ?…ë ¥???¨ì–´?€ ?…ë ¥ê°’ì´ ê°™ì? ê²½ìš° 
					strcpy(rain_words[i].words, ""); // ?´ë‹¹ ?¨ì–´ ?œê±°
					word_len = strlen(input_word); //?Œì•… ?„ë¡œ?¸ìŠ¤ ë¶€ë¶??¨ìˆ˜???˜ê¸¸ ?¨ì–´ ê¸¸ì´ë¥?êµ¬í•¨
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

void start_thread() // ?¤ë ˆ???œì‘ ?¨ìˆ˜
{
	thr_exit = 0;
	thr_id1 = pthread_create(&p_thread1, NULL, t_function, NULL); // ?¤ë ˆ???ì„±
}

void end_thread() // ?¤ë ˆ??ì¤‘ì? ?¨ìˆ˜
{
	thr_exit = 1;
	pthread_cancel(p_thread1); // ?¤ë ˆ??ì¢…ë£Œ
}

void help_function() // ?„ì?ë§??¨ìˆ˜
{
	textcolor(CYAN, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	system("cls");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t ___   ___  _________   _          __________ " << endl;
	cout << "\t\t\t\t |  | |  |  | ______|  | |         |     __  | " << endl;
	cout << "\t\t\t\t |   -   |  | ______   | |_______  |     ____|" << endl;
	cout << "\t\t\t\t |__| |__|  |_______|  |_|______|  |____|" << endl;
	cout << "\n\n\n";
	textcolor(BROWN, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\t ?˜ëŠ˜?ì„œ ë¹„ì²˜???´ë ¤?¤ëŠ” ?¨ì–´ë¥??¤ë³´?œë¡œ ?…ë ¥?´ì£¼?¸ìš”!" << endl << endl;
	cout << "\t\t\t\t ?¨ì–´ë¥??…ë ¥?˜ë©´ ?¨ì–´??ê¸¸ì´ë§Œí¼ ?Œì´ ?¬ìƒ?©ë‹ˆ??" << endl << endl;
	cout << "\t\t\t\t ì²´ë ¥??0???˜ë©´ ê²Œì„??ì¢…ë£Œ?©ë‹ˆ?? " << endl << endl;
	cout << "\t\t\t\t ê²Œì„??ì¢…ë£Œ?˜ë©´ ?˜ë§Œ???Œì•…???„ì„±?©ë‹ˆ?? " << endl << endl<<endl;
	textcolor(MAGENTA, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\të©”ë‰´ë¡??Œì•„ê°€ê³??¶ë‹¤ë©??„ë¬´ ?¤ë‚˜ ?ŒëŸ¬ì£¼ì„¸??" << endl << endl;
	_getch(); //?„ë¬´?¤ë‚˜ ?…ë ¥ë°›ìŒ
	fflush(stdin);
}

bool menu_function() { //ë©”ì¸ë©”ë‰´ ?¨ìˆ˜
	textcolor(BROWN, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?

	int choice = 0; //?¬ìš©?ê? ë©”ë‰´?ì„œ ? íƒ??ê°’ì„ ?€?¥í•˜??ë³€??

	system("cls"); // ì½˜ì†”ì°?ì´ˆê¸°??
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
	textcolor(BLUE, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\t\t\t 1. GAME START " << endl << endl << endl;
	textcolor(GREEN, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\t\t\t 2. HELP " << endl << endl << endl;
	textcolor(RED, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\t\t\t 3. GAME END " << endl << endl << endl << endl << endl;
	textcolor(BROWN, WHITE); //?”ë©´ê³?ê¸€???‰ìƒ ë³€ê²?
	cout << "\t\t\t\t\t\t MENU NUMBER >> ";
	fflush(stdin);
	// ë©”ë‰´ ? íƒ??ë²ˆí˜¸ 1,2,3 ì¤??˜ë‚˜ë¥??…ë ¥ë°›ìŒ (?˜ë¨¸ì§€ ?…ë ¥?€ ë¬´ì‹œ??
	while (1)
	{
		choice = _getch();

		if (choice == 49) { //?¬ìš©?ê? 1???…ë ¥??ê²½ìš°
			cout << "1";
			system("cls");
			break;
		}
		else if (choice == 50) { //?¬ìš©?ê? 2ë¥??…ë ¥??ê²½ìš°
			cout << "2";
			system("cls");
			break;
		}
		else if (choice == 51) { //?¬ìš©?ê? 3???…ë ¥??ê²½ìš°
			cout << "3";
			system("cls");
			break;
		}
	}

	switch (choice)
	{
	case 49: //?¬ìš©?ê? 1???…ë ¥??ê²½ìš°
		play_game(); // ê²Œì„ ?œì‘ ?¨ìˆ˜ ?¸ì¶œ
		if (!game_over()) return false;   //ë§Œì•½ ?¬ìš©?ê? continue?(Y/N) ì§ˆë¬¸?ì„œ n???…ë ¥??ê²½ìš° false??ë°˜í™˜?˜ì—¬ ê²Œì„ ì¢…ë£Œ?œí‚´
		break;
	case 50: //?¬ìš©?ê? 2ë¥??…ë ¥??ê²½ìš°
		help_function(); // ?„ì?ë§?ì¶œë ¥ ?¨ìˆ˜ ?¸ì¶œ
		break;
	case 51: //?¬ìš©?ê? 3???…ë ¥??ê²½ìš°
		system("cls"); // ì½˜ì†”ì°?ì´ˆê¸°??
		return false; // 1??ë°˜í™˜?˜ê³  ê²Œì„ ì¢…ë£Œ
		break;
	default: // ê·¸ì™¸ ?…ë ¥ ë¬´ì‹œ
		break;
	}
	return true;
}

void GotoXY(int x, int y)		// ì»¤ì„œ ?„ì¹˜ ?´ë™?˜ëŠ” ?¨ìˆ˜
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background)  //ê¸€???‰ìƒ ì¶œë ¥ ?¨ìˆ˜
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
