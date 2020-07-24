//homework of school
//a checker game
//code written by Liu Yuming
//UI made by Lu Zihao
//
//
//V1.1 2020.7.24


#include<iostream>
#include<easyx.h>
#include <conio.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"Winmm.lib")

using namespace std;


//different colors of the chess pieces
enum color {
	BOUNDARY_OUT = 7, EMPTY_LOCAL = 0, RED_LOCAL = 1, YELLOW_LOCAL = 2,
	BLUE_LOCAL = 3, BROWN_LOCAL = 4, BLACK_LOCAL = 5, WHITE_LOCAL = 6
};

struct pixel
{
	int x;
	int y;
};

IMAGE mainbkimg, gamebkimg, gameoverbkimg, red, yellow, blue, brown, black, white, highlight;

//chessboard
class chessboard
{
private:
	color board[17][25] = { BOUNDARY_OUT };
	int step[6] = { 0 };
	int turn = 0;
	int mode = 0;
public:
	void chessboard_set(int mode_input);
	void two_players_mode_set();
	void three_players_mode_set();
	void six_players_mode_set();
	bool game_over();
	bool two_players_game_over();
	bool three_players_game_over();
	bool six_players_game_over();
	void print_board();
	color what_is_here(int cordx, int cordy);
	void update_the_board(int from_cordx, int from_cordy, int to_cordx, int to_cordy);
	void count_step(int player);
	void print_step();
	int how_many_steps(int player);
	int whos_turn(bool if_add, bool if_mi);
};


//functions of the class chessboard


//public function of class chessboard
//judge if a two-player game is over
//input: none
//output: a bool ,with true being over, false being not over
bool chessboard::two_players_game_over()
{
	int blue = 0;
	int white = 0;
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[i][12 - i + j] == RED_LOCAL)
			{
				blue++;
			}
			if (board[16 - i][12 - i + j] == YELLOW_LOCAL)
			{
				white++;
			}
		}
	}
	return blue == 10 || white == 10;
}


//public function of class chessboard
//judge if a three-player game is over
//input: none
//output: a bool ,with true being over, false being not over
bool chessboard::three_players_game_over()
{
	int white = 0;
	int brown = 0;
	int yellow = 0;
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[16 - i][12 - i + j] == BLUE_LOCAL)
			{
				white++;
			}

		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[7 - i][3 - i + j] == YELLOW_LOCAL)
			{
				brown++;
			}
			if (board[7 - i][21 - i + j] == RED_LOCAL)
			{
				yellow++;
			}
		}
	}
	return white == 10 || brown == 10 || yellow == 10;
}


//public function of calss chessboard
//judge if a six-player game is over
//input: none
//output: a bool ,with true being over, false being not over
bool chessboard::six_players_game_over()
{
	int white = 0;
	int brown = 0;
	int yellow = 0;
	int blue = 0;
	int red = 0;
	int black = 0;
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[i][12 - i + j] == BLUE_LOCAL)
			{
				blue++;
			}
			if (board[16 - i][12 - i + j] == WHITE_LOCAL)
			{
				white++;
			}
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[7 - i][3 - i + j] == BROWN_LOCAL)
			{
				brown++;
			}
			if (board[7 - i][21 - i + j] == YELLOW_LOCAL)
			{
				yellow++;
			}
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			if (board[9 + i][3 - i + j] == BLACK_LOCAL)
			{
				black++;
			}
			if (board[9 + i][21 - i + j] == RED_LOCAL)
			{
				red++;
			}
		}
	}
	return red == 10 || yellow == 10 || blue == 10 || brown == 10 || black == 10 || white == 10;
}


//public function of class chessboard
//judge if a game is over
//input: mode 1234 for 1236 players
//output: a bool ,with true being over, false being not over
bool chessboard::game_over()
{
	switch (mode)
	{
	case 1:
	case 2:
		return two_players_game_over();
		break;
	case 3:
		return three_players_game_over();
		break;
	case 6:
		return six_players_game_over();
		break;
	}
}


//public function of class chessboard
//set the chessboard to two players mode
//input: none
//output: none
void chessboard::two_players_mode_set()
{
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[i][12 - i + j] = YELLOW_LOCAL;
			board[16 - i][12 - i + j] = RED_LOCAL;
		}
	}
}


