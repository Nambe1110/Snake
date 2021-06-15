#include "Drawing_FUNCTION.h"
#include "SConsole.h"
using namespace std;

// vẽ biểu tượng snake
void DrawingText(char Text, int x, int y)
{
	if (Text == 65 || Text == 97)
	{
		gotoXY(x, y);     cout << "   00  ";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00  00";     Sleep(40);
		gotoXY(x, y + 2); cout << " 00  00";     Sleep(40);
		gotoXY(x, y + 3); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 4); cout << " 00  00";     Sleep(40);
	}

	else if (Text == 69 || Text == 101)
	{
		gotoXY(x, y);     cout << " 000000";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 2); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 3); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 4); cout << " 000000";     Sleep(40);
	}

	else if (Text == 75 || Text == 107)
	{
		gotoXY(x, y);     cout << "00    00";   Sleep(40);
		gotoXY(x, y + 1); cout << "00   00 ";   Sleep(40);
		gotoXY(x, y + 2); cout << "00 0 0  ";   Sleep(40);
		gotoXY(x, y + 3); cout << "00  00  ";   Sleep(40);
		gotoXY(x, y + 4); cout << "00    00";   Sleep(40);
	}

	else if (Text == 78 || Text == 110)
	{
		gotoXY(x, y);     cout << "00     00";  Sleep(40);
		gotoXY(x, y + 1); cout << "00 0   00";  Sleep(40);
		gotoXY(x, y + 2); cout << "00  0  00";  Sleep(40);
		gotoXY(x, y + 3); cout << "00   0 00";  Sleep(40);
		gotoXY(x, y + 4); cout << "00     00";  Sleep(40);
	}

	else if (Text == 83 || Text == 115)
	{
		gotoXY(x, y);     cout << " 000000";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 2); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 3); cout << "     00.";     Sleep(40);
		gotoXY(x, y + 4); cout << " 000000";     Sleep(40);
	}
	////
	else if (Text == 84 || Text == 116)
	{
		gotoXY(x, y);     cout << " 00000000";     Sleep(40);
		gotoXY(x, y + 1); cout << "    00   ";     Sleep(40);
		gotoXY(x, y + 2); cout << "    00   ";     Sleep(40);
		gotoXY(x, y + 3); cout << "    00   ";     Sleep(40);
		gotoXY(x, y + 4); cout << "    00   ";     Sleep(40);
	}

	else if (Text == 77 || Text == 109)
	{
		gotoXY(x, y);     cout << " 00     00";     Sleep(40);
		gotoXY(x, y + 1); cout << " 000   000";     Sleep(40);
		gotoXY(x, y + 2); cout << " 00  0  00";     Sleep(40);
		gotoXY(x, y + 3); cout << " 00     00";     Sleep(40);
		gotoXY(x, y + 4); cout << " 00     00";     Sleep(40);
	}

	else if (Text == 53)
	{
		gotoXY(x, y);     cout << " 0000000";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 2); cout << " 0000000";     Sleep(40);
		gotoXY(x, y + 3); cout << "      00";     Sleep(40);
		gotoXY(x, y + 4); cout << " 0000000";     Sleep(40);
	}

}
// vẽ logo nhóm 5
void print_team()
{
	setTextColor(244);
	DrawingText('T', 29, 9);
	DrawingText('E', 39, 9);
	DrawingText('A', 49, 9);
	DrawingText('M', 59, 9);
	DrawingText('5', 78, 9);

	Sleep(200);

}
// hiện biểu tượng loading
void logo_loading()
{
	clearscreen();
	print_team();
	setTextColor(244);
	gotoXY(55, 15); cout << "LOADING...";
	for (int i = 40;i < 58;i++)
	{
		gotoXY(i, 17);putchar(219); Sleep(40);
	}
	for (int i = 58;i < 68;i++)
	{
		gotoXY(i, 17);putchar(219); Sleep(30);
	}
	for (int i = 68;i < 77;i++)
	{
		gotoXY(i, 17);putchar(219);
		Sleep(20);
	}

	Sleep(300);
	clearscreen();
}
// icon khi thua
void logo_lost()
{
	clearscreen();
	setTextColor(244);
	int x = 35;
	int y = 2;
	gotoXY(x, y);     cout << " 000000";    
	gotoXY(x, y + 1); cout << " 00    ";    
	gotoXY(x, y + 2); cout << " 000000";     
	gotoXY(x, y + 3); cout << "     00.";    
	gotoXY(x, y + 4); cout << " 000000";     

	x = 45;
	gotoXY(x, y);     cout << "00     00";  Sleep(40);
	gotoXY(x, y + 1); cout << "00 0   00";  Sleep(40);
	gotoXY(x, y + 2); cout << "00  0  00";  Sleep(40);
	gotoXY(x, y + 3); cout << "00   0 00";  Sleep(40);
	gotoXY(x, y + 4); cout << "00     00";  Sleep(40);

	x = 55;
	gotoXY(x, y);     cout << "   00  ";     Sleep(40);
	gotoXY(x, y + 1); cout << " 00  00";     Sleep(40);
	gotoXY(x, y + 2); cout << " 00  00";     Sleep(40);
	gotoXY(x, y + 3); cout << " 000000";     Sleep(40);
	gotoXY(x, y + 4); cout << " 00  00";     Sleep(40);

	x = 65;
	gotoXY(x, y);     cout << "00    00";   Sleep(40);
	gotoXY(x, y + 1); cout << "00   00 ";   Sleep(40);
	gotoXY(x, y + 2); cout << "00 0 0  ";   Sleep(40);
	gotoXY(x, y + 3); cout << "00  00  ";   Sleep(40);
	gotoXY(x, y + 4); cout << "00    00";   Sleep(40);

	x = 75;
	gotoXY(x, y);     cout << " 000000";     Sleep(40);
	gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
	gotoXY(x, y + 2); cout << " 000000";     Sleep(40);
	gotoXY(x, y + 3); cout << " 00    ";     Sleep(40);
	gotoXY(x, y + 4); cout << " 000000";     Sleep(40);

	x = 8;
	int a = 52;
	gotoXY(a, x);     cout << " xxxxxxxxxxxxx ";
	gotoXY(a, x + 1); cout << "x             x";
	gotoXY(a, x + 2); cout << "x    x   x    x";
	gotoXY(a, x + 3); cout << "x             x";
	gotoXY(a, x + 4); cout << "x   xxxxxxx   x";
	gotoXY(a, x + 5); cout << "x x         x x";
	gotoXY(a, x + 6); cout << "x             x";
	gotoXY(a, x + 7); cout << " xxxxxxxxxxxxx ";
	gotoXY(a - 1, x + 9);

	cout << "Oh no!! You lose.";

	Sleep(1500);
}
// icon khi win game
void logo_win()
{
	clearscreen();
	int a = 45, x = 8;
	setTextColor(244);
	gotoXY(a, x);     cout << "00    00                     ";
	gotoXY(a, x + 1); cout << " 00  00   0000000   00     00  ";
	gotoXY(a, x + 2); cout << "  0000   00     00  00     00  ";
	gotoXY(a, x + 3); cout << "   00    00     00  00     00  ";
	gotoXY(a, x + 4); cout << "   00     0000000    0000000    ";

	a = 46, x = 16;
	gotoXY(a, x);     cout << "00       00   00   00      00       00        ";
	gotoXY(a, x + 1); cout << "00       00   00   00 0    00       00     ";
	gotoXY(a, x + 2); cout << "00   0   00   00   00  0   00       00        ";
	gotoXY(a, x + 3); cout << "00 0   0 00   00   00    0 00              ";
	gotoXY(a, x + 4); cout << "00       00   00   00      00       00       ";

	a = 15, x = 9;
	for (int i = 21;i < 36;i++)
	{
		gotoXY(i, x);
		putchar(223);
	}
	gotoXY(a, x + 1);cout << "      xx           xx ";
	gotoXY(a, x + 2);cout << "       xx         xx  ";
	gotoXY(a, x + 3);cout << "   x x xx         xx x x  ";
	gotoXY(a, x + 4);cout << " x     xx         xx     x  ";
	gotoXY(a, x + 5);cout << " x      xxxx   xxxx      x ";
	gotoXY(a, x + 6);cout << " x        x xxx x        x  ";
	gotoXY(a, x + 7);cout << "  x  x x  x xxx x x x  x  ";
	gotoXY(a, x + 8);cout << "            xxx            ";
	gotoXY(a, x + 9);cout << "            xxx            ";
	gotoXY(a, x + 10);cout << "            xxx            ";
	gotoXY(a, x + 11);cout << "           xxxxx           ";

	Sleep(2200);
}

