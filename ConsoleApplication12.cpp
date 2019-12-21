#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include<windows.h> 

#define LEFT 0
#define UP 1
#define DOWN 2
#define RIGHT 3

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80

void FindZero(); 

int Table[3][3];
int gRow = 0;
int gCol = 0;


void lnit() // 기본 셋팅
{
	int count = 1;
	for( int row = 0; row < 3; row++ )
	{
		for( int col = 0; col < 3; col++ )
		{
			Table[row][col] = count;
			++count;
		}
	}
	Table[2][2] = 0;
}

void Shuffle() // 퍼즐 섞는 함수
{
	int count = 0;

	while(count < 150 )
	{
		
		int dir = rand() % 4;
		FindZero();
		
		int nR = gRow;
		int nC = gCol;
		

		switch( dir )
		{
			case LEFT:
				if( gCol == 0 )
					continue;     
				
				nC = gCol - 1;
				break;

			case RIGHT:
				if( gCol == 2 )
					continue;

				nC = gCol + 1;
				break;

			case UP:
				if( gRow == 0 )
					continue;

				nR = gRow - 1;
				break;

			case DOWN:
				if( gRow == 2 )
					continue;

				nR = gRow + 1;
				break;
		}
		
		int temp = Table[gRow][gCol];       
		Table[gRow][gCol] = Table[nR][nC];   
		Table[nR][nC] = temp;               
    	++count;

	}
}

void Input() //키보드 입력받는 함수
{
	if( _kbhit() ) 
	{
		int Key = _getche(); 

		if( Key == 224 ) 
		{
			Key = _getche();

			FindZero();
			int nR = gRow;
			int nC = gCol;

			switch( Key )
			{
				case KEY_LEFT:
					if( gCol == 0 )
						return;
					nC = gCol - 1;
					break;
				case KEY_RIGHT:
					if( gCol == 2 )
						return;
					nC = gCol + 1;
					break;
				case KEY_UP:
					if( gRow == 0 )
						return;
					nR = gRow - 1;
					break;
				case KEY_DOWN:
					if( gRow == 2 )
						return;
					nR = gRow + 1;
					break;
			}

			int temp = Table[gRow][gCol];
			Table[gRow][gCol] = Table[nR][nC];
			Table[nR][nC] = temp;
		}
	}
}

void FindZero() 
{
	for( int row = 0; row < 3; row++ )
	{
		for( int col = 0; col < 3; col++ )
		{
			if( Table[row][col] == 0 )
			{
				
				gRow = row;
				gCol = col;
				return;
			}
		
		}
	}
}



void Display() // 기본셋팅 디스플레이 출력
{
	for( int row = 0; row < 3; row++ )
	{
		for( int col = 0; col < 3; col++ )
		{
			printf("[%2d]", Table[row][col]);
		}
		printf("\n");
	}
}

int IsEnd() // 게임 끝내는 함수
{
	int count = 1;
	for( int row = 0; row < 3; row++ )
	{
		for( int col = 0; col < 3; col++ )
		{
			if( Table[row][col] == count )
			{
				++count;
			}
		}
	}
	if( Table[2][2] == 0 )
	{
		if( count == 9 )
			return 1;
	}
	return 0;
}


int main()
{
	srand(time(0)); 

	lnit();
	Shuffle();
	while( true )
	{
		system("cls"); //화면을 지움
		Input();
		Display();	
		if( IsEnd() )
		{
			break;
		}
	}
	printf("게임클리어");
	
}