//public function of class chessboard
//set the chessboard to three player mode
//input: none
//output: none
void chessboard::three_players_mode_set()
{
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[i][12 - i + j] = BLUE_LOCAL;
			board[16 - i][12 - i + j] = EMPTY_LOCAL;
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[7 - i][3 - i + j] = EMPTY_LOCAL;
			board[7 - i][21 - i + j] = EMPTY_LOCAL;
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[9 + i][3 - i + j] = RED_LOCAL;
			board[9 + i][21 - i + j] = YELLOW_LOCAL;
		}
	}
}


//public function of class chessboard
//set the chessboard for six players mode
//input: none
//ouput: none
void chessboard::six_players_mode_set()
{
	int i, j;
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[i][12 - i + j] = WHITE_LOCAL;
			board[16 - i][12 - i + j] = BLUE_LOCAL;
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[7 - i][3 - i + j] = RED_LOCAL;
			board[7 - i][21 - i + j] = BLACK_LOCAL;
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 2 * i; j = j + 2)
		{
			board[9 + i][3 - i + j] = YELLOW_LOCAL;
			board[9 + i][21 - i + j] = BROWN_LOCAL;
		}
	}
}


//public function of class chessboard
//intialize the chessboard based on the given mode
//1234 for 1236players
//input: mode {1-4}
//output: none
void chessboard::chessboard_set(int mode_input)
{
	int i, j, n;
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 25; j++)
		{
			board[i][j] = BOUNDARY_OUT;
		}
	}
	switch (mode_input)
	{
	case 1:
		cout << "This function is still under construction!";
	case 2:
		two_players_mode_set();
		break;
	case 3:
		three_players_mode_set();
		break;
	case 6:
		six_players_mode_set();
		break;
	}
	for (i = 0; i <= 4; i++)
	{
		for (j = 0; j <= 8 + 2 * i; j = j + 2)
		{
			board[4 + i][8 - i + j] = EMPTY_LOCAL;
		}
	}
	for (i = 0; i <= 3; i++)
	{
		for (j = 0; j <= 8 + 2 * i; j = j + 2)
		{
			board[12 - i][8 - i + j] = EMPTY_LOCAL;
		}
	}
	//initialize the steps
	for (n = 0; n < 6; n++)
	{
		step[n] = 0;
	}
	turn = 1;
	mode = mode_input;
}


//public function of class chessboard
//print the board
void chessboard::print_board()
{
	int i, j;
	for (i = 16; i >= 0; i--)
	{
		for (j = 0; j <= 24; j++)
		{
			if (board[i][j] == 7)   //if it's BOUDARY_OUT, print a space to get better look
			{
				cout << "  ";
			}
			else
			{
				cout << board[i][j] << ' ';
			}
		}
		cout << "\n";
	}
}


//public function of class chessboard
//check how the given position is colored
//input: the cord of a position
//output: the color of the position, typed enum color
color chessboard::what_is_here(int cordx, int cordy)
{
	if (cordx < 0 || cordy < 0)
	{
		cordx = 0;
		cordy = 0;
	}
	return board[cordy][cordx];
}


//public function of the class chessboard
//input: the start coordinate and the target coordinate
void chessboard::update_the_board(int from_cordx, int from_cordy, int to_cordx, int to_cordy)
{
	color temp;
	temp = board[from_cordy][from_cordx];
	board[from_cordy][from_cordx] = board[to_cordy][to_cordx];
	board[to_cordy][to_cordx] = temp;
}


//public function of class chessboard
//respectively count the players steps
//input: the from cordx and from cordy
//no output
void chessboard::count_step(int player)
{
	step[player - 1]++;
}


//public function of class chessboard
//print the steps for every players so far
//no input or output
void chessboard::print_step()
{
	int n;
	cout << "The steps of the players are:(player, steps)\n";
	for (n = 0; n < 6; n++)
	{
		cout << "(" << n + 1 << " , " << step[n] << ")";
	}
	cout << "\n";
}


//public function of calss chessboard
//get the player to play the game
//input:bool to tell the function whether it should switch turns
//output: the turn matched by number of piece
int chessboard::whos_turn(bool if_add, bool if_mi)
{
	if (if_mi)
	{
		if (if_add == true)
		{
			turn++;
			if (turn > mode)
			{
				turn -= mode;
			}
		}
	}
	else
	{
		turn += mode - 1;
		if (turn > mode)
		{
			turn -= mode;
		}
	}
	return turn;
}

int chessboard::how_many_steps(int player)
{
	return step[player];
}

//end of functions of the class chessboard
//functions to generate the game


