#include <iostream>
#include <mygraphics.h>

using namespace std;

int lives = 3;

void maximizeWindow() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

class Player {
	int state;		// Determines if Pacman is in ghost eat mode
	int score;		// The score of the player by eating the dots
	int lives;
	char turn;		// Determines the axis in which the player is moving 
	int speed;		// The speed of the player

public:
	Player(int lives = 0, int speed = 2) {
		this->lives = lives;
		state = 0;
		score = 0;
		turn = 'r';
		this->speed = speed;
	}

	int getLives() {
		return lives;
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

	void updateState() {
		if (this->state == 0)
			state = 1;
		else
			state = 0;
	}

	void drawPlayer(int x1, int y1, int x2, int y2) {
		drawEllipse(x1, y1, x2, y2, 245, 245, 0, 245, 245, 0);
		delay(9);
		drawEllipse(x1, y1, x2, y2, 0, 0, 0, 0, 0, 0);
		return;
	}
};

class Board {
	int x, y;	// Original Height / Width
	int uwidth, lwidth;		// Upper width / Lower width
	int lheight, rheight;		// Left height / Right height
	Player* CurrentPlayer;			// PacMan

public:
	Board(int x, int y, Player& P) {
		CurrentPlayer = &P;
		this->x = x;
		this->y = y;
		uwidth = 52; lwidth = y - 32;
		lheight = 6; rheight = x - 496;
		drawBoard();
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

		drawMaze();
		drawDotes();
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

		drawRectangle(279, 112, 426, 128, 0, 0, 255);		// First Obstacle
		drawRectangle(192, 130, 207, 236, 0, 0, 255);		// Second

		drawRectangle(567, 149, 696, 166, 0, 0, 255);		// Third 

		drawRectangle(762, 94, 777, 230, 0, 0, 255);		// Fourth

		drawRectangle(323, 326, 397, 399, 0, 0, 255);		// "O"
		drawRectangle(343, 344, 377, 377, 0, 0, 255);

		drawRectangle(431, 325, 506, 399, 0, 0, 255);		// "O"
		drawRectangle(449, 343, 488, 379, 0, 0, 255);

		drawRectangle(548, 324, 566, 400, 0, 0, 255);		// "P
		drawRectangle(567, 324, 617, 365, 0, 0, 255);
		drawRectangle(577, 333, 603, 354, 0, 0, 255);
		
	}

	bool checkObstacle(int x, int y) {

		if (x >= 279 && y >= 112 && x <= 426 + 25 && y <= 128 + 25)		// First
			return false;

		if (x >= 191 && y >= 129 && x <= 208 + 25 && y <= 237 + 25)		// Second
			return false;

		if (x >= 567 && y >= 149 && x <= 696 + 25 && y <= 166 + 25)		// Third
			return false;

		if (x >= 762 - 2 && y >= 94 && x <= 777 + 25 && y <= 230 + 25)	// Fourth
			return false;

		if (x >= 323 && y >= 326 && x <= 397 + 25 && y <= 399 + 25)		// O
			return false;

		if (x >= 431 && y >= 325 && x <= 506 + 25 && y <= 399 + 25)		// O
			return false;

		if (x >= 548 && y >= 324 && x <= 566 + 25 && y <= 400 + 25)		// P Bar
			return false;

		if (x >= 567 && y >= 324 && x <= 617 + 25 && y <= 365 + 25)		// P Outline
			return false;

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

	void drawDotes() {}
};


bool checkCoordinates(int x, int y, Board B) {
	if (y <= B.getUpperWidth() || x >= B.getRightHeight() || x <= B.getLeftHeight() || y >= B.getLowerWidth())
		return false;
	return true;
}

int main() {

	// Initialising
	int w = 0, h = 0;
	getWindowDimensions(w, h);
	cout << w << " " << h << endl;

	cls();
	showConsoleCursor(false);

	Player PacMan(lives);		// Lives;
	Board Board(w, h, PacMan);

	// main event loop
	int i = 59, j = 88;
	while (true) {

		Board.drawBoard();
		PacMan.drawPlayer(2 * i, j, 2 * i + 25, j + 25);

		if (PacMan.getTurn() == 'r') {
			if (checkCoordinates(i + 1, j, Board) && Board.checkObstacle(2 * i + 25, j + 25))
				i++;
		}

		else if (PacMan.getTurn() == 'l') {
			if (checkCoordinates(i - 1, j, Board) && Board.checkObstacle(2 * i + 25, j + 25))
				i--;
		}

		else if (PacMan.getTurn() == 'u') {
			if (checkCoordinates(i, j + 1, Board) && Board.checkObstacle(2 * i + 25, j + 25))
				j++;
		}

		else if (PacMan.getTurn() == 'd') {
			if (checkCoordinates(i, j - 1, Board) && Board.checkObstacle(2 * i + 25, j + 25))
				j--;
		}

		char c = getKey();

		if (c == 'q') break;

		if (c == 'l' && checkCoordinates(i + PacMan.getSpeed(), j, Board)) {
			if (Board.checkObstacle(2 * i + 25, j + 25)) {
				i += PacMan.getSpeed();
				PacMan.setTurn('r');
			}
			else {
				j += PacMan.getSpeed();
				PacMan.setTurn('l');
			}

		}

		if (c == 'j' && checkCoordinates(i - PacMan.getSpeed(), j, Board)) {
			if (Board.checkObstacle(2 * i + 25, j + 25)) {
				i -= PacMan.getSpeed();
				PacMan.setTurn('l');
			}
		}

		if (c == 's')
			i = 6;

		if (c == 'k' && checkCoordinates(i, j + PacMan.getSpeed(), Board)) {
			if (Board.checkObstacle(2 * i + 25, j + 25)) {
				j += PacMan.getSpeed();
				PacMan.setTurn('u');
			}
		}

		if (c == 'i' && checkCoordinates(i, j - PacMan.getSpeed(), Board)) {
			if (Board.checkObstacle(2 * i + 25, j + 25)) {
				j -= PacMan.getSpeed();
				PacMan.setTurn('d');
			}
		}
	}

	// cleaning
	drawLine(0, 5, w, 5, 0);
	drawEllipse(w - 10, 0, w, 10, 0, 0, 0, 0, 0, 0);

	cls();
	showConsoleCursor(true);

	gotoxy(0, 0);

	return 0;
}
