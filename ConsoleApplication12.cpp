#include "pch.h"
#include <iostream>

#include <stdlib.h>
// srand, rand 를 사용하기 위해 주가
// srand() : 섞는 기준을 저장하는 함수
// srand(time(NULL)); : 섞는 기준을 현재시간으로 설정하겠다. 섞는 기준이 계속 바뀌기 때문에 랜덤값을 계속 받아낼 수 있음.

#include <conio.h>
// _kbhit() 함수 사용하기 위해 추가

#include <time.h>
//time 함수를 사용하기 위해 추가
#include<windows.h> 
// System("cls") 함수를 사용하기 위해 추가

#define LEFT 0
#define UP 1
#define DOWN 2
#define RIGHT 3

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80

void FindZero(); // 코드 어딘가에  FindZero() 함수가 존재한다는것을 의미.

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

	while(count < 150 ) //섞을 횟수
	{
		
		int dir = rand() % 4;
		FindZero(); // 0의 위치를 찾아 gRow, gCol에 저장한다.
		
		int nR = gRow;
		int nC = gCol;
		// 0의 위치를 임시 변수에 저장한다.

		switch( dir )
		{
			case LEFT:
				if( gCol == 0 )
					continue;     // 다시 순환문(while) 으로 돌아간다는 것을 의미
				
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
		
		int temp = Table[gRow][gCol];        // temp 에 0의 값을 넣겠다.
		Table[gRow][gCol] = Table[nR][nC];   // Table[gRow][gCol] 자리에 Table[nR][nC];  값을 넣겠다는 의미
		Table[nR][nC] = temp;                // Table[nR][nC] 에 Table[gRow][gCol]; 에 있던 값을 넣겠다는 의미
    	++count;

	}
}

void Input() //키보드 입력받는 함수
{
	if( _kbhit() ) // 키보드버퍼 : 키보드 값이 입력된다면 1을 출력
	{
		int Key = _getche(); //키보드 버퍼로부터 1바이트값 얻어옴

		if( Key == 224 ) // 224는 확장키를 의미 화살표키 부분 오른쪽 자판은 확장키라 첫값에 224 그뒤 키값 2바이트를 입력받음.
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

void FindZero() // 0값을 찾는 함수
{
	for( int row = 0; row < 3; row++ )
	{
		for( int col = 0; col < 3; col++ )
		{
			if( Table[row][col] == 0 )
			{
				// 0값이 위치하고 있는 행과 열의 값을 전역 변수에 저장
				gRow = row;
				gCol = col;
				// 0값을 찾았다면 함수를 종료
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

int IsEnd()
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









// 초기화 함수 구현 ( lnit )
// 출력 함수 구현 ( Display )
// 0의 위치를 찾는 함수 구현 ( FindZero )
// 입력을 받는 함수 구현 ( Input )
// 섞는 함수 구현 ( Shuffle )

//3*3 배열을 선언하고, Init() 함수를 만들어서 배열값을 
//1,2,3,4,5,6,7,8,0 순으로 초기화 되도록 한다.

//게임 테이블에 있는 값을 그대로 출력해 본다.

//게임 테이블을 순회하면서 0을 찾도록 하고, 찾은 위치값을 전역변수에 저장한다.

// kbhit() 함수를 사용하여 키보드 버퍼에 저장된 값이 있는지 체크하고 , 저장된 값이 있다면 _getche() 함수를 사용하여 1바이트를 얻어온다
// 얻어온 값이 224 라면 확장키이며, 이때 다른 1바이트를 얻어와서 좌,우,상,하 에 해당하는 값인지 검사하고 처리한다.