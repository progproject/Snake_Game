#include "graphics.h"
#include <iostream>
#include <stdio.h>
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

struct boundary {
	
	int length;
	int width;
	int border;

};

struct player {

	char name[10];
	int score;
	int highscrore;
 
};

/*GLOBAL VARIABLE*/
food f;
snakeBody s;
boundary b;
player p;
bool snake_erase = false;

/*FUNCTION DECLARATION*/
void menu( );
void menuPause( );

/*BOARD*/
void drawBoundary( );    //draw boundry on board 
void drawObstacles( );   //draw obstacle on board

/*FOOD*/
void initFood( );        //food random positions
void drawFood( );        //draw food on board
void eatFood( );         //perform action when snake eat food

/*SNAKE*/
void initSnake( );       //initialize snakebody
void drawSnake( );       //draw snakebody on board
void moveSnake( );       //change values of snake head and tail according to direction
void eraseSnake( );      //to erase snake to avoid screen blink issue
void snakeDir( );        //take direction from user

/*Utilities*/
void colDet( );          //detect collision when hit with boundry or obstacle
void getPlayer( );       //get user name from player
void saveGame( );        //save game in pause menu;
void loadGame( );        //Load previous game

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

	getPlayer( );
	initSnake( );
	initFood( );
	drawBoundary( );
	drawObstacles( );

	while( true )
	{
		snakeDir( );
	}

}

/*FUCTIONS START*/
int main ( )
{

	s.dir = '\0';

	initwindow(800, 600, "Snake Game");

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
	rectangle(5,5,795,595);

	//heading
	setcolor( 3 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 400, 20, "Welcome To Snake Game" );
	//Menu
	setcolor( 2 );
	settextjustify( 1, 1 );
	settextstyle( 4, HORIZ_DIR, 1 );
	outtextxy( 395, 250, "Press 1 to Play Game" );
	outtextxy( 400, 280, "Press 2 for High Score" );
	outtextxy( 380, 360, "Press E to Exit" );


	choice = getch();
	cleardevice();


	switch(choice)
	{
	case '1':
		{

			cleardevice( );
			
			//heading
			setcolor( 1 );
			settextjustify( 1, 2 );
			settextstyle( 10, HORIZ_DIR, 4 );
			outtextxy( 400, 20, "Welcome To Snake Game" );
			//Menu
			setcolor( 1 );
			settextjustify( 1, 1 );
			settextstyle( 4, HORIZ_DIR, 1 );
			outtextxy( 395, 250, "Press 1 to Start New Game" );
			outtextxy( 400, 280, "Press 2 to Load Game" );

			char newchoice = '\0';
			newchoice = getch( );

			switch(newchoice)
			{
			case '1':
				{

					gameEngine( );

				}
			case '2':
				{

					drawBoundary( );
					drawObstacles( );
					loadGame( );
					snake_erase = false;

					while( true )
					{
						snakeDir( );
					}

				}
			default:
				{
					menu( );
				}

			}

			break;

		}
	case '2':
		{
			//getHighScores();

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
	outtextxy( 400, 20, "Snake Game" );
	//Pause
	setcolor( 4 );
	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 4 );
	outtextxy( 400, 200, "GAME PAUSE" );
	//Menu
	setcolor( 6 );
	settextjustify( 1, 1 );
	settextstyle( 4, HORIZ_DIR, 1 );
	outtextxy( 395, 265, "Press C to Continue" );
	outtextxy( 390, 310, "Press S to Save Game" );
	outtextxy( 390, 360, "Press E for Main menu" );

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
			menu( );

			break;
		}
	case 's': case 'S':
		{
			saveGame( );
			
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

	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length - 1; j++ )
		{
			cout << s.snake[i][j] << " ";
		}
		cout << endl;
	}

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
			
			s.c = s.dir; //save value to use after continue

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

	colDet( );

}//end moveSnake

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

}//end initFood

void drawFood( )
{

	setfillstyle(4, f.color);
	setcolor(RED);
	circle(f.x,f.y,f.radius);
	floodfill(f.x + 1,f.y + 1,f.color);

}//end drawFood

void eatFood( )
{

	if(s.snake[0][s.length - 1] == f.x && s.snake[1][s.length -1] == f.y )
	{
		s.length++;
		p.score++;

		s.snake[0][s.length-1] = s.snake[0][s.length-2];
		s.snake[1][s.length-1] = s.snake[0][s.length-2];

		cout << s.length;

		setcolor( BLACK );
	    setfillstyle(8, BLACK);
		fillellipse(f.x, f.y,f.radius,f.radius);

		initFood( );
		moveSnake( );
	}

}//end eatFood

