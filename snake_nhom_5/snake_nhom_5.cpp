#include "SConsole.h"
#include "Drawing_FUNCTION.h"
enum Direction { UP, DOWN, LEFT, RIGHT, PAUSE, SAVE, RETURN };
enum Menu { U, D, ENTER, BACK };
struct coordinate
{
	int x, y;
};
istream& operator >> (istream& inDev, coordinate& toado)
{
	inDev >> toado.x >> toado.y;
	return inDev;
}
ostream& operator << (ostream& outDev, const coordinate& toado)
{
	outDev << toado.x << " " << toado.y;
	return outDev;
}
istream& operator >> (istream& inDev, Direction& dr)
{
	int temp;
	inDev >> temp;
	switch (temp)
	{
	case 0:
		dr = UP;
		break;
	case 1:
		dr = DOWN;
		break;
	case 2:
		dr = LEFT;
		break;
	case 3:
		dr = RIGHT;
		break;
	default:
		break;
	}
	return inDev;
}
ostream& operator << (ostream& outDev, const Direction& dr)
{
	switch (dr)
	{
	case UP:
		outDev << 0;
		break;
	case DOWN:
		outDev << 1;
		break;
	case LEFT:
		outDev << 2;
		break;
	case RIGHT:
		outDev << 3;
		break;
	default:
		break;
	}
	return outDev;
}
struct Snake
{
	coordinate* dot = NULL;
	int length;
	Direction dr;
};
struct gate {
	coordinate td[6];
	Direction direction;
};
typedef struct gate GATE;
GATE ggate;
coordinate obstacle[5] = { {46,13 }, {18, 9}, { 73,18 }, { 18,18 }, { 73,9 } };
coordinate Gate[6] = { {18,14}, {73,14}, {23,8}, {69,8}, {23,19}, {69,19} };
char len[47] = "#19120481@19120529@19120563@19120583@19120595@";

Snake snake;
coordinate food;

int mark, challenge;
bool flagdrawgateout;
bool flagdrawgatein;
bool flagwingame;
bool flagreturnmenu;
typedef char str[100];
str line[3] = { " 1->NEW GAME", " 2->LOAD GAME",  " 3->EXIT" };

void create();
void display(coordinate tail);
void snakecontrol(coordinate& tail);
void processing();
bool gameover();
bool losing();
void createobstacles();
void speed();
Menu key(int z);
int menucontrol(str line[4]);
void DrawGate();
void DrawGateOut();
void GateUP();
void GateDOWN();
void GateLEFT();
void GateRIGHT();
void eraseGate();
bool checkGate();
bool snakeEatGate();
bool gothroughgatein();
bool gothroughgateout();
void snakeInGate();
void snakeOutGate();
void deletelastpart();
bool checkwingame();
void save_game();
bool DrawLoadMenu();

int main()
{
	FixConsoleWindow();
	ResizeConsole(900, 480);
	DeleteScrollbar();
	noCursorType();

	while (true)
	{
		clearscreen();
		logo_loading();
		switch (menucontrol(line))
		{
		case 0:
		{
			clrscr();
			setTextColor(244);
			srand(time(NULL));
			createwall(1);
			create();
			guide();
			coordinate tail = { 0,0 };

			while (true)
			{
				snakecontrol(tail);
				if (flagreturnmenu) break;
				display(tail);
				
				if (checkwingame()) break;
				if (losing()) break;

				processing();

				speed();
			}

			delete[] snake.dot;
			break;
		}
		case 1:
		{
			clrscr();
			if (DrawLoadMenu()) {
				clearscreen();
				setTextColor(244);
				srand(time(NULL));
				createwall(1);
				createobstacles();
				// in cong 
				for (int i = 0; i < 5; i++)
				{
					if (ggate.td[i].x != 0) {
					gotoXY(ggate.td[i].x, ggate.td[i].y);
					putchar(219);
					}
				}
				guide();
				
				coordinate tail = {0,0};
				while (true)
				{
					snakecontrol(tail);
					if (flagreturnmenu) break;
					display(tail);

					if (checkwingame()) break;
					if (losing()) break;

					processing();

					speed();
				}

				delete[] snake.dot;
			}
			break;
		}
		case 2:
		{
			exit(0);
		}
		}

	}
	return 0;
}
// ham khoi tao cac gia tri ban dau
void create()
{
	// diem = 0
	mark = 0;
	// man dau tien la man 1
	challenge = 1;
	// co ve cong out
	flagdrawgateout = false;
	// co ve cong in
	flagdrawgatein = false;
	// co thang game
	flagwingame = false;
	// co thoat game tro ve menu
	flagreturnmenu = false;
	// do dai ban dau cua ran la 1
	snake.length = 1;
	// huong di chuyen ban dau la 5
	snake.dr = RIGHT;
	snake.dot = new coordinate[snake.length];
	// vi tri cac dot ran ban dau
	for (int i = 0; i < snake.length; i++)
	{
		snake.dot[i].x = 8 + snake.length - i - 1;
		snake.dot[i].y = 6;
	}
	// toa do ban dau cua cong
	for (int i = 0; i < 6; i++) ggate.td[i] = { 0, 0 };

	// Tao vi tri hoa qua
	food.x = 7 + rand() % (consolex - 4);
	food.y = 7 + rand() % (consoley - 4);

}

