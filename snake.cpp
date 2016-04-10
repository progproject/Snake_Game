#include "graphics.h"
#include <iostream>
#include <fstream>
#include <time.h>

#define KEY_ESC   27

using namespace std;

/*STRUCTURES*/
struct snakeBody {

	int snake[2][100];
	int erase_snake[2][100];
	int length;
	int height;
	int radius;
	char dir;
	char c;

};

struct food {

	int x,y;
	int radius;
	int color;

};

/*GLOBAL VARIABLE*/
food f;
snakeBody s;
bool snake_erase = false;

/*FUNCTION DECLARATION*/
void menu( );
void menuPause( );
void initFood( );
void drawFood( );
void initSnake( );
void drawSnake( );
void moveSnake( );
void eraseSnake( );
void colDet( );

void gameEngine( )
{   

	initFood( );
	initSnake( );

	//while( true )
	{
		drawFood( );
		moveSnake( );
		colDet( );
	}

}

/*FUCTIONS START*/
int main ( )
{

	s.dir = '\0';

	initwindow(600, 600, "Snake Game");

	menu( );

	while (!kbhit( ))
	{
		delay( 200 );
	}


	return 0;

}//end main

void menu( )
{

	cleardevice();

	char choice = 0;

	//border
	setcolor( 8 );
	rectangle(5,5,595,595);

	//heading
	setcolor( 3 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 20, "Welcome To Snake Game" );
	//Menu
	setcolor( 2 );
	settextjustify( 1, 1 );
	settextstyle( 4, HORIZ_DIR, 1 );
	outtextxy( 295, 250, "Press 1 to Play Game" );
	outtextxy( 300, 280, "Press 2 for High Score" );
	outtextxy( 280, 310, "Press 3 for Settings" );
	outtextxy( 280, 360, "Press E to Exit" );


	choice = getch();
	cleardevice();


	switch(choice)
	{
	case '1':
		{
			gameEngine( );
			/*initSnake();
			initFood();

			while(1)
			{
			moveSnake();
			}*/

			break;
		}
	case '2':
		{
			//getHighScores();

			break;
		}
	case '3':
		{
			//settings();
			break;
		}
	case 'e' : case 'E':
		{
			exit(0);
		}
	default:
		{
			menu( );
		}
	}

}//end menu

void menuPause( )
{

	cleardevice( );

	//heading
	setcolor( 3 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 20, "Snake Game" );
	//Pause
	setcolor( 4 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 200, "GAME PAUSE" );
	//Menu
	setcolor( 6 );
	settextjustify( 1, 1 );
	settextstyle( 4, HORIZ_DIR, 1 );
	outtextxy( 295, 255, "Press C to Continue" );
	outtextxy( 290, 290, "Press E for Main menu" );

	char choice = '\0';
	choice = getch();

	cleardevice();

	switch(choice)
	{
	case 'c' : case 'C':
		{

			s.dir = s.c;
			moveSnake( );

			break;
		}
	case 'e': case 'E':
		{
			menu();

			break;
		}
	default:
		{
			menuPause( );
		}
	}

}

void initSnake( )
{

	s.length = 10; //initial length of snake
	s.height  = 10;  //initial thickness of snake
	s.radius = 5;

	for(int i = 0; i  < 2; i++)
	{

		int temp = 310;

		for(int j = s.length - 1; j >= 0; j--)
		{
			if(i == 0)
			{
				s.snake[i][j] = temp -= s.height;
			}
			else
				s.snake[i][j] = temp;
		}
	}

	for(int i = 0; i  < 2; i++)
	{
		for(int j = 0; j < s.length; j++ )
		{

			cout << s.snake[i][j] << " ";

		}
		cout << endl;
	}

}//end initSnake

void drawSnake( )
{

	//cleardevice( );

	drawFood( );

	//green
	setcolor( 2 );
	setfillstyle(8, 10);

	for(int i = s.length - 1; i >= 0 ; i--)
	{
		circle(s.snake[0][i], s.snake[1][i],s.radius);
		floodfill(s.snake[0][i]+1, s.snake[1][i]+1,2);
	}

	eraseSnake( );
	colDet( );

	delay( 300 );

}//end drawSnake;

