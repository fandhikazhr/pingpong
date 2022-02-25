#include<iostream>
#include<time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>
using namespace std;

int _kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

enum eDir {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};
class cBall{
	private:
		int x,y;
		int originalX, originalY;
		eDir direction;
	public:
		cBall(int posX, int posY){
			originalX = posX;
			originalY = posY;
			x = posX; y = posY;
			direction = STOP;
		}
		void Reset(){
			x = originalX; y = originalY;
			direction = STOP;
		}
		void changeDirection(eDir d){
			direction = d;
		}
		void randomDirection(){
			direction = (eDir)((rand() % 6) + 1);
		}
		inline int getX() { return x; }
		inline int getY() { return y; }
		inline eDir getDirection() { return direction; }
		void Move(){
			switch(direction){
				case STOP:
					break;
				case LEFT:
					x--;
				break;
				case RIGHT:
					x++;
				break;
				case UPLEFT:
					x--; y--;
				break;
				case DOWNLEFT:
					x--; y++;
				break;
				case UPRIGHT:
					x++; y--;
				break;
				case DOWNRIGHT:
					x++; y++;
				break;
				default:
					break;
			}
		}
		friend ostream& operator<<(ostream & o, cBall c){
			o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
			return o;
		}

};

class cPaddle{

	private:
		int x, y;
		int originalX, originalY;
	public:
		cPaddle(){
			x = y = 0;
		}
		cPaddle(int  posX, int posY) : cPaddle(){
			
			originalX = posX;
			originalY = posY;
			x = posX;
			y = posY;

		}
		inline void Reset() { x = originalX; y = originalY; }
		inline int getX() { return x; }
		inline int getY() { return y; }
		inline void moveUp() { y--; }
		inline void moveDown() { y++; }
		friend ostream& operator<<(ostream & o, cPaddle c){
			o << "Paddle [" << c.x << "," << c.y << "]";
			return o;
		}

};
