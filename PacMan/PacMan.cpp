#include <iostream>
#include <cstdlib>
#include <time.h>
#include <mygraphics.h>

using namespace std;

int lives = 3;
int game_state = 0;
int w = 0, h = 0;

class Board;
class Enemy;

class Player {
	int* x,* y;

	int state;		// Determines if Pacman is in ghost eat mode
	int score;		// The score of the player by eating the dots
	int lives;
	char turn;		// Determines the axis in which the player is moving 
	int speed;		// The speed of the player

	int state_time_count;
	int interval;		// Allocated time for Pacman to eat the ghost

	friend void initializerFunction(Player&, Enemy**);

public:
	Player(int& i, int& j, int lives = 0, int speed = 3) {
		x = &i;
		y = &j;
		this->lives = lives;
		state = 0;
		score = 0;
		turn = 'r';
		this->speed = speed;
		state_time_count = 0;
		interval = 400;
	}

	int getLives() {
		return lives;
	}

	int getInterval() {
		return interval;
	}

	void decLives() {
		this->lives--;
	}

	int getX() {
		return *x;
	}

	int getY() {
		return *y;
	}

	int getState_time_count() {
		return state_time_count;
	}

	void incState_time_count() {
		state_time_count++;
	}

	void resetState_time_count() {
		state_time_count = 0;
	}

	int getScore() {
		return score;
	}

	int getState() {
		return state;
	}

	char getTurn() {
		return turn;
	}

	void setTurn(char turn) {
		this->turn = turn;
	}

	int getSpeed() {
		return this->speed;
	}

	void setSpeed(int speed) {
		this->speed = speed;
	}

	void incScore(int inc) {
		this->score+=inc;
	}

	void updateState() {
		if (this->state == 0)
			state = 1;
		else
			state = 0;
	}

	void drawPlayer(int x1, int y1, int x2, int y2) {

		if (this->state == 1)
			state_time_count++;

		if (state_time_count >= interval) {
			updateState();
			state_time_count = 0;
		}

		if(state == 1)
			drawEllipse(x1, y1, x2, y2, 0, 255, 255, 0, 255, 255);
		else
			drawEllipse(x1, y1, x2, y2, 245, 245, 0, 245, 245, 0);
		delay(9);
		drawEllipse(x1, y1, x2, y2, 0, 0, 0, 0, 0, 0);
		return;
	}
};

class Obstacle {
	int x1, y1, x2, y2;
	static int ObstacleCount;

public:
	Obstacle(int x1, int y1, int x2, int y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		ObstacleCount++;
	}

	void CreateObstacle() {
		drawRectangle(x1, y1, x2, y2, 0, 0, 255);	// A function which would print hollow obstacle
	}

	void CreateGreenObstacle() {
		drawRectangle(x1, y1, x2, y2, 0, 255, 0);	// A function which would print hollow obstacle
	}

	void CreateGreenObstacle(int dontcare) {
		drawRectangle(x1, y1, x2, y2, 0, 255, 0, 0, 255, 0);	// A function which would print hollow obstacle
	}

	void CreateRedObstacle() {
		drawRectangle(x1, y1, x2, y2, 255, 0, 0);	// A function which would print hollow obstacle
	}

	void CreateRedObstacle(int dontcare) {
		drawRectangle(x1, y1, x2, y2, 255, 0, 0, 255, 0, 0);	// A function which would print hollow obstacle
	}

	void CreateObstacle(int dontcare) {						// A function which would print solid obstacle
		drawRectangle(x1, y1, x2, y2, 0, 0, 255, 0, 0, 255);
	}

	bool checkObstacle(int inc1, int inc2, int inc3, int inc4, int x, int y) {
		if (x >= x1+inc1 && y >= y1+inc2 && x <= x2+inc3 && y <= y2+inc4)		// Obstacle Check
			return false;
		return true;
	}

	static int getObstacleCount() {
		return ObstacleCount;
	}
};

class Board {
	int x, y;			// Original Height / Width
	int uwidth, lwidth;		// Upper width / Lower width
	int lheight, rheight;		// Left height / Right height
	Player* CurrentPlayer;			// PacMan
	int PacFood[173];

