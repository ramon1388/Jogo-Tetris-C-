#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{int x,y;} a[4], b[4];

int figures[7][4] =
{
	1,3,5,7,
	2,4,5,7, 
	3,5,4,6, 
	3,5,4,7, 
	2,3,5,7, 
	3,5,7,6, 
	2,3,4,5, 
};

bool check()
{
   for (int i=0;i<4;i++)
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};


int main()
{
    srand(time(0));	 

	RenderWindow window(VideoMode(320, 480), "O Jogo Tetris!");

    Texture t1,t2,t3;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");

	Sprite s(t1), background(t2), frame(t3);

    int dx=0; bool rotate=0; int colorNum=1;
	float timer=0,delay=0.3; 

	Clock clock;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

			if (e.type == Event::KeyPressed)
			  if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;
		}

	if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

	//// <- Mover -> ///
	for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];

	//////Girar//////
	if (rotate)
	  {
		Point p = a[1]; //Girar Para o centro
		for (int i=0;i<4;i++)
		  {
			int x = a[i].y-p.y;
			int y = a[i].x-p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
	 	  }
   	    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
	  }

	///////Tempo//////
	if (timer>delay)
	  {
	    for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

		if (!check())
		{
		 for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

		 colorNum=1+rand()%7;
		 int n=rand()%7;
		 for (int i=0;i<4;i++)
		   {
		    a[i].x = figures[n][i] % 2;
		    a[i].y = figures[n][i] / 2;
		   }
		}

	  	timer=0;
	  }

	///////Verifica as linhas//////////
    int k=M-1;
	for (int i=M-1;i>0;i--)
	{
		int count=0;
		for (int j=0;j<N;j++)
		{
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
		}
		if (count<N) k--;
	}

    dx=0; rotate=0; delay=0.3;

    /////////Empate//////////
    window.clear(Color::White);	
    window.draw(background);
		  
	for (int i=0;i<M;i++)
	 for (int j=0;j<N;j++)
	   {
         if (field[i][j]==0) continue;
		 s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
		 s.setPosition(j*18,i*18);
		 s.move(28,31); 
		 window.draw(s);
	   }

	for (int i=0;i<4;i++)
	  {
		s.setTextureRect(IntRect(colorNum*18,0,18,18));
		s.setPosition(a[i].x*18,a[i].y*18);
		s.move(28,31); 
		window.draw(s);
	  }

	window.draw(frame);
 	window.display();
	}

    return 0;
}