// ham hien thi
void display(coordinate tail)
{
	// neu diem khac 9 in thuc an
	if (mark != 9)
	{
		int i = rand() % 10;
		setTextColor(240+i);
		gotoXY(food.x, food.y);
		putchar('O');
	}
	setTextColor(244);
	gotoXY(11 + consolex, 6);
	cout << "      CHALLENGE " << challenge;
	// in ran
	for (int i = 0; i < snake.length; i++)
	{
		if (snake.dot[i].y != 0 && snake.dot[i].x != 0  )
		{
			gotoXY(snake.dot[i].x, snake.dot[i].y);
			putchar(len[i]);
		}
	}

	// xoa dot cuoi cung khi di chuyen
	gotoXY(tail.x, tail.y);
	cout << " ";
}
// dieu khien ran, xu ly cong 
void snakecontrol(coordinate &tail)
{
	Snake s;
	tail = snake.dot[snake.length - 1];

	// nhan phim
	if (_kbhit())
	{
		char key = _getch();

		// 4 phim di chuyen 
		if (key == KEY_UP && snake.dr != DOWN)		snake.dr = UP;
		else if (key == KEY_DOWN && snake.dr != UP)	snake.dr = DOWN;
		else if (key == KEY_LEFT && snake.dr != RIGHT)	snake.dr = LEFT;
		else if (key == KEY_RIGHT && snake.dr != LEFT)  snake.dr = RIGHT; 
		// Phim SPACE de dung game
		else if (key == 32)
		{
			s.dr = snake.dr;
			snake.dr = PAUSE;
		}
		// phim S de luu game
		else if (key == 's' || key == 'S')
		{
			s.dr = snake.dr;
			snake.dr = SAVE;
		}
		// phim ESC thoat ra menu
		else if (key == KEY_ESC)
		{
			s.dr = snake.dr;
			snake.dr = RETURN;
		}
	}
	// gan toa do cua dot ran sau cho dot ran truoc bat dau tu dot ran cuoi cho den dot ran thu 1
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.dot[i] = snake.dot[i - 1];
	}
	// xu ly toa do do dot ran thu 0
	if (snake.dot[0].x != 0 && snake.dot[0].y != 0)
	{
		if (snake.dr == UP)	snake.dot[0].y--;
		if (snake.dr == DOWN) snake.dot[0].y++;
		if (snake.dr == LEFT) snake.dot[0].x--;
		if (snake.dr == RIGHT) snake.dot[0].x++;
	}

	// Xu ly dung game
	if (snake.dr == PAUSE)
	{
		clearscreen();
		setTextColor(244);
		gotoXY(44, 14);
		cout << "PAUSE. ENTER SPACE TO CONTINUE";
		logo_pause();
		while (true)
		{
			if (_kbhit())
			{
				char key2 = _getch();
				// SPACE
				if (key2 == 32)
				{
					clearscreen();
					snake.dr = s.dr;
					setTextColor(244);
					createwall(0);
					guide();
					for (int i = 0; i < snake.length; i++)
					{
						gotoXY(snake.dot[i].x, snake.dot[i].y);
						putchar(len[i]);
					}
					gotoXY(food.x, food.y);
					putchar('0');
					for (int i = 0; i < 5; i++)
					{
						if (ggate.td[i].x != 0) {
							gotoXY(ggate.td[i].x, ggate.td[i].y);
							putchar(219);
						}
					}
					createobstacles();
					break;
				}
				else
					continue;
			}
		}
	}
	// Xu ly de quay ve menu
	if (snake.dr == RETURN)
	{
		if (khung_yesno("BAN CO MUON TRO VE MENU ?"))
		{
			flagreturnmenu = true;
		}
		else
		{
			snake.dr = s.dr;
			createobstacles();
		}
	}
	// xu ly luu game
	if (snake.dr == SAVE)
	{
		snake.dr = s.dr;
		save_game();
		createobstacles();
	}
	// Neu diem = 9 thi ve cong vao
	if (mark == 9 && flagdrawgatein == false)
	{
		DrawGate();
		flagdrawgatein = true;
	}
	// neu dot ran nao vao trong cong thi gan toa do dot do ve (0 0)
	if (mark == 9 && flagdrawgatein == true && snake.dot[0].x == ggate.td[5].x && snake.dot[0].y == ggate.td[5].y)
	{
		snakeInGate();
	}
	//neu ran vao hoan toan trong cong vao thi xoa cong vao
	// Sau do ve cong ra
	if (flagdrawgatein == true && gothroughgatein())
	{
		eraseGate();
		// neu man hien tai la 5 (man cuoi) -> khi con ran vao hoan toan trong cong thi nguoi choi thang
		challenge++;
		if (challenge == 6)
		{
			flagwingame = true;
			return ;
		}
		setTextColor(252);
		gotoXY(16, 12);
		cout << "Congratulation. A more difficult challenge is waiting for you ";
		mark = 0;
		setTextColor(244);
		gotoXY(11 + consolex, 9);
		cout << "Mark : " << mark;
		Sleep(1000);
		gotoXY(16, 12);
		cout << "                                                              ";
		createobstacles();
		if (!flagwingame)
		{
			flagdrawgatein = false;
			DrawGateOut();
			flagdrawgateout = true;
			snakeOutGate();
		}
	}
	// cac dot ran ra het khoi cong thi xoa cong ra
	if (flagdrawgateout == true && gothroughgateout())
	{
		flagdrawgateout = false;
		eraseGate();
	}
}
void processing()
{
	gotoXY(11 + consolex, 7);
	cout << "Mark : " << mark;
	gotoXY(11 + consolex, 8);
	cout << "Earn 9 marks to come to ";
	gotoXY(11 + consolex, 9);
	cout << "next challenge ";

	// xu ly an hoa qua
	// Neu toa do dau ran trung voi toa do thuc an
	// tao them dot ran moi o phia sau dot ran cuoi cung
	if (snake.dot[0].x == food.x && snake.dot[0].y == food.y && mark != 9)
	{
		snake.length++;
		coordinate* anew = (coordinate*)realloc(snake.dot, (snake.length) * sizeof(coordinate));
		if (anew != NULL)
		{
			if (snake.dr == UP) {
				anew[snake.length - 1].y = anew[snake.length - 2].y++;
				anew[snake.length - 1].x = anew[snake.length - 2].x;
			}
			else if (snake.dr == DOWN)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y--;
				anew[snake.length - 1].x = anew[snake.length - 2].x;
			}
			else if (snake.dr == LEFT)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y;
				anew[snake.length - 1].x = anew[snake.length - 2].x++;
			}
			else if (snake.dr == RIGHT)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y;
				anew[snake.length - 1].x = anew[snake.length - 2].x--;
			}
			snake.dot = anew;
			mark++;
			
			// random lai vi tri hoa qua khi bi an
			food.x = 7 + rand() % (consolex - 4);
			food.y = 7 + rand() % (consoley - 4);
		}

		// xu ly vi tri hoa qua tranh trung voi chuong ngai vat o cac man
		while (food.x == 18 || food.x == 73 || food.x == 46)
			food.x = 7 + rand() % (consolex - 4);
		if (challenge == 5) food.y = 12 + rand() % 6;
		if (mark == 3)
		{
			if (challenge % 2 == 1) food.x = 3 + consolex;
			else food.x = 7;
		}
		if (mark == 6)
		{
			if (challenge % 2 == 1) food.y = 3 + consoley;
			else food.y = 8;
		}
	}

	if (snake.dot[snake.length - 1].y == 6)
	{
		gotoXY(snake.dot[snake.length - 1].x + 1, 5);
		putchar(220);
		gotoXY(snake.dot[snake.length - 1].x , 5);
		putchar(220);
		gotoXY(snake.dot[snake.length - 1].x - 1, 5);
		putchar(220);
	}
	if (snake.dot[snake.length - 1].y == 4 + consoley)
	{
		gotoXY(snake.dot[snake.length - 1].x + 1, 5 + consoley);
		putchar(223);
		gotoXY(snake.dot[snake.length - 1].x, 5 + consoley);
		putchar(223);
		gotoXY(snake.dot[snake.length - 1].x - 1, 5 + consoley);
		putchar(223);
	}
}
// tra ve khi ran cham tuong, cham than , cham chuong ngai vat
bool gameover()
{
	// xu ly cham tuong
	if (snake.dot[0].y == 5) {
		createwall(0);
		return true;
	}
	if (snake.dot[0].y == 5 + consoley) {
		createwall(0);
		return true;
	}
	if (snake.dot[0].x == 5) {
		createwall(0);
		return true;
	}
	if (snake.dot[0].x == 5 + consolex) {
		createwall(0);
		return true;
	}
	// xu ly cham tham
	if (flagdrawgatein == false && flagdrawgateout == false)
		for (int i = 2; i < snake.length; i++)
		{
			if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				return true;
		}
	// xu ly cham chuong ngai vat
	if (challenge == 1) return false;
	if (challenge >= 2)
	{
		if (snake.dot[0].x == obstacle[0].x && snake.dot[0].y == obstacle[0].y)
		{
			gotoXY(obstacle[0].x, obstacle[0].y);
			putchar(219);
			return true;
		}
	}
	if (challenge >= 3)
	{
		if (snake.dot[0].x == obstacle[1].x && snake.dot[0].y == obstacle[1].y)
		{
			gotoXY(obstacle[1].x, obstacle[1].y);
			putchar(219);
			return true;
		}
		if (snake.dot[0].x == obstacle[2].x && snake.dot[0].y == obstacle[2].y) {
			gotoXY(obstacle[2].x, obstacle[2].y);
			putchar(219);
			return true;
		}
	}
	if (challenge >= 4)
	{
		if (snake.dot[0].x == obstacle[3].x && snake.dot[0].y == obstacle[3].y) {
			gotoXY(obstacle[3].x, obstacle[3].y);
			putchar(219);
			return true;
		}
		if (snake.dot[0].x == obstacle[4].x && snake.dot[0].y == obstacle[4].y) {
			gotoXY(obstacle[4].x, obstacle[4].y);
			putchar(219);
			return true;
		}
	}
	if (challenge == 5)
	{
		for (int i = 6; i < 12; i++)
		{
			if (snake.dot[0].x == 28 && snake.dot[0].y == i) {
				gotoXY(28, i);
				putchar(219);
				return true;
			}
		}
		for (int i = 17; i < 23; i++)
		{
			if (snake.dot[0].x == 65 && snake.dot[0].y == i) {
				gotoXY(65, i);
				putchar(219);
				return true;
			}
		}
	}
	return false;
}
// tra ve khi ban thua
bool losing()
{
	if (gameover() || snakeEatGate())
	{
		Sleep(1000);
		logo_lost();
		clearscreen();
		return true;

	}
	return false;
}
// tao vat can o cac man
void createobstacles()
{
	if (challenge == 2)
	{
		gotoXY(obstacle[0].x, obstacle[0].y);
		putchar((char)219);
	}
	else if (challenge == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			gotoXY(obstacle[i].x, obstacle[i].y);
			putchar((char)219);
		}
	}
	else if (challenge == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			gotoXY(obstacle[i].x, obstacle[i].y);
			putchar((char)219);
		}
	}
	else if (challenge == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			gotoXY(obstacle[i].x, obstacle[i].y);
			putchar((char)219);
		}
		for (int i = 6; i < 12; i++)
		{
			gotoXY(28, i);
			putchar(219);
		}
		for (int i = 17; i < 23; i++)
		{
			gotoXY(65, i);
			putchar(219);
		}
	}


}