	Obstacle O[19];

public:
	Board(int x, int y, Player& P)
		: O{ {279, 112, 426, 128}, {158,100,172,237}, {580, 149, 709, 166}, {762, 94, 777, 230},
			{323, 326, 397, 399}, {343, 344, 377, 377}, {431, 325, 506, 399}, {449, 343, 488, 379},
			{548, 324, 566, 400}, {567, 324, 617, 365}, {577, 333, 603, 354}, {761,305,775,404},
			{666,389,760,404}, {158,303,172,402}, {173,387,267,402}, {460,186,474,286}, {416,230,522,245},
			{70,91,82,420}, {881,88,893,416} }			/* Coordinates of an obstacle, any obstacle can be passed and it would start working
																		on its own without implementing anything */

	{
		CurrentPlayer = &P;
		this->x = x;
		this->y = y;
		uwidth = 52; lwidth = y - 39;
		lheight = 6; rheight = x - 499;

		for (int i = 0; i < 173; i++)
			PacFood[i] = 1;		// 1 means that the food is yet to be eaten

		drawBoard();
		drawMaze();
		drawDotes();
	}

	void drawBoard() {
		drawLine(30, 12, x - (x * 60 / 100), 12, 255);			// Upper Lines
		drawLine(x - (x * 43 / 100), 12, x - 30, 12, 255);
		drawLine(30, 37, x - (x * 60 / 100), 37, 255);		// Lower Lines
		drawLine(x - (x * 43 / 100), 37, x - 30, 37, 255);

		gotoxy(55, 1);										// Title
		cout << "PACMAN";

		gotoxy(x - (x * 98 / 100), 1);										// Score
		cout << "Score: " << CurrentPlayer->getScore();

		gotoxy(82, 1);										// Lives
		cout << "Lives: ";
		for (int i = 0; i < CurrentPlayer->getLives(); i++)
			cout << " # ";

	}

	void drawMaze() {
		drawLine(7, 50, x - 10, 50, 255);		// Upper Border
		drawLine(7, 51, x - 11, 51, 255);
		drawLine(8, 50, 8, y - 10, 255);			// Left Border
		drawLine(9, 51, 9, y - 11, 255);
		drawLine(7, y - 10, x - 10, y - 10, 255);			// Lower Border
		drawLine(7, y - 11, x - 11, y - 11, 255);
		drawLine(x - 10, 50, x - 10, y - 10, 255);				// Right Border
		drawLine(x - 11, 50, x - 11, y - 11, 255);

		for (int i = 0; i < Obstacle::getObstacleCount(); i++) {
			if (i == 4 || i == 6 || i == 8 || i == 9)
				O[i].CreateObstacle(0);
			else
				O[i].CreateObstacle();
		}
	}


	bool checkObstacle(int x, int y) {
		for (int i = 0; i < Obstacle::getObstacleCount(); i++) {
			if (!O[i].checkObstacle(-5, 0, 25, 25, x, y))
				return false;
		}
		return true;
	}

	bool checkObstacle(int x, int y, int inc1, int inc2) {
		for (int i = 0; i < Obstacle::getObstacleCount(); i++) {
			if (!O[i].checkObstacle(inc1, 0, inc2, 25, x, y))
				return false;
		}
		return true;
	}

	int getRightHeight() {
		return rheight;
	}

	int getUpperWidth() {
		return uwidth;
	}

	int getLeftHeight() {
		return lheight;
	}

	int getLowerWidth() {
		return lwidth;
	}

	int getPlayerState() {
		return CurrentPlayer->getState();
	}

	Player getCurrentPlayer() {
		return *CurrentPlayer;
	}