void drawBoundary ( )
{

	char buffer[100] = {'\0'};

	b.length = 600;
	b.width = 600;
	b.border = 20;

	setcolor(YELLOW);
	setfillstyle(7,YELLOW);

	bar(b.length-b.width,b.length-b.width,b.border,b.length);//left
	bar(b.length-b.width,b.length-b.width,b.length,b.border);//top
	bar(b.length-b.border,b.length-b.width,b.length,b.width);//right
	bar(b.length-b.width,b.length-b.border,b.length,b.width);//bottom

	setcolor(YELLOW);
	setfillstyle(7,RED);
	bar(600,0,610,600);
	bar(600,0,800,10);
	bar(800,0,790,800);
	bar(600,590,800,600);

	setcolor( 13 );
	settextjustify( 1, 2 );
	settextstyle( 8, HORIZ_DIR, 3 );
	outtextxy(700,20,"SNAKE GAME");
	
	setcolor( 3 );
	settextjustify( 1, 2 );
	settextstyle( 8, HORIZ_DIR, 2 );
	outtextxy(700,250,p.name);
	settextstyle( 8, HORIZ_DIR, 1 );
	outtextxy(650,300,"Score :");
	outtextxy(700,301,itoa(p.score,buffer,10));

	setcolor( 13 );
	settextjustify( 1, 2 );
	settextstyle( 8, HORIZ_DIR, 1 );
	outtextxy(700,450,"P to pause");
	outtextxy(700,480,"Q to quite");

} //end boundary

void drawObstacles ( )

{
	
	setfillstyle(5,RED);
	bar(200,100,220,300);//1st Obstacle
	bar(300,400,500,420);//2nd Obstacle

}//endobstacles

void colDet( )
{
	//BoundryCollision
	if(s.snake[0][s.length - 1] == (b.border) || s.snake[1][s.length - 1] == (b.border) || s.snake[0][s.length - 1] == (b.width - b.border) || s.snake[1][s.length - 1] == (b.length - b.border))
	{
		
		delay( 300 );
		cleardevice( );
		
		setcolor( 4 );
		settextjustify( 1, 2 );
		settextstyle( 10, HORIZ_DIR, 5 );
		outtextxy( 300, 200, "GAME OVER" );

		delay( 500 );

		menu( );

	} 
	//Obstacle 1 Collision
	else if(s.snake[0][s.length - 1] >= 200 && s.snake[0][s.length - 1] <= 220 && s.snake[1][s.length - 1] >= 100 && s.snake[1][s.length - 1] <= 300 )
	{

		delay( 300 );
		cleardevice( );
		
		setcolor( 4 );
		settextjustify( 1, 2 );
		settextstyle( 10, HORIZ_DIR, 5 );
		outtextxy( 300, 200, "GAME OVER" );

		delay( 500 );

		menu( );

	}
	//Obstacle 2 Collision
	else if ( s.snake[0][s.length - 1] >= 300 && s.snake[0][s.length - 1] <= 500 && s.snake[1][s.length - 1] >= 400 && s.snake[1][s.length - 1] <= 420 ) 
	{

		delay( 300 );
		cleardevice( );
		
		setcolor( 4 );
		settextjustify( 1, 2 );
		settextstyle( 10, HORIZ_DIR, 5 );
		outtextxy( 300, 200, "GAME OVER" );

		delay( 500 );

		menu( );

	}

}//end colDet

void getPlayer( )
{
	
	cleardevice( );
	p.score = 0;
	memset(p.name,'\0',10);

	char ch = '\0';

	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy( 400, 250, "Please Enter Your Username" );

	rectangle(270,300,500,350);

	for( int i = 0; i < 6; i++)
	{

		ch = getch();
		p.name[i] = toupper(ch);
	
	}

	settextjustify( 1, 2 );
	settextstyle( 10, HORIZ_DIR, 2 );
	outtextxy(380,315,p.name);

	delay( 300 );

	cleardevice( );

}//end getPlayer

void saveGame( )
{

	FILE * fp = fopen("Savegame.txt","w");

	fprintf(fp,"%s\n",p.name);
	fprintf(fp,"%d\n",p.score);
	fprintf(fp,"%d",f.x);
	fprintf(fp," %d\n",f.y);
	fprintf(fp,"%d\n",f.radius);
	fprintf(fp,"%d\n",s.length);
	fprintf(fp,"%d\n",s.height);
	fprintf(fp,"%d\n",s.radius);
	fprintf(fp,"%c\n",s.dir);
	fprintf(fp,"%c\n",s.c);
	
	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length; j++ )
		{
			fprintf(fp,"%d ",s.snake[i][j]);
		}
		fprintf(fp,"\n");
	}

	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length; j++ )
		{
			fprintf(fp,"%d ",s.erase_snake[i][j]);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);

	menuPause( );

}//end saveGame

void loadGame( ) 
{

	FILE * lp = fopen("Savegame.txt","r");

	fscanf(lp,"%s",p.name);
	fscanf(lp,"%d",&p.score);
	fscanf(lp,"%d",&f.x);
	fscanf(lp," %d\n",&f.y);
	fscanf(lp,"%d\n",&f.radius);
	fscanf(lp,"%d\n",&s.length);
	fscanf(lp,"%d\n",&s.height);
	fscanf(lp,"%d\n",&s.radius);
	fscanf(lp,"%c\n",&s.dir);
	fscanf(lp,"%c\n",&s.c);
	
	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length; j++ )
		{
			fscanf(lp,"%d ",&s.snake[i][j]);
		}
		fscanf(lp,"\n");
	}

	for(int i = 0; i < 2; i++)
	{
		for( int j = 0; j < s.length; j++ )
		{
			fscanf(lp,"%d ",&s.erase_snake[i][j]);
		}
		fscanf(lp,"\n");
	}

	fclose(lp);

	cleardevice();

}//end loadGame