//ve cong vao
void DrawGate() {
	if (ggate.td[0].x == 0) {
		do
		{
			int u = rand() % 6;

			ggate.td[0].x = Gate[u].x;
			ggate.td[0].y = Gate[u].y;

			if (u == 0)
				GateRIGHT();
			else if (u == 1)
				GateLEFT();
			else if (u == 2)
				GateDOWN();
			else if (u == 3)
				GateDOWN();
			else if (u == 4)
				GateUP();
			else if (u == 5) GateUP();
		} while (checkGate());
	}

	for (int i = 0; i < 5; i++)
	{
		gotoXY(ggate.td[i].x, ggate.td[i].y);
		putchar(219);
	}
}
// ve cong ra
void DrawGateOut()
{
	if (ggate.direction == LEFT)
	{
		ggate.td[0].x = Gate[0].x;
		ggate.td[0].y = Gate[0].y;
		GateRIGHT();
	}
	else if (ggate.direction == RIGHT)
	{
		ggate.td[0].x = Gate[1].x;
		ggate.td[0].y = Gate[1].y;
		GateLEFT();
	}
	else if (ggate.direction == UP)
	{
		ggate.td[0].x = Gate[2].x;
		ggate.td[0].y = Gate[2].y;
		GateDOWN();
	}
	else if (ggate.direction == DOWN)
	{
		ggate.td[0].x = Gate[5].x;
		ggate.td[0].y = Gate[5].y;
		GateUP();
	}

	for (int i = 0; i < 5; i++)
	{
		gotoXY(ggate.td[i].x, ggate.td[i].y);
		putchar(219);
	}
}
// ve cong huong len tren  
void GateUP() {
	ggate.direction = UP;

	ggate.td[1].x = ggate.td[0].x - 1;
	ggate.td[1].y = ggate.td[0].y;

	ggate.td[2].x = ggate.td[0].x + 1;
	ggate.td[2].y = ggate.td[0].y;


	ggate.td[3].x = ggate.td[0].x - 1;
	ggate.td[3].y = ggate.td[0].y - 1;

	ggate.td[4].x = ggate.td[0].x + 1;
	ggate.td[4].y = ggate.td[0].y - 1;

	ggate.td[5].x = ggate.td[0].x;
	ggate.td[5].y = ggate.td[0].y - 1;
}