	void foodEatenChecker(int x, int y) {
		int count = 0;
		for (int i = lheight + 4; i < rheight - lheight + 10; i += 30) {
			for (int j = uwidth + 10; j < lwidth - uwidth + 67; j += 30) {
				if (checkObstacle(2 * i + 4, j + 4)) {
					if (PacFood[count] == 1) {
						if ((2 * i == 920 && j == 62) || (2 * i == 20 && j == 62)) {
							if (x >= 2 * i - 5 && y >= j - 2 && x <= 2 * i + 10 + 4 + 25 && y <= j + 10 + 2 + 25) {
								drawEllipse(2 * i - 3, j, 2 * i + 10 - 2, j + 10, 0, 0, 0, 0, 0, 0);
								if(CurrentPlayer->getState() == 0)
									CurrentPlayer->updateState();
							}
						}

						if (x >= 2 * i - 2 && y >= j - 2 && x <= 2 * i + 4 + 2 + 25 && y <= j + 4 + 2 + 25) {
							CurrentPlayer->incScore(5);		// Increment of 5 in score per food eaten
							drawRectangle(2 * i, j, 2 * i + 4, j + 4, 0, 0, 0, 0, 0, 0);
							PacFood[count] = 0;
						}
					}
					count++;	// Total would be 173 pieces of food
				}
			}
		}
	}

	void redrawFood(int x, int y) {
		int count = 0;
		for (int i = lheight + 4; i < rheight - lheight + 10; i += 30) {
			for (int j = uwidth + 10; j < lwidth - uwidth + 67; j += 30) {
				if (checkObstacle(2 * i + 4, j + 4)) {
					if (PacFood[count] == 1) {
						if ((2 * i == 920 && j == 62) || (2 * i == 20 && j == 62)) {
							if (x >= 2 * i - 5 && y >= j - 2 && x <= 2 * i + 10 + 4 + 25 && y <= j + 10 + 2 + 25)
								drawEllipse(2 * i - 3, j, 2 * i + 10 - 2, j + 10, 255, 140, 0, 255, 140, 0);
						}

						else if (x >= 2 * i - 2 && y >= j - 2 && x <= 2 * i + 4 + 2 + 25 && y <= j + 4 + 2 + 25) {
							drawRectangle(2 * i, j, 2 * i + 4, j + 4, 255, 255, 255, 255, 255, 255);
						}
					}
					count++;
				}
			}
		}
	}

	bool gameStateON() {
		bool proceed = true;
		for (int i = 0; i < 173; i++)
			if (PacFood[i] != 0)
				proceed = false;

		if (proceed)
			game_state = 1;

		return proceed;
	}

	void drawDotes() {
		int count = 0;
		for (int i = lheight + 4; i < rheight - lheight + 10; i += 30) {
			for (int j = uwidth + 10; j < lwidth - uwidth + 67; j += 30) {
				if (checkObstacle(2 * i + 4, j + 4)) {
					if (PacFood[count] == 1) {
						if((2 * i == 920 && j == 62) || (2 * i == 20 && j == 62))
							drawEllipse(2 * i - 3, j, 2 * i + 10 - 2, j + 10, 255, 140, 0, 255, 140, 0);
						else
							drawRectangle(2 * i, j, 2 * i + 4, j + 4, 255, 255, 255, 255, 255, 255);
					}
					count++;
				}
			}
		}
	}

	bool checkCoordinates(int x, int y) {
		if (y <= getUpperWidth() || x >= getRightHeight() || x <= getLeftHeight() || y >= getLowerWidth())
			return false;
		return true;
	}
};

class Enemy {
	int* x1, * y1;
	int speed;
	int chaseSpeed;
	bool exist;
	Board* B;

	static int EnemyCount;

	friend void initializerFunction(Player&, Enemy**);

public:
	Enemy(int& i, int& j, Board& Board) : x1(&i), y1(&j), B(&Board), exist(true), speed(4), chaseSpeed(2) { EnemyCount++; }

	int getX() {
		return *x1;
	}

	int getSpeed() {
		return speed;
	}

	int getChaseSpeed() {
		return chaseSpeed;
	}

	int getY() {
		return *y1;
	}

	void setX(int x) {
		*x1 = x;
	}

	static int getEnemyCount() {
		return EnemyCount;
	}

	Board getB() {
		return *B;
	}

	void noExistance() {
		exist = false;
	}

	bool exists() {
		if (exist)
			return true;
		else
			return false;
	}

	void setY(int y) {
		*y1 = y;
	}


	virtual void move() = 0;