//check the neaby space in the chessboard and find whether is empty
//input: coordinate of x, coordinate of y(both are int) and the substantialized chessboard
//output: 1-dimension int array. The fisrt number record the number of valid pair(s) of coodinates
//        the following oddth elements are the x of a possible coordinate, and the next element to be the y
//        all the available coordinates are in the front of the array, with -1 in behind
int* check_move_near(int cordx, int cordy, chessboard chessboard_real)
{
	int* potential_cord = new int[13];
	int i, j;
	int n = 1;
	int count = 0;
	int temp1, temp2;
	potential_cord[0] = 0;
	//set values for the nearby places
	for (i = -2; i <= 2; i++)
	{
		if (i == 0)
		{
			;
		}
		else
		{
			for (j = -1; j <= 1; j++)
			{
				if (abs(i + j) == 2 || i + j == 0)
				{
					potential_cord[n] = cordx + i;
					potential_cord[n + 1] = cordy + j;
					n += 2;
				}
			}
		}
	}
	//check if the places are available
	for (n = 1; n < 12; n = n + 2)
	{
		if (chessboard_real.what_is_here(potential_cord[n], potential_cord[n + 1]) != EMPTY_LOCAL)
		{
			potential_cord[n] = -1;
			potential_cord[n + 1] = -1;
		}
	}
	//count the available place(s)
	for (n = 1; n < 12; n = n + 2)
	{
		if (potential_cord[n] != -1)
		{
			count++;
		}
	}
	potential_cord[0] = count;
	//put them(it) into order
	for (i = 1; i < 12; i = i + 2)
	{
		if (potential_cord[i] == -1)
		{
			for (j = i + 2; j < 12; j = j + 2)
			{
				if (potential_cord[j] != -1)
				{
					temp1 = potential_cord[i];
					temp2 = potential_cord[i + 1];
					potential_cord[i] = potential_cord[j];
					potential_cord[i + 1] = potential_cord[j + 1];
					potential_cord[j] = temp1;
					potential_cord[j + 1] = temp2;
				}
			}
		}
	}
	return potential_cord;
}


//checked whether the given cord is checked beford, used in the function move_jumo_inner
//input: cordx, cordy, checked_cord
//output: bool, if checked return true, if unchecked return false
bool check_whether_in(int cordx, int cordy, int* range_array)
{
	int n;
	for (n = 0; n < 160; n = n + 2)
	{
		if (range_array[n] == cordx && range_array[n + 1] == cordy)
		{
			return true;
		}
	}
	return false;
}



//check the only the subneaby spaces in the chessboard find whether the move conform to the rules
//input: coordinate of x, coordinate of y(both are int) and the substantialized chessboard, the arry of known valid coordinates
//output: nothing(directly modify the array)
void check_move_jump_inner(int cordx, int cordy, chessboard chessboard_real, int* valid_cord, int* checked_cord)
{
	int* potential_cord = new int[13]();
	int i, j;
	int n = 1;
	//set values for the nearby places
	for (i = -2; i <= 2; i++)
	{
		if (i == 0)
		{
			;
		}
		else
		{
			for (j = -1; j <= 1; j++)
			{
				if (abs(i + j) == 2 || i + j == 0)
				{
					potential_cord[n] = cordx + i;
					potential_cord[n + 1] = cordy + j;
					n += 2;
				}
			}
		}
	}
	//check if the places are available
	for (n = 1; n < 12; n = n + 2)
	{
		if (chessboard_real.what_is_here(potential_cord[n], potential_cord[n + 1]) == EMPTY_LOCAL ||
			chessboard_real.what_is_here(potential_cord[n], potential_cord[n + 1]) == BOUNDARY_OUT)
		{
			potential_cord[n] = -1;
			potential_cord[n + 1] = -1;
		}
	}
	//extend the range and check whether the extended range are available
	for (n = 1; n < 12; n = n + 2)
	{
		if (potential_cord[n] != -1)
		{
			potential_cord[n] += potential_cord[n] - cordx;
			potential_cord[n + 1] += potential_cord[n + 1] - cordy;
			if (chessboard_real.what_is_here(potential_cord[n], potential_cord[n + 1]) != EMPTY_LOCAL ||
				chessboard_real.what_is_here(potential_cord[n], potential_cord[n + 1]) == BOUNDARY_OUT)
			{
				potential_cord[n] = -1;
				potential_cord[n + 1] = -1;
			}
		}
	}
	//find the valid coordinates, record them in the checked_cord, and recursively fing the next ones
	for (n = 1; n < 12; n = n + 2)
	{
		if (potential_cord[n] != -1 && !check_whether_in(potential_cord[n], potential_cord[n + 1], checked_cord)) //meaning unchecked and valid
		{
			for (i = 1; i < 160; i = i + 2)
			{
				if (valid_cord[i] == 0)
				{
					valid_cord[i] = potential_cord[n];
					valid_cord[i + 1] = potential_cord[n + 1];
					break;
				}
			}
			for (i = 0; i < 160; i = i + 2)
			{
				if (checked_cord[i] == 0)
				{
					checked_cord[i] = potential_cord[n];
					checked_cord[i + 1] = potential_cord[n + 1];
					break;
				}
			}
			check_move_jump_inner(potential_cord[n], potential_cord[n + 1], chessboard_real, valid_cord, checked_cord);
		}
	}
	delete[] potential_cord;
}