// logo snake
void printlogo()
{
	setTextColor(244);
	DrawingText('S', 29, 2);
	DrawingText('N', 39, 2);
	DrawingText('A', 49, 2);
	DrawingText('K', 59, 2);
	DrawingText('E', 68, 2);
}
// icon khi pause game
void logo_pause()
{
	int a = 35, x = 8;
	setTextColor(244);
	gotoXY(a, x);     cout << "0000000     0000     00    00   0000000  0000000";
	gotoXY(a, x + 1); cout << "00    00  00    00   00    00   00       00     ";
	gotoXY(a, x + 2); cout << "0000000   00 00 00   00    00   0000000  0000000";
	gotoXY(a, x + 3); cout << "00        00    00   00    00        00  00     ";
	gotoXY(a, x + 4); cout << "00        00    00    000000    0000000  0000000";

}

void xoa_khung() {
	setTextColor(244);
	for (int i = 10; i <= 16; i++)
		for (int j = 30; j <= 60;j++) {
			gotoXY(j, i);
			putchar(' ');
		}
}

void ve_khung() {
	setTextColor(244);
	for (int i = 30; i <= 60; i++) {
		gotoXY(i, 10); putchar(NGANGTREN);
		gotoXY(i, 16); putchar(NGANGDUOI);
	}

	for (int i = 11; i < 16; i++) {
		gotoXY(30, i); putchar(DOC);
		gotoXY(60, i); putchar(DOC);
	}
}
// ve khung yes-no
// yes tra ve true no tra ve false
bool khung_yesno(const char* message) {

	xoa_khung();
	ve_khung();

	setTextColor(240);
	gotoXY(34, 12); puts(message);
	setTextColor(244);
	gotoXY(38, 14); puts("CO");
	setTextColor(240);
	gotoXY(50, 14); puts("KHONG");

	int x_cur = 38;
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == KEY_LEFT) {
				if (x_cur != 38) {
					x_cur = 38;
					setTextColor(244);
					gotoXY(38, 14); puts("CO");
					setTextColor(240);
					gotoXY(50, 14); puts("KHONG");
				}
			}
			else if (key == KEY_RIGHT) {
				if (x_cur == 38) {
					x_cur = 50;
					setTextColor(244);
					gotoXY(50, 14); puts("KHONG");
					setTextColor(240);
					gotoXY(38, 14); puts("CO");
				}
			}
			else if (key == KEY_ENTER)
				break;
		}
	}

	xoa_khung();
	return x_cur == 38;
}
// in menu
void printmenu()
{

	gotoXY(45, 10);
	setTextColor(244);
	cout << " 1->NEW GAME";
	Sleep(200);
	gotoXY(45, 10);
	setTextColor(240);
	cout << " 1->NEW GAME";

	gotoXY(45, 12);
	setTextColor(244);
	cout << " 2->LOAD GAME";
	Sleep(200);
	gotoXY(45, 12);
	setTextColor(240);
	cout << " 2->LOAD GAME";

	gotoXY(45, 14);
	setTextColor(244);
	cout << " 3->EXIT";
	Sleep(200);
	gotoXY(45, 14);
	setTextColor(240);
	cout << " 3->EXIT";

}
// ve tuong
void createwall(int style)
{
	// toa do tuong : x = 5 -> 5 + chieu dai tuong
	//         y = 5 -> 5 + chieu rong tuong
	int x = 5;
	int y = 6;
	// ve tuong co hieu ung
	setTextColor(244);
	if (style == 1)
	{
		while (y < 5 + consoley)
		{
			gotoXY(5, y);
			putchar(219);
			gotoXY(5 + consolex, y);
			putchar(219);
			Sleep(10);
			y++;
		}
		while (x <= 5 + consolex)
		{
			gotoXY(x, 5);
			putchar(220);
			gotoXY(2 * 5 + consolex - x, 5 + consoley);
			putchar(223);
			Sleep(10);
			x++;
		}
	}
	// ve tuong khong hieu ung
	if (style == 0)
	{
		for (int i = 5; i <= 5 + consolex; i++)
		{
			gotoXY(i, 5);
			putchar(220);
			gotoXY(i, 5 + consoley);
			putchar(223);
		}
		for (int i = 6; i < 5 + consoley; i++)
		{
			gotoXY(5, i);
			putchar(219);
			gotoXY(5 + consolex, i);
			putchar(219);
		}
	}
}
// in huong dan choi
void guide()
{
	setTextColor(244);
	gotoXY(16 + consolex, 13);
	cout << " SNAKE GUIDE ";
	gotoXY(11 + consolex, 14);
	cout << " 'UP'   : moving up ";
	gotoXY(11 + consolex, 15);
	cout << " 'DOWN' : moving down";
	gotoXY(11 + consolex, 16);
	cout << " 'LEFT' : turn left ";
	gotoXY(11 + consolex, 17);
	cout << " 'RIGHT': turn right";
	gotoXY(11 + consolex, 18);
	cout << " 'SPACE': pause game";
	gotoXY(11 + consolex, 19);
	cout << " 'S'    : save game";
	gotoXY(11 + consolex, 20);
	cout << " 'ESC'  : return to Menu";
	
}