// ve cong huong xuong duoi		
void GateDOWN() {
	ggate.direction = DOWN;

	ggate.td[1].x = ggate.td[0].x - 1;
	ggate.td[1].y = ggate.td[0].y;

	ggate.td[2].x = ggate.td[0].x + 1;
	ggate.td[2].y = ggate.td[0].y;

	ggate.td[3].x = ggate.td[0].x - 1;
	ggate.td[3].y = ggate.td[0].y + 1;

	ggate.td[4].x = ggate.td[0].x + 1;
	ggate.td[4].y = ggate.td[0].y + 1;

	ggate.td[5].x = ggate.td[0].x;
	ggate.td[5].y = ggate.td[0].y + 1;
}

// ve cong huong sang trai											
void GateLEFT() {
	ggate.direction = LEFT;

	ggate.td[1].x = ggate.td[0].x;
	ggate.td[1].y = ggate.td[0].y - 1;

	ggate.td[2].x = ggate.td[0].x;
	ggate.td[2].y = ggate.td[0].y + 1;

	ggate.td[3].x = ggate.td[0].x - 1;
	ggate.td[3].y = ggate.td[0].y - 1;

	ggate.td[4].x = ggate.td[0].x - 1;
	ggate.td[4].y = ggate.td[0].y + 1;

	ggate.td[5].x = ggate.td[0].x - 1;
	ggate.td[5].y = ggate.td[0].y;
}