//using the function check_move_jump_inner to recrusively find the valid spaces
//input: coordinate of x, coordinate of y(both are int) and the substantialized chessboard
//output: 1-dimension int array. The fisrt number record the number of valid pair(s) of coodinates
//        the following oddth elements are the x of a possible coordinate, and the next element to be the y
//        all the available coordinates are in the front of the array, with -1 in behind
int* check_move_jump(int cordx, int cordy, chessboard chessboard_real)
{
	int* valid_cord = new int[81]();  //initialize all elements to be zeros
	int* checked_cord = new int[160]();  //initialize all elements to be zeros
	int n;
	int count = 0;
	check_move_jump_inner(cordx, cordy, chessboard_real, valid_cord, checked_cord);
	delete[] checked_cord;
	for (n = 1; n < 81; n = n + 2)
	{
		if (valid_cord[n] != 0 || valid_cord[n + 1] != 0)
		{
			count++;
		}
	}
	valid_cord[0] = count;
	return valid_cord;
}


//use the function check_move_near and check_move_jumo to give all the possible coordinates
//input: cordx, cordy, and the chessboard
//ouput: an 1-dimension arrsy, with first element to be the numbers of possible position
//       oddth elements are the xs, eventh elements are the ys
int* check_possible_move(int cordx, int cordy, chessboard chessboard_real)
{
	int* valid_cord = new int[93]();
	int* valid_cord_near; //should be 13 elements
	int* valid_cord_jump; //should be 81 elements
	int n;
	valid_cord_near = check_move_near(cordx, cordy, chessboard_real);
	valid_cord_jump = check_move_jump(cordx, cordy, chessboard_real);
	for (n = 1; n <= 2 * valid_cord_near[0]; n++)
	{
		valid_cord[n] = valid_cord_near[n];
	}
	for (; n <= 2 * valid_cord_jump[0] + 2 * valid_cord_near[0]; n++)
	{
		valid_cord[n] = valid_cord_jump[n - 2 * valid_cord_near[0]];
	}
	valid_cord[0] = valid_cord_jump[0] + valid_cord_near[0];
	delete[] valid_cord_near;
	delete[] valid_cord_jump;
	return valid_cord;
}


//check if the given move intention is possible
//including checking if from empty or boudout position, if the move conform to the rules, if the to position is boundout
//input: from coordinate, to coordinate, chessboard and the valid_cord
bool check_move(int from_cordx, int from_cordy, int to_cordx, int to_cordy, chessboard chessboard_real, int* valid_cord)
{
	int n;
	if (chessboard_real.what_is_here(from_cordx, from_cordy) == EMPTY_LOCAL ||
		chessboard_real.what_is_here(from_cordx, from_cordy) == BOUNDARY_OUT)
	{
		return false;
	}
	if (chessboard_real.what_is_here(to_cordx, to_cordy) == BOUNDARY_OUT)
	{
		return false;
	}
	for (n = 1; n < 2 * valid_cord[0]; n = n + 2)
	{
		if (valid_cord[n] == to_cordx && valid_cord[n + 1] == to_cordy)
		{
			return true;
		}
	}
	return false;
}

//end of functions to generate the game
//begin of functions to generate the gui

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
// 透明贴图函数
// 参数：
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void initmainimg()//初始化主界面与设定坐标系函数
{
	initgraph(660, 660);
	setorigin(330, 330);
	setaspectratio(1, -1);
	loadimage(&mainbkimg, _T("./res/mainbkimg .png"));
	loadimage(&gameoverbkimg, _T("./res/gameoverbkimg.png"));
}