void eraseSnake( )
{

	//Remove Snake
	setcolor( BLACK );
	setfillstyle(8, BLACK);
	for(int i = 0; i < s.length; i++)
	{
		fillellipse(s.snake[0][0], s.snake[1][0],s.radius,s.radius);
	}

	if( snake_erase != false )
	{

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < s.length ; j++)
			{
				s.erase_snake[i][j] = s.snake[i][j]; 
			}
		}

		for(int i = 1; i < s.length; i++)
		{
			fillellipse(s.erase_snake[0][i], s.erase_snake[1][i],s.radius,s.radius);
		}

		snake_erase = false;
	}

}

void moveSnake( )
{

	//default direction
	while( !kbhit() )
	{

		if(s.dir == KEY_UP)
		{

			s.snake[1][s.length - 1] -= s.height;

			drawSnake( );

			//All values on x-axis should be equal to head
			//and shifting values from head to tail on y-axis
			for( int i = 0; i < s.length - 1; i++)
			{
				s.snake[0][i] = s.snake[0][s.length - 1];
				s.snake[1][i] = s.snake[1][i + 1];
			}

		} else if(s.dir == KEY_DOWN) {

			s.snake[1][s.length - 1] += s.height;

			drawSnake( );

			//All values on x-axis should be equal to head
			//and shifting values from head to tail on y-axis
			for( int i = 0; i < s.length - 1; i++)
			{
				s.snake[0][i] = s.snake[0][s.length - 1];
				s.snake[1][i] = s.snake[1][i + 1];
			}

		} else if(s.dir == KEY_LEFT) {

			s.snake[0][s.length - 1] -= s.height;

			drawSnake( );

			//All values on y-axis should be equal to head
			//and shifting values from head to tail on x-axis
			for( int i = 0; i < s.length - 1; i++)
			{
				s.snake[1][i] = s.snake[1][s.length - 1];
				s.snake[0][i] = s.snake[0][i+1];
			}

		} else if(s.dir == KEY_RIGHT) {

			s.snake[0][s.length - 1] += s.height;

			drawSnake( );

			//All values on y-axis should be equal to head
			//and shifting values from head to tail on x-axis
			for( int i = 0; i < s.length - 1; i++)
			{
				s.snake[1][i] = s.snake[1][s.length - 1];
				s.snake[0][i] = s.snake[0][i+1];
			}

		} else {

			for( int i = 0; i < s.length; i++)
			{
				s.snake[0][i] += s.height;
			}

			drawSnake( );

		}
	}

	//Ater getting direction function
	//will be called again
	while( kbhit() )
	{
		s.c = s.dir;
		s.dir = getch();

		if( s.dir == KEY_ESC)
		{
			menuPause( );
		} else if( s.dir == 'q' || s.dir == 'Q' ) {
			menu( );
		} else {
			snake_erase = true;
			moveSnake( );
		}

	}

}//end snakeDir

void initFood( )
{

	srand(time (NULL) );
	f.x = rand()%500+20;
	f.y = rand()%500+20;
	f.radius = 5;
	f.color = 4;

}

void drawFood( )
{

	setfillstyle(4, f.color);
	setcolor(RED);
	circle(f.x,f.y,f.radius);
	floodfill(f.x + 1,f.y + 1,f.color);

}

void colDet( )
{

	/*if( RED == getpixel(s.snake[0][s.length -1],s.snake[1][s.length -1] ) )
	{
	cleardevice();
	setcolor( 4 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 300, 200, "GAME OVER");
	}*/

	if(s.snake[0][s.length -1] == (f.x + f.radius) && s.snake[1][s.length -1] == (f.y + f.radius))
	{

		cleardevice( );
		setcolor( 4 );
		settextjustify( 1, 2 );
		settextstyle( 10, HORIZ_DIR, 4 );
		outtextxy( 300, 200, "GAME OVER");

	}

}