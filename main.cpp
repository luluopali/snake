#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define lenght 20
#define weight 60

using namespace std;

int global_max = 3;
bool check_game = true;

class Snake
{
	public:
	int position_x;
	int position_y;
};

class maca
{
	public:
 	int position_xm;
 	int position_ym;
 	maca(int x, int y)
 	{
	 	position_xm = x;
	 	position_ym = y;
    }
};

maca M(6,5);

int point=0;
int keyword;
int UP=0,DOWN=1,LEFT=2,RIGHT=3;

char terminus()
{
	char check;
	M.position_xm = 6;
	M.position_ym = 5;
	cout << "sua pontuacao foi: " << point << endl;
	cout << "deseja jogar novamente [S/N]";
	cin >> check;
	return check;
}

char mapa[lenght][weight];

Snake snake[1000] = {{4,3}};

void update_screen()
{
	for(int i=0;i<lenght;i++)
	{
		for(int k=0;k<weight;k++)
		{
			if(i == 0 || i == lenght-1)
			{
				mapa[i][k] = '+';
			}
			else if((i != 0 && i != lenght-1) && (k == 0 || k == weight-1))
			{
				mapa[i][k] = '+';
			}
			if(i != 0 && i != lenght-1 && k != 0 && k != weight-1)
			{
			    mapa[i][k] = ' ';
			}
			else if(i == snake[0].position_y && k == snake[0].position_x)
			{
				mapa[snake[0].position_y][snake[0].position_x] = '+';
			}
			for(int pos=global_max;pos>0;pos--)
	        {
	   	        mapa[snake[pos].position_y][snake[pos].position_x] = 'O';
	        }

			if(i == M.position_ym && k == M.position_xm)
			{
				mapa[i][k] = 'O';
			}

			else if(snake[0].position_y == M.position_ym && snake[0].position_x == M.position_xm)
			{
				srand(time(0));
				global_max++;
				M.position_xm = rand()%58;
				M.position_ym = rand()%18;
				point++;
			}
			cout << mapa[i][k];
			if(k==weight-1 && i == 0)
            {
				cout << " pontuacao: " << point;
            }
		}
		cout << endl;
	}
}

void update_position()
{
    if(keyword == UP)
	   snake[0].position_y--;
    else if(keyword == RIGHT)
	   snake[0].position_x++;
    if(keyword == DOWN)
	   snake[0].position_y++;
    else if(keyword == LEFT)
	   snake[0].position_x--;

   //mudança de posição se tocar nas paredes do mapa alternando para o oposto eixo x
    if(snake[0].position_x < 0)
   	   snake[0].position_x = weight-1;
    else if(snake[0].position_x > weight-1)
   	   snake[0].position_x = 0;
   //mudança de posição se tocar nas paredes do mapa alternando para o oposto eixo y
    if(snake[0].position_y < 0)
   	   snake[0].position_y = lenght-1;
    else if(snake[0].position_y > lenght-1)
   	   snake[0].position_y = 0;

	   for(int pos=global_max;pos>0;pos--)
	   {
	   	   snake[pos].position_y = snake[pos-1].position_y;
	   	   snake[pos].position_x = snake[pos-1].position_x;
	   	   if(snake[0].position_x == snake[pos+1].position_x && snake[0].position_y == snake[pos+1].position_y)
			  {
			  	if(terminus() == 'S')
			    {
			 	   snake[0].position_x = 4;
 	               snake[0].position_y = 4;
			 	   point = 0;
			 	   global_max = 3;
			    }
			    else{check_game = false;}
			  }
       }
}

int main(int argc, char** argv)
{
    keyword = DOWN;
    while(check_game)
	{
	update_screen();
	for(int i=0;i<=30000000;i++)
	{
		if(i==30000000){system("cls");}
	}

	   	char l;
	   	if(kbhit()){l = getch();}
	   	if(l=='w' && keyword != DOWN){keyword=UP;}
        if(l=='a' && keyword != RIGHT){keyword=LEFT;}
  	    if(l=='s' && keyword != UP){keyword=DOWN;}
    	if(l=='d' && keyword != LEFT){keyword=RIGHT;}
 		if(l=='e')
		 {
		 	if(terminus() == 'S')
			 {
			 	snake[0].position_x = 4;
			 	snake[0].position_y = 4;
			 	point = 0;
			 	global_max = 3;
			 	l = 'd';
			 }
		    else{break;}
		 }
	 update_position();
    }
   return 0;
}