void initgameimg() //初始化游戏资源
{
	loadimage(&gamebkimg, _T("./res/Board_Wodden.png"));
	loadimage(&red, _T("./res/Piece_A.PNG"));
	loadimage(&yellow, _T("./res/Piece_B.PNG"));
	loadimage(&blue, _T("./res/Piece_C.PNG"));
	loadimage(&brown, _T("./res/Piece_D.PNG"));
	loadimage(&black, _T("./res/Piece_E.PNG"));
	loadimage(&white, _T("./res/Piece_F.PNG"));
	loadimage(&highlight, _T("./res/Piece_Transparant.PNG"));
	mciSendString(_T("open ./res/bgm.wav type MPEGVideo"), NULL, 0, NULL);//载入bgm文件
	mciSendString(_T("open ./res/win.wav type MPEGVideo"), NULL, 0, NULL);//载入胜利音乐文件
}

int selectmode()//选择模式函数，返回1 人机对弈，2 二人对战，3 三人对战，4 六人对战
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton == true)
		{
			if (m.x > 180 && m.x < 480 && m.y>250 && m.y < 330)
				return 1;
			else if (m.x > 180 && m.x < 480 && m.y>350 && m.y < 430)
				return 2;
			else if (m.x > 180 && m.x < 480 && m.y>450 && m.y < 530)
				return 3;
			else if (m.x > 180 && m.x < 480 && m.y>550 && m.y < 630)
				return 6;
		}
	}
}

void whosturn(chessboard chessboard_real)//根据当前是哪位玩家执棋，在屏幕的右上角打印出对应的棋子图像
{
	int x = 230, y = 245;
	switch (chessboard_real.whos_turn(false, true))
	{
	case 1:
		transparentimage(NULL, x, y, &red, BLACK);
		break;
	case 2:
		transparentimage(NULL, x, y, &yellow, BLACK);
		break;
	case 3:
		transparentimage(NULL, x, y, &blue, BLACK);
		break;
	case 4:
		transparentimage(NULL, x, y, &brown, BLACK);
		break;
	case 5:
		transparentimage(NULL, x, y, &black, BLACK);
		break;
	case 6:
		transparentimage(NULL, x, y, &white, BLACK);
		break;
	}
}

pixel loc_to_pix(int i, int j)//二维数组坐标转换为像素坐标
{
	pixel pix;
	pix.y = (int)((j - 8) * 38.5);
	pix.x = (int)((i - 12) * 22);
	return pix;
}

void loadchessimg(chessboard chessboard_real)//根据二维数组信息，加载棋子图像和棋盘图像
{
	int i, j;
	BeginBatchDraw();
	putimage(-330, -330, &gamebkimg);
	whosturn(chessboard_real);
	for (i = 0; i <= 24; i++)
	{
		for (j = 0; j <= 16; j++)
		{
			switch (chessboard_real.what_is_here(i, j))
			{
			case 1:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &red, BLACK);
				break;
			case 2:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &yellow, BLACK);
				break;
			case 3:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &blue, BLACK);
				break;
			case 4:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &brown, BLACK);
				break;
			case 5:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &black, BLACK);
				break;
			case 6:
				transparentimage(NULL, loc_to_pix(i, j).x - 19, loc_to_pix(i, j).y - 19, &white, BLACK);
				break;
			case 7:
				break;
			case 0:
				break;
			}
		}
	}
	EndBatchDraw();
}

pixel click(chessboard chessboard_real, MOUSEMSG m)//判断第一次点击时，光标在哪个棋子上，返回棋子的坐标
{
	pixel loc;
	int i, j, x, y, chess_x, chess_y;
	x = m.x - 330;
	y = 330 - m.y;
	for (j = 0; j <= 16; j++)
	{
		for (i = 0; i <= 24; i++)
		{
			chess_x = loc_to_pix(i, j).x;//用于避免函数反复引用
			chess_y = loc_to_pix(i, j).y;
			if (x >= chess_x - 19 && x <= chess_x + 19 && y >= chess_y - 19 && y <= chess_y + 19//判断光标在哪个空格上
				&& chessboard_real.whos_turn(false, true) == chessboard_real.what_is_here(i, j))//判断点击的棋子是不是当前执棋玩家的棋子
			{
				loc.x = i;
				loc.y = j;
				return loc;
			}

		}
	}
	loc.x = -1;
	loc.y = -1;
	return loc;
}

