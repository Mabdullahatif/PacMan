#include <iostream>
#include <mygraphics.h>

using namespace std;

void maximizeWindow() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

class Board {
	int x, y;	// Original Height / Width
	int uwidth, lwidth;		// Upper width / Lower width
	int lheight, rheight;		// Left height / Right height
	int lives;

public:
	Board(int x, int y, int lives) {
		this->x = x;
		this->y = y;
		this->lives = lives;
		uwidth = 52; lwidth = y - 32; 
		lheight = 6; rheight = x - 496;
		drawBoard();
	}

	void drawBoard() {
		drawLine(30, 12, x - (x* 60/100), 12, 255);			// Upper Lines
		drawLine(x - (x * 43 / 100), 12, x - 30, 12, 255);
		drawLine(30, 37, x - (x * 60 / 100), 37, 255);		// Lower Lines
		drawLine(x - (x * 43 / 100), 37, x - 30, 37, 255);

		gotoxy(55, 1);										// Title
		cout << "PACMAN";

		gotoxy(x - (x * 98.5/100), 1);										// Score
		cout << "Score: ";

		gotoxy(82, 1);										// Lives
		cout << "Lives: ";
		for (int i = 0; i < this->lives; i++)
			cout << " # ";

		drawMaze();
		drawDotes();
	}

	void drawMaze() {
		drawLine(7, 50, x-10, 50, 255);		// Upper Border
		drawLine(7, 51, x-11, 51, 255);	
		drawLine(8, 50, 8, y-10, 255);			// Left Border
		drawLine(9, 51, 9, y-11, 255);
		drawLine(7, y-10, x-10, y-10, 255);			// Lower Border
		drawLine(7, y-11, x-11, y-11, 255);
		drawLine(x-10, 50, x-10, y-10, 255);				// Right Border
		drawLine(x-11, 50, x-11, y-11, 255);	
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

class Player {
	int state;		// Determines if Pacman is in ghost eat mode
	int score;		// The score of the player by eating the dots
	int lives;		// The lives of the player

	char turn;		// Determines the axis in which the player is moving 
	int speed;		// The speed of the player

	Board Board;

public:
	Player(int w, int h, int lives = 0, int speed = 2): Board(w, h, lives) {
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

	bool checkCoordinates(int x, int y) {
		if (y <= Board.getUpperWidth() || x >= Board.getRightHeight() || x <= Board.getLeftHeight() || y >= Board.getLowerWidth())
			return false;
		return true;
	}

	void drawPlayer(int x1, int y1, int x2, int y2) {
		Board.drawBoard();
		drawEllipse(x1, y1, x2, y2, 245, 245, 0, 245, 245, 0);
		delay(9);
		drawEllipse(x1, y1, x2, y2, 0, 0, 0, 0, 0, 0);
		return;
	}
};

int main() {

	// Initialising
	int w = 0, h = 0;
	getWindowDimensions(w, h);
	cout << w << " " << h;

	cls();
	showConsoleCursor(false);

	Player PacMan(w, h, 3);		// Lives = 3;

	// main event loop
	int i = 59, j = 88;
	while (true) {

		PacMan.drawPlayer(2 * i, j, 2 * i + 25, j + 25);

		if (PacMan.checkCoordinates(i + 1, j)) {
			if (PacMan.getTurn() == 'r')
				i++;
			else if (PacMan.getTurn() == 'l')
				i--;
			else if (PacMan.getTurn() == 'u')
				j++;
			else if (PacMan.getTurn() == 'd')
				j--;
		}

		char c = getKey();

		if (c == 'q') break;

		if (c == 'l' && PacMan.checkCoordinates(i + PacMan.getSpeed(), j)) {
			i += PacMan.getSpeed();
			PacMan.setTurn('r');
		}

		if (c == 'j' && PacMan.checkCoordinates(i - PacMan.getSpeed(), j)) {
			i -= PacMan.getSpeed();
			PacMan.setTurn('l');
		}

		if (c == 's')
			i = 6;

		if (c == 'k' && PacMan.checkCoordinates(i, j + PacMan.getSpeed())) {
			j += PacMan.getSpeed();
			PacMan.setTurn('u');
		}

		if (c == 'i' && PacMan.checkCoordinates(i, j - PacMan.getSpeed())) {
			j -= PacMan.getSpeed();
			PacMan.setTurn('d');
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
