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

struct boundary
{
	
	int length;
	int width;
	int border;

};

struct obstacles
{
	int locX1;
	int locY1;
	int locX2;
	int locY2;
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
void snakeDir( );
void colDet( );
void drawBoundary( );
void drawObstacles( );
void eatFood( );

void draw ( )
{
	drawBoundary( );
	drawObstacles( );
	drawFood( );
	drawSnake( );
	eatFood( );
}

void gameEngine( )
{   

	initFood( );
	initSnake( );
	draw( );

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

			initSnake( );
			initFood( );
			drawBoundary( );
			drawObstacles( );

			while( true )
			{
				snakeDir( );
			}

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

	s.length = 5; //initial length of snake
	s.height  = 10;  //initial thickness of snake
	s.radius = 5;
	s.dir = '\0';

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

}//end initSnake

void drawSnake( )
{

	//green
	setcolor( 2 );
	setfillstyle(8, 10);

	for(int i = s.length - 1; i >= 0 ; i--)
	{
		circle(s.snake[0][i], s.snake[1][i],s.radius);
		floodfill(s.snake[0][i]+1, s.snake[1][i]+1,2);
	}

	delay( 300 );

	eraseSnake( );

}//end drawSnake;

void eraseSnake( )
{

	//Remove Snake
	setcolor( BLACK );
	setfillstyle(8, BLACK);

	if( snake_erase != false )
	{

		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < s.length ; j++)
			{
				s.erase_snake[i][j] = s.snake[i][j]; 
			}
		}

		for(int i = 0; i < s.length; i++)
		{
			fillellipse(s.erase_snake[0][i], s.erase_snake[1][i],s.radius,s.radius);
		}

		snake_erase = false;
	}

	for(int i = 0; i < s.length; i++)
	{
		fillellipse(s.snake[0][0], s.snake[1][0],s.radius,s.radius);
	}

}//end eraseSnake

void snakeDir( )
{
		if ( kbhit( ) )
		{
			s.dir = getch(); 

			if(s.dir == '\0')
			{
				s.dir = getch();

				snake_erase = true;
				moveSnake( );
				draw( );

			} else if ( s.dir == 'p' || s.dir == 'P' ) {

				menuPause( );
			
			} else if (  s.dir == 'q' || s.dir == 'Q' ) {

				menu( );

			}

		}

		while(!kbhit())
		{

			moveSnake( );
		    draw( );

		}

}//end snakeDir

void moveSnake( )
{

	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length - 1; j++ )
		{
			s.snake[i][j] = s.snake[i][j+1];
		}
	}

	if( s.dir == KEY_UP )
		s.snake[1][s.length - 1] -= s.height;
	else if( s.dir == KEY_DOWN )
		s.snake[1][s.length - 1] += s.height;
	else if( s.dir == KEY_LEFT )
		s.snake[0][s.length - 1] -= s.height;
	else if( s.dir == KEY_RIGHT )
		s.snake[0][s.length - 1] += s.height;
	else if ( s.dir == '\0' )
		s.snake[0][s.length - 1] += s.height;

}

void initFood( )
{

	srand(time (NULL) );
	f.x = rand()%500+20;
	f.y = rand()%500+20;
	f.radius = 8;
	f.color = 4;

	cout << "fx " << f.x <<endl;
	cout << "fy " << f.y <<endl;

	cout << "fx " << f.x + f.radius <<endl;
	cout << "fy " << f.y + f.radius <<endl;

}

void drawFood( )
{

	setfillstyle(4, f.color);
	setcolor(RED);
	circle(f.x,f.y,f.radius);
	floodfill(f.x + 1,f.y + 1,f.color);

}

void eatFood( )
{

	 if(s.snake[0][s.length - 1] == (f.x + f.radius) && s.snake[1][s.length -1] == (f.y + f.radius))
	{
		s.length++;


		s.snake[0][s.length-1] = s.snake[0][s.length-2];
		s.snake[1][s.length-1] = s.snake[0][s.length-2];

		cout << s.length;

		setcolor( BLACK );
	    setfillstyle(8, BLACK);
		fillellipse(f.x, f.y,f.radius,f.radius);

		initFood( );
		moveSnake( );
	}

}

void drawBoundary ( )
{

	boundary b;
	b.length = 600;
	b.width = 600;
	b.border = 20;

	setcolor(YELLOW);
	setfillstyle(7,YELLOW);

	bar(b.length-b.width,b.length-b.width,b.border,b.length);//left
	bar(b.length-b.width,b.length-b.width,b.length,b.border);//top
	bar(b.length-b.border,b.length-b.width,b.length,b.width);//right
	bar(b.length-b.width,b.length-b.border,b.length,b.width);//bottom

} //end boundary

void drawObstacles ( )

{
	obstacles o;
	
	setfillstyle(5,RED);
	bar(200,100,220,300);//1st Obstacle
	bar(300,400,500,420);//2nd Obstacle

}//endobstacles