// ve cong huong sang trai											
void GateRIGHT() {
	ggate.direction = RIGHT;

	ggate.td[1].x = ggate.td[0].x;
	ggate.td[1].y = ggate.td[0].y - 1;

	ggate.td[2].x = ggate.td[0].x;
	ggate.td[2].y = ggate.td[0].y + 1;

	ggate.td[3].x = ggate.td[0].x + 1;
	ggate.td[3].y = ggate.td[0].y - 1;

	ggate.td[4].x = ggate.td[0].x + 1;
	ggate.td[4].y = ggate.td[0].y + 1;

	ggate.td[5].x = ggate.td[0].x + 1;
	ggate.td[5].y = ggate.td[0].y;
}

// xoa cong
void eraseGate() {
	for (int i = 0; i < 6; i++) {
		gotoXY(ggate.td[i].x, ggate.td[i].y);
		putchar(' ');
		ggate.td[i].x = 0;
		ggate.td[i].y = 0;
	}
}

//kiem tra cong co trung voi snake
bool checkGate() {
	for (int i = 0; i < snake.length; i++)
		for (int j = 0; j < 5; j++)
			if (snake.dot[i].x == ggate.td[j].x && snake.dot[i].y == ggate.td[j].y)
				return true;

	return false;
}

//kiem tra snake co cham cong
bool snakeEatGate()
{
	for (int i = 0; i < 5; i++)
	{
		if (snake.dot[0].x == ggate.td[i].x && snake.dot[0].y == ggate.td[i].y)
		{
			gotoXY(ggate.td[i].x, ggate.td[i].y);
			putchar(219);
			return true;
		}
	}
	return false;
}
// tra ve khi ran vao hoan toan trong cong 
bool gothroughgatein()
{
	// neu dot cuoi cua ran vao hoan toan trong cong thi xoa dot cuoi con hien thi tren man hinh va tra ve true
	if (snake.dot[snake.length - 1].x == 0 && snake.dot[snake.length - 1].y == 0)
	{
		deletelastpart();
		return true;
	}

	return false;
}
//tra ve khi ran vao hoan toan  ra het khoi cong
bool gothroughgateout()
{
	// neu dot ran cuoi cung ra khoi cong tra ve true
	if (snake.dot[snake.length - 1].x != 0 && snake.dot[snake.length - 1].y != 0)
		return true;

	return false;
}
// xu ly khi ran vAO cong
void snakeInGate()
{
	// neu dot ran dau vao cong thi gan toa do cua no bang (0 0) cac dot sau se co toa do thay doi theo dot dau
	if (snake.dot[0].x == ggate.td[5].x && snake.dot[0].y == ggate.td[5].y)
	{
		snake.dot[0].x = 0;
		snake.dot[0].y = 0;
	}
}
// xu ly khi ra ra khoi cong
void snakeOutGate()
{
	// khi ran bat dau ra khoi cong , gan toa do dot ran dau bang toa do khe cong
	//( toa do cac dot ran sau se thay doi theo dot ran dau )
	snake.dot[0].x = ggate.td[5].x;
	snake.dot[0].y = ggate.td[5].y;
}
// xoa dot ran cuoi cung khi ran vao cong
void deletelastpart()
{
	if (ggate.direction == UP)
	{
		gotoXY(ggate.td[5].x, ggate.td[5].y - 1);
		cout << " ";
	}
	if (ggate.direction == DOWN)
	{
		gotoXY(ggate.td[5].x, ggate.td[5].y + 1);
		cout << " ";
	}
	if (ggate.direction == LEFT)
	{
		gotoXY(ggate.td[5].x - 1, ggate.td[5].y);
		cout << " ";
	}
	if (ggate.direction == RIGHT)
	{
		gotoXY(ggate.td[5].x + 1, ggate.td[5].y);
		cout << " ";
	}
}

bool checkwingame()
{
	// neu co win game la true thi in logo va tra ve true
	if (flagwingame)
	{
		logo_win();
		clearscreen();
		Sleep(1500);
		return true;
	}
	return false;
}
// xu ly toc do ran. Qua man toc do giam 15 ms
void speed()
{
	Sleep(110 - (challenge - 1) * 15);
}
// Nhan phim trong menu
Menu key(int z)
{
	if (z == 224)
	{
		char key;
		key = _getch();
		if (key == KEY_UP) return U;
		if (key == KEY_DOWN) return D;
	}
	else if (z == 13) return ENTER;
}
int menucontrol(str line[4])
{
	printlogo();
	printmenu();
	int selection = 0;
	int* color = new int[3];
	for (int i = 0; i < 3; i++) color[i] = 240;
	color[0] = 244;
	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			setTextColor(color[i]);
			gotoXY(45, 10 + 2 * i);
			cout << line[i];
		}
		int z = _getch();
		Menu choice = key(z);
		switch (choice)
		{
		case U:
		{
			if (selection == 0) selection = 2;
			else selection--;
			break;
		}
		case D:
		{
			if (selection == 2) selection = 0;
			else selection++;
			break;
		}
		case ENTER: return selection;
		}
		for (int i = 0; i < 3; i++) color[i] = 240;
		color[selection] = 244;
	}
}
// luu game
void save_game() {

	// cho nguoi dung nhap ten file neu dong y luu game
	char tenfile[21] = ".txt";
	if (khung_yesno("  BAN CO MUON LUU GAME ?")) {
		ve_khung();
		while (1) {
			if (_kbhit()) {
				char key = _getch();
				if (key == KEY_ENTER)
					break;
				else if (key == KEY_BACKSPACE) {
					if (strlen(tenfile) > 4) {
						memmove(tenfile + strlen(tenfile) - 5, tenfile + strlen(tenfile) - 4, 4);
						tenfile[strlen(tenfile) - 1] = '\0';
					}
				}
				else {
					if (strlen(tenfile) < 20) {
						memmove(tenfile + strlen(tenfile) - 3, tenfile + strlen(tenfile) - 4, 4);
						tenfile[strlen(tenfile) - 5] = key;
					}
				}
			}
			gotoXY(36, 13);
			cout << tenfile << " ";
		}
		xoa_khung();

		// xuat file luu gia tri cac bien hien co
		fstream g("resume.txt", ios::in | ios::out);
		int dem;
		g >> dem;
		dem++;
		g.clear();
		g.seekp(0, ios::end);
		g << endl << tenfile;
		g.seekp(0, ios::beg);
		g << dem;
		g.close();

		ofstream fo(tenfile);
		fo << snake.length << endl;
		for (int i = 0; i < snake.length; i++) fo << snake.dot[i] << endl;
		fo << snake.dr << endl;
		fo << food << endl;
		fo << mark << endl;
		fo << challenge << endl;
		for (int i = 0; i < 6; i++) fo << ggate.td[i] << endl;
		fo << ggate.direction << endl;
		fo << flagdrawgatein << endl;
		fo << flagdrawgateout << endl;
		fo << flagreturnmenu << endl;
		fo << flagwingame << endl;
		fo.close();
	}
}
// ve menu load game
bool DrawLoadMenu() {

	printlogo();
	setTextColor(240);
	gotoXY( 37, 11);
	cout << "Press 'ESC' to return to Menu";

	// vẽ khung nhỏ có hiệu ứng
	int x = 30;
	int y = 10;
	setTextColor(244);
	while (y < 25)
	{
		gotoXY(30, y);
		putchar(219);
		gotoXY(75, y);
		putchar(219);
		Sleep(15);
		y++;
	}
	while (x <= 75)
	{
		gotoXY(x, 9);
		putchar(220);
		gotoXY(2 * 30 + 45 - x, 25);
		putchar(223);
		Sleep(15);
		x++;
	}

	//  in cac tenfile da luu truoc do

	char tenfile[21];
	int dem;
	ifstream g1("resume.txt");
	g1 >> dem;
	string* file = new string[dem];
	for (int i = 0; i < dem; i++) g1 >> file[i];

	int selection = 0;
	int start = 0;
	int end;
	if (dem < 10) end = dem - 1;
	else end = 9;

	while (true) {
		int dong = 13;
		for (int i = start; i <= end; i++) {
			gotoXY(40, dong++);
			if (i == selection)
				setTextColor(244);
			else
				setTextColor(240);
			cout << file[i] << "           ";
		}
		if (_kbhit()) {
			char key = _getch();
			if (key == KEY_UP) {
				if (selection == start && start > 0) {
					selection--;
					start--;
					end--;
				}
				else if (selection != 0)
					selection--;
			}
			else if (key == KEY_DOWN) {
				if (selection == end && end < dem - 1) {
					selection++;
					start++;
					end++;
				}
				else if (selection != dem - 1)
					selection++;
			}
			else if (key == KEY_ENTER)
				break;
			else if (key == KEY_ESC) {
				delete[] file;
				return false;
			}
		}
	}
	// doc file da luu truoc do 

	ifstream g(file[selection]);
	g >> snake.length;
	snake.dot = new coordinate[snake.length];
	for (int i = 0; i < snake.length; i++) g >> snake.dot[i];
	g >> snake.dr;
	g >> food;
	g >> mark;
	g >> challenge;
	for (int i = 0; i < 6; i++) g >> ggate.td[i];
	g >> ggate.direction;
	g >> flagdrawgatein;
	g >> flagdrawgateout;
	g >> flagreturnmenu;
	g >> flagwingame;

	delete[] file;
	return true;
}