pixel click_2(chessboard chessboard_real, int* p, MOUSEMSG m)//判断第二次点击时，光标在哪个可移动的空格上，返回可移动到空格的坐标
{
	pixel loc;
	int i, j, x, y, k, box_x, box_y, flag = 0;
	x = m.x - 330;
	y = 330 - m.y;
	for (j = 0; j <= 16; j++)
	{
		for (i = 0; i <= 24; i++)
		{
			for (k = 0; k < p[0] * 2; k = k + 2)
			{
				if (p[k + 1] == i && p[k + 2] == j)//判断当前i，j指代的空格，是不是棋子能移动到的空格
				{
					flag = 1;
					break;
				}
				else flag = 0;
			}
			box_x = loc_to_pix(i, j).x;
			box_y = loc_to_pix(i, j).y;
			if (x >= box_x - 19 && x <= box_x + 19 && y >= box_y - 19 && y <= box_y + 19//判断坐标在哪个空格上
				&& flag == 1)//判断该空格是不是能移动到的空格
			{
				loc.x = i;
				loc.y = j;
				return loc;
			}
		}
	}
	loc.x = -1;
	loc.y = -1;
	return loc;
}

void high_light(int* p)
{
	int i;
	for (i = 0; i < p[0] * 2; i = i + 2)
	{
		transparentimage(NULL, loc_to_pix(p[i + 1], p[i + 2]).x - 19, loc_to_pix(p[i + 1], p[i + 2]).y - 19, &highlight, BLACK);
	}
}

bool gameover(chessboard chessboard_real)//展示gameover界面，列出最终胜利者，并设置结束游戏与再来一局按钮。
{
	int x = -70, y = 5;
	putimage(-330, -330, &gameoverbkimg);
	mciSendString(_T("stop ./res/bgm.wav"), NULL, 0, NULL);//结束播放背景音乐
	Sleep(500);
	mciSendString(_T("play ./res/win.wav"), NULL, 0, NULL);//播放胜利音乐
	switch (chessboard_real.whos_turn(false, false))
	{
	case 1:
		transparentimage(NULL, x, y, &red, BLACK);
		break;
	case 2:
		transparentimage(NULL, x, y, &yellow, BLACK);
		break;
	case 3:
		transparentimage(NULL, x, y, &blue, BLACK);
		break;
	case 4:
		transparentimage(NULL, x, y, &brown, BLACK);
		break;
	case 5:
		transparentimage(NULL, x, y, &black, BLACK);
		break;
	case 6:
		transparentimage(NULL, x, y, &white, BLACK);
		break;
	}
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton == true)
		{
			if (m.x > 180 && m.x < 480 && m.y > 410 && m.y < 490)
				return true;
			else if (m.x > 180 && m.x < 480 && m.y > 510 && m.y < 590)
				return false;
		}
	}
}

//main funciton
//recurrently execute play_game to update the chessboard
int main()
{
	chessboard chessboard_real;
	int mode_input;
	bool continue_play = true;
	pixel from_cord, to_cord;
	int* p;
	MOUSEMSG m;
	initmainimg();//初始化背景图片
	initgameimg();//初始化游戏资源图片
	while (continue_play)
	{
		putimage(-330, -330, &mainbkimg);//加载背景图片
		mode_input = selectmode();//进入主界面，读取游玩哪个模式
		chessboard_real.chessboard_set(mode_input);
		mciSendString(_T("play ./res/bgm.wav repeat"), NULL, 0, NULL);//开始循环播放背景音乐
		while (!chessboard_real.game_over())//进入游戏界面
		{
		begin:loadchessimg(chessboard_real);
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				from_cord = click(chessboard_real, m);
				if (from_cord.x != -1)
				{
					p = check_possible_move(from_cord.x, from_cord.y, chessboard_real);
					high_light(p);
				}
				else goto begin;
				while (1)//使程序卡住，等待下一次的左键信息
				{
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN)
					{
						to_cord = click_2(chessboard_real, p, m);
						if (to_cord.x != -1)
						{
							chessboard_real.update_the_board(from_cord.x, from_cord.y, to_cord.x, to_cord.y);
							chessboard_real.count_step(chessboard_real.whos_turn(false, true));
							chessboard_real.whos_turn(true, true);
							break;
						}
						else goto begin;
					}
				}
			}
		}
		continue_play = gameover(chessboard_real);//进入游戏结束界面，并判断是否继续游戏。
	}
	return 0;
}