	void del() {
		drawRectangle(2 * getX(), getY(), 2 * getX() + 25, getY() + 25, 0, 0, 0, 0, 0, 0);
		B->redrawFood(2 * getX() + 25, getY() + 25);
		noExistance();
	}

	int checkCaught(int x, int y) {
		if (x >= 2 * (*x1) - 15 && y >= *y1 - 15 && x <= 2 * (*x1) + 25 + 15 && y <= *y1 + 25 + 15 && B->getPlayerState() != 1)
			return 1;

		else if (x >= 2 * (*x1) - 15 && y >= *y1 - 15 && x <= 2 * (*x1) + 25 + 15 && y <= *y1 + 25 + 15 && B->getPlayerState() == 1)
			return 0;

		return -1;
	}
};

class Prowler : public Enemy {

	int direction;
	int interval;
	int moveCount;

public:
	Prowler(int& x, int& y, Board& B) : Enemy(x, y, B) { direction = 0; interval = 5; moveCount = 0; }

	void ghostAI() {
		double a = sqrt((pow((double)(getX() - getChaseSpeed()) - (getB().getCurrentPlayer().getX()), 2)) + pow((double)getY() 
			- getB().getCurrentPlayer().getY(), 2)); // LEFT

		double b = sqrt((pow((double)(getX() + getChaseSpeed()) - (getB().getCurrentPlayer().getX()), 2)) + pow((double)getY()
			- getB().getCurrentPlayer().getY(), 2)); // RIGHT

		double c = sqrt((pow((double)(getX()) - (getB().getCurrentPlayer().getX()), 2)) + pow((double)(getY() - getChaseSpeed())
			- getB().getCurrentPlayer().getY(), 2)); // UP

		double d = sqrt((pow((double)(getX()) - (getB().getCurrentPlayer().getX()), 2)) + pow((double)(getY() + getChaseSpeed())
			- getB().getCurrentPlayer().getY(), 2)); // DOWN

		if (a < b && a <= c && a <= d && direction != 3) 
			direction = 0;

		else if (b <= c && b <= d && direction != 0) 
			direction = 3;

		else if (c < d && direction != 2) 
			direction = 1;

		else if (direction != 1) 
			direction = 2;

		else
			direction = rand() % 4;	
	}

	void move() {
		getB().redrawFood(2 * getX() + 25, getY() + 25);

		if (moveCount >= interval) {
			moveCount = 0;
			ghostAI();
		}

		switch (direction)
		{
		case 1:
			if (getB().checkCoordinates(getX(), getY() - getChaseSpeed()) && getB().checkObstacle(2 * getX() + 25, getY() + 25 - getChaseSpeed(), -5, 30))
				setY(getY() - getChaseSpeed());
			else
				direction = rand() % 4;
			break;
		case 2:
			if (getB().checkCoordinates(getX(), getY() + getChaseSpeed()) && getB().checkObstacle(2 * getX() + 25, getY() + 25 + getChaseSpeed(), -5, 30))
				setY(getY() + getChaseSpeed());
			else
				direction = rand() % 4;
			break;
		case 0:
			if (getB().checkCoordinates(getX() - getChaseSpeed(), getY()) && getB().checkObstacle(2 * getX() + 25 - getChaseSpeed(), getY() + 25, -5, 30))
				setX(getX() - getChaseSpeed());
			else
				direction = rand() % 4;
			break;
		case 3:
			if (getB().checkCoordinates(getX() + getChaseSpeed(), getY()) && getB().checkObstacle(2 * getX() + 25 + getChaseSpeed(), getY() + 25, -5, 30))
				setX(getX() + getChaseSpeed());
			else
				direction = rand() % 4;
			break;
		}
		moveCount++;
	}
};

class randomChaser : public Enemy {

	int turn;
	int moveCount;
	int interval;

public:
	randomChaser(int& x, int& y, Board& B) : Enemy(x, y, B) { turn = 0; moveCount = 0; interval = 200; }

	void move() {
		getB().redrawFood(2 * getX() + 25, getY() + 25);

		moveCount++;

		if (moveCount >= interval) {
			moveCount = 0;
			turn = rand() % 4;
		}

		switch (turn){
		case 0:
			if(getB().checkCoordinates(getX() - getSpeed(), getY()) && getB().checkObstacle(2 * getX() + 25 - getSpeed(), getY() + 25, -5, 30))
				setX(getX() - getSpeed());
			else
				turn = rand() % 4;
			break;
		case 1:
			if (getB().checkCoordinates(getX(), getY() - getSpeed()) && getB().checkObstacle(2 * getX() + 25, getY() + 25 - getSpeed(), -5, 30))
				setY(getY() - getSpeed());
			else
				turn = rand() % 4;
			break;
		case 2:
			if (getB().checkCoordinates(getX(), getY() + getSpeed()) && getB().checkObstacle(2 * getX() + 25, getY() + 25 + getSpeed(), -5, 30))
				setY(getY() + getSpeed());
			else
				turn = rand() % 4;
			break;
		case 3:
			if (getB().checkCoordinates(getX() + getSpeed(), getY()) && getB().checkObstacle(2 * getX() + 25 + getSpeed(), getY() + 25, -5, 30))
				setX(getX() + getSpeed());
			else
				turn = rand() % 4;
			break;
		}
	}
};

void initializerFunction(Player& P, Enemy** E) {

	if (P.getState() == 1)
		P.incState_time_count();

	if (P.getState_time_count() >= P.getInterval()) {
		P.updateState();
		P.resetState_time_count();
	}

	if (P.getState() == 1)
		drawEllipse(2 * P.getX(), P.getY(), 2 * P.getX() + 25, P.getY() + 25, 0, 255, 255, 0, 255, 255);
	else
		drawEllipse(2 * P.getX(), P.getY(), 2 * P.getX() + 25, P.getY() + 25, 245, 245, 0, 245, 245, 0);


	if(E[0]->exists())
		drawRectangle(2 * E[0]->getX(), E[0]->getY(), 2 * E[0]->getX() + 25, E[0]->getY() + 25, 255, 0, 0, 255, 0, 0);

	if (E[1]->exists())
		drawRectangle(2 * E[1]->getX(), E[1]->getY(), 2 * E[1]->getX() + 25, E[1]->getY() + 25, 255, 192, 203, 255, 192, 203);

	delay(9);

	drawEllipse(2 * P.getX(), P.getY(), 2 * P.getX() + 25, P.getY() + 25, 0, 0, 0, 0, 0, 0);

	for (int i = 0; i < Enemy::getEnemyCount(); i++) {
		if (E[i]->exists()) {
			drawRectangle(2 * E[i]->getX(), E[i]->getY(), 2 * E[i]->getX() + 25, E[i]->getY() + 25, 0, 0, 0, 0, 0, 0);
			E[i]->move();
		}
	}
}

int Obstacle::ObstacleCount = 0;
int Enemy::EnemyCount = 0;

void victory() {
	cls();
	Obstacle* WIN = new Obstacle[15]{ {275,176,302,313}, {275,278,366,313}, {346,211,384,311}, {366,278,447,313},
		{420,178,446,311}, {476,214,503,313}, {476,178,502,203}, {531,179,557,314}, {533,177,568,204}, {568,203,597,225},
		{596,223,624,246}, {621,245,650,268}, {647,267,676,288}, {673,287,699,308}, {687,177,711,313} };

	for (int i = 0; i < 15; i++)
		if(i == 6)
			WIN[i].CreateGreenObstacle(0);
		else
			WIN[i].CreateGreenObstacle();

	delete[] WIN;
}

void defeat() {
	cls();
	Obstacle* LOOSE = new Obstacle[13]{ {215,179,239,315}, {239,294,294,315}, {309,211,411,307}, {327,231,393,288},
	{527,201,438,222}, {438,221,458,249}, {438,237,526,260}, {502,255,526,308}, {509,308,438,286}, {558,200,580,314},
	{560,199,643,225}, {559,244,632,268}, {644,314,559,290} };

	for (int i = 0; i < 13; i++)
		if (i == 3)
			LOOSE[i].CreateRedObstacle(0);
		else
			LOOSE[i].CreateRedObstacle();

	delete[] LOOSE;
}

int main() {

	srand(time(0));
	getWindowDimensions(w, h);
	cls();
	showConsoleCursor(false);

	int i = 59, j = 88;
	int ri = 205, rj = 200;
	int pi = 305, pj = 200;

	Player PacMan(i, j, lives);		// Lives;
	Enemy** Enemies = new Enemy * [2];

	Board Board(w, h, PacMan);

	Enemies[0] = new randomChaser(ri, rj, Board);
	Enemies[1] = new Prowler(pi, pj, Board);

	// main event loop

	do {
		initializerFunction(PacMan, Enemies);

		Board.drawBoard();

		if (PacMan.getTurn() == 'r') {
			if (Board.checkCoordinates(i + 2, j) && Board.checkObstacle(2 * i + 25 + 2, j + 25)) {
				i+=2;
			}
		}

		else if (PacMan.getTurn() == 'l') {
			if (Board.checkCoordinates(i - 2, j) && Board.checkObstacle(2 * i + 25 - 2, j + 25)) {
				i-=2;
			}
		}

		else if (PacMan.getTurn() == 'u') {
			if (Board.checkCoordinates(i, j + 2) && Board.checkObstacle(2 * i + 25, j + 25 + 2)) {
				j+=2;
			}
		}

		else if (PacMan.getTurn() == 'd') {
			if (Board.checkCoordinates(i, j - 2) && Board.checkObstacle(2 * i + 25, j + 25 - 2)) {
				j-=2;
			}
		}

		char c = getKey();

		if (c == 'q') break;

		if (c == 'l' && Board.checkCoordinates(i + PacMan.getSpeed(), j)) {
			if (Board.checkObstacle(2 * i + 25 + PacMan.getSpeed(), j + 25)) {
				i += PacMan.getSpeed();
				PacMan.setTurn('r');
			}
		}

		if (c == 'j' && Board.checkCoordinates(i - PacMan.getSpeed(), j)) {
			if (Board.checkObstacle(2 * i + 25 - PacMan.getSpeed(), j + 25)) {
				i -= PacMan.getSpeed();
				PacMan.setTurn('l');
			}
		}

		if (c == 's')
			i = 6;

		if (c == 'k' && Board.checkCoordinates(i, j + PacMan.getSpeed())) {
			if (Board.checkObstacle(2 * i + 25, j + 25 + PacMan.getSpeed())) {
				j += PacMan.getSpeed();
				PacMan.setTurn('u');

			}
		}

		if (c == 'i' && Board.checkCoordinates(i, j - PacMan.getSpeed())) {
			if (Board.checkObstacle(2 * i + 25, j + 25 - PacMan.getSpeed())) {
				j -= PacMan.getSpeed();
				PacMan.setTurn('d');
			}
		}

		Board.foodEatenChecker(2 * i + 25, j + 25);

			if (Enemies[0]->exists()) {
				if (Enemies[0]->checkCaught(2 * i + 25, j + 25) == 1) {
					if (PacMan.getLives() <= 0)
						game_state = 2;
					else {
						PacMan.decLives();
						i = 59, j = 88;
						cls();
						Board.drawBoard();
						Board.drawMaze();
						Board.drawDotes();
					}
				}

				else if (Enemies[0]->checkCaught(2 * i + 25, j + 25) == 0) {
					Enemies[0]->del();
				}
			}

			if (Enemies[1]->exists()) {
				if (Enemies[1]->checkCaught(2 * i + 25, j + 25) == 1) {
					if (PacMan.getLives() <= 0)
						game_state = 2;
					else {
						PacMan.decLives();
						i = 59, j = 88;
						cls();
						Board.drawBoard();
						Board.drawMaze();
						Board.drawDotes();
					}
				}

				else if (Enemies[1]->checkCaught(2 * i + 25, j + 25) == 0) {
					Enemies[1]->del();
				}
			}

	} while (!Board.gameStateON() && game_state == 0);

	// cleaning

	delete[] Enemies;
	drawLine(0, 5, w, 5, 0);
	drawEllipse(w - 10, 0, w, 10, 0, 0, 0, 0, 0, 0);

	if (game_state == 1)
		victory();
	else
		defeat();

	delay(500);
	showConsoleCursor(true);
	gotoxy(0, 0);

	return 0;
}
