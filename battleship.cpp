/*CPSC 230                                Fall 2021                                 Mr. Irish
Michael Wang
*/

//libraries
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

const int MAX = 10;

using namespace std;

//class
class gameplay
{
public:
	//prototypes
	string playerOneBoard[MAX][MAX];
	string playerTwoBoard[MAX][MAX];
	string playerOneTarget[MAX][MAX];
	string playerTwoTarget[MAX][MAX];
	string computerReference[MAX][MAX];
	int indexes[3][MAX];
	int choice;
	int round = 1;
	string names[2];
	gameplay(string inputp1[][MAX], string inputp2[][MAX], int twoOrOne, string pnames[], int positions[][MAX]);
	void playGame();
	void playerMove();
	void computerMove();
	void shipSank(); // uses the indexes list to compare
	bool shipsLeft();
	void outOfBounds(int& var);
	void selector(int axis, int number, int x, int y);
	int winner();
	void printABoard();
};
//manually set board-yes
void manualBoard(string playerArray[][MAX], int indexArray[][MAX], int index);
//set board automatically-yes
void autoBoard(string playerArray[][MAX], int indexArray[][MAX], int index);
//place ships (called by manualBoard)-yes
bool placeShip(int length, int xcoor, int ycoor, int zcoor, string playerArray[][MAX]);
//fill arrays-yes
void initialize(string playerArray[][MAX]);
//print the board-yes
void printBoard(string playerArray[][MAX]);
//show instructions-yes
void manualInstruct();
void autoInstruct();
//start program-yes
void input(int& twoOrOne, int& autoOrMan, string names[]);
void withinBounds(int& check);

int main()
{
	srand(time(NULL));
	//if x, blank, if m, miss, if h, ship hit, if o, ship on orignal graph, if s, ship sank

	int choice;
	int speedup;
	string playerNames[2];
	string playerOne[MAX][MAX];
	string playerTwo[MAX][MAX];
	string michael;
	string wang;
	int shipPos[3][MAX];
	input(choice, speedup, playerNames);

	initialize(playerOne);
	initialize(playerTwo);

	if (speedup == 1)
	{
		autoInstruct();
		cout << "\n\nFor " << playerNames[0] << endl;
		cout << "Initializing board" << endl;
		autoBoard(playerOne, shipPos, 0);
		printBoard(playerOne);
		cout << "Done!" << endl;
	}
	else
	{
		manualInstruct();
		cout << "\n\nFor " << playerNames[0] << endl;
		manualBoard(playerOne, shipPos, 0);
	}

	if (choice == 1)
	{
		cout << "Please hand the device off to player 2, enter 'huck finn' when done." << endl;
		cin >> michael;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	}

	if (choice == 0)
	{
		cout << "\n\nInitializing computer's board" << endl;
		autoBoard(playerTwo, shipPos, 5);
		cout << "Done!\n" << endl;
	}
	else if (speedup == 1)
	{
		cout << "\n\nFor " << playerNames[1] << endl;
		autoBoard(playerTwo, shipPos, 5);
		printBoard(playerTwo);
	}
	else
	{
		cout << "\n\nFor " << playerNames[1] << endl;
		manualBoard(playerTwo, shipPos, 5);
	}

	if (!choice == 0)
	{
		cout << "Please enter 'tom sawyer' when done and hand the device to player 2 when done." << endl;
		cin >> wang;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	}
	gameplay newGame(playerOne, playerTwo, choice, playerNames, shipPos);
	newGame.playGame();
	return 0;
}


void manualBoard(string playerArray[][MAX], int indexArray[][MAX], int index)
{
	int x, y, z;
	bool successful = false;

	printBoard(playerArray);
	for (int i = 1; i < 6; i++)
	{
		while (!successful)
		{
			cout << "What is the x coordinate of the location of the ship of length " << i << "? (0 - 9)" << endl;
			cin >> x;
			while (x < 0 || x > 9)
			{
				cout << "Please input a valid coordinate value." << endl;
				cin >> x;
			}
			cout << "What is the y coordinate of the location of the ship of length " << i << "? (0 - 9)" << endl;
			cin >> y;
			while (y < 0 || y > 9)
			{
				cout << "Please input a valid coordinate value." << endl;
				cin >> y;
			}
			if (i > 1)
			{
				cout << "What is the orientation of the ship? '1' for vertical, '0' for horizontal" << endl;
				withinBounds(z);
			}
			else
			{
				z = 2;
			}
			successful = placeShip(i, x, y, z, playerArray);
			if (!successful)
			{
				cout << "Ship exceeded bounds of coordinate plane, try again." << endl;
			}
			else
			{
				cout << "Ship of length " << i << " successfully added!\n\n" << endl;
				printBoard(playerArray);
				indexArray[0][i - 1 + index] = x;
				indexArray[1][i - 1 + index] = y;
				indexArray[2][i - 1 + index] = z;
			}
		}
		successful = false;
	}
	return;
}

bool placeShip(int length, int xcoor, int ycoor, int zcoor, string playerArray[][MAX])
{
	bool overlap = false;
	if (zcoor == 1)
	{
		if (ycoor + length - 1 < MAX)
		{
			for (int i = 0; i < length; i++)
			{
				if (playerArray[9- ycoor - i][xcoor] == "o")
				{
					return false;
				}
			}
			for (int i = 0; i < length; i++)
			{
				playerArray[9 - ycoor - i][xcoor] = "o";
			}
			return true;
		}
	}
	else if (zcoor == 0)
	{
		if (xcoor + length - 1 < MAX)
		{
			for (int i = 0; i < length; i++)
			{
				if (playerArray[9 - ycoor][xcoor + i] == "o")
				{
					return false;
				}
			}
			for (int i = 0; i < length; i++)
			{
				playerArray[9 - ycoor][xcoor + i] = "o";
			}
			return true;
		}
	}
	else
	{
		playerArray[9- ycoor][xcoor] = "o";
		return true;
	}
	return false;
}
void initialize(string playerArray[][MAX])
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			playerArray[i][j] = "x";
		}
	}
	return;
}
void printBoard(string playerArray[][MAX])
{
	for (int i = 0; i < MAX; i++)
	{
		cout << (9-i) << " ";
		for (int j = 0; j < MAX; j++)
		{
			cout << playerArray[i][j] << " ";
		}
		cout << endl;
	}
	cout << "  ";
	for (int k = 0; k < MAX; k++)
	{
		cout << k << " ";
	}
	cout << endl;
	return;
}
void autoBoard(string playerArray[][MAX], int indexArray[][MAX], int index)
{
	int x, y, z;
	bool successful = false;

	for (int i = 1; i < 6; i++)
	{
		while (!successful)
		{
			x = rand() % MAX;
			y = rand() % MAX;
			if (i == 1)
			{
				z = 2;
			}
			else
			{
				z = rand() % 2;
			}
			successful = placeShip(i, x, y, z, playerArray);
		}
		indexArray[0][i - 1 + index] = x;
		indexArray[1][i - 1 + index] = y;
		indexArray[2][i - 1 + index] = z;
		successful = false;
	}
	return;
}
void manualInstruct()
{
	cout << "In this rendition of battleship, you have one ship each of size 1, 2, 3, 4, and 5." << endl;
	cout << "The ships can be placed anywhere on the grid provided they do not exceed the bounds, ";
	cout << "and must be orientated vertically or horizontally." << endl;
	cout << "Ships also cannot overlap, or occupy the same spot within the grid." << endl;
	cout << "Enter the x coordinate then y coordinate of the ships location. Both axes range from";
	cout << " values of 0 to 9.\nIf the ships length is greater than 1, you will be prompted on the ";
	cout << "orientation of the ship. Entering '1' will result in a vertical orientation and '0'";
	cout << "a horizontal one.\nThe initial coordinates will serve as the leftmost and bottommost";
	cout << "coordinate occupied by the ship, if applicable." << endl;
	cout << "Let's get started. Where would you like to place your ship of length 1?" << endl;
	return;
}
void autoInstruct()
{
	cout << "In this rendition of battleship, you have one ship each of size 1, 2, 3, 4, and 5." << endl;
	cout << "The ships can be placed anywhere on the grid provided they do not exceed the bounds, ";
	cout << "and must be orientated vertically or horizontally." << endl;
	cout << "Ships also cannot overlap, or occupy the same spot within the grid." << endl;
	cout << "The grid is a 10 by 10 area where you can place ships on any of the available spots." << endl;
	cout << "Your ship layout will now be automatically generated." << endl;
	return;
}
void input(int& twoOrOne, int& autoOrMan, string names[])
{
	cout << "Welcome to Battleship!" << endl;
	cout << "What is your name?" << endl;
	cin >> names[0];
	cout << "\nExcellent, will this be a 2 player game or a game versus AI?";
	cout << " Enter '1' or '0', for your selection, respectively." << endl;
	withinBounds(twoOrOne);
	if (twoOrOne == 1)
	{
		cout << "What is the second player's name?" << endl;
		cin >> names[1];
	}
	else
	{
		names[1] = "computer";
	}

	cout << "Now would you like to automatically set the player boards?";
	cout << " Enter '1' for yes and '0' for no." << endl;
	withinBounds(autoOrMan);
	return;
}
void withinBounds(int& check)
{
	cin >> check;
	while (!(check == 0 || check == 1))
	{
		cout << "That is an incorrect input, please try again." << endl;
		cin >> check;
	}
	return;
}

gameplay::gameplay(string inputp1[][MAX], string inputp2[][MAX], int twoOrOne, string pnames[], int positions[][MAX])
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			playerOneBoard[i][j] = inputp1[i][j];
			computerReference[i][j] = "x";
			playerTwoBoard[i][j] = inputp2[i][j];
			playerOneTarget[i][j] = "x";
			playerTwoTarget[i][j] = "x";
			if (i <= 2)
			{
				indexes[i][j] = positions[i][j];
			}
		}
	}
	choice = twoOrOne;
	names[0] = pnames[0];
	names[1] = pnames[1];
	srand(time(NULL));
}
void gameplay::playGame()
{
	cout << "Now we will begin the game.\n" << endl;
	cout << "Oh, by the way, did I ever mention there is a twist?" << endl;
	cout << "This is the equivalent of battleship hard mode- you will not be told ";
	cout << "If you have sunk a ship or not. Have fun!" << endl;
	if (choice == 1)
	{
		while (shipsLeft())
		{
			cout << "\nRound " << round << endl;
			if (round % 2 == 1)
			{
				cout << names[0] << "'s turn\n" << endl;
			}
			else
			{
				cout << names[1] << "'s turn\n" << endl;
			}
			printABoard();
			playerMove();
			shipSank();
			round++;
		}
	}
	else
	{
		while (shipsLeft())
		{
			cout << "\nRound " << round << endl;
			if (round % 2 == 1)
			{
				cout << names[0] << "'s turn\n" << endl;
				printABoard();
				playerMove();
				shipSank();
			}
			else
			{
				cout << "computer's turn\n" << endl;
				printABoard();
				computerMove();
				shipSank();
			}
			round++;
		}
	}
	if (winner() == 1)
	{
		cout << names[0] << " has won!" << endl;
	}
	else
	{
		cout << names[1] << " has won!" << endl;
	}
	return;
}
void gameplay::playerMove()
{
	int x, y;
	bool repeat = true;
	while (repeat)
	{
		cout << "What is the x coordinate of your target? (0-9)" << endl;
		cin >> x;
		outOfBounds(x);

		cout << "What is the y coordinate of your target? (0-9)" << endl;
		cin >> y;
		outOfBounds(y);

		if (round % 2 == 1)
		{
			if (playerTwoBoard[9 - y][x] == "o")
			{
				playerOneTarget[9 - y][x] = "h";
				playerTwoBoard[9 - y][x] = "h";
				cout << "Ship hit!" << endl;
				repeat = false;
			}
			else if (playerTwoBoard[9 - y][x] == "x")
			{
				playerOneTarget[9 - y][x] = "m";
				cout << "No ship hit." << endl;
				repeat = false;
			}
			else
			{
				cout << "You have already tried that location, try again." << endl;
			}
		}
		else
		{
			if (playerOneBoard[9 - y][x] == "o")
			{
				playerTwoTarget[9 - y][x] = "h";
				playerOneBoard[9 - y][x] = "h";
				cout << "Ship hit!" << endl;
				repeat = false;
			}
			else if (playerOneBoard[9 - y][x] == "x")
			{
				playerTwoTarget[9 - y][x] = "m";
				cout << "No ship hit." << endl;
				repeat = false;
			}
			else
			{
				cout << "You have already tried that location, try again." << endl;
			}
		}
	}
	return;
}
void gameplay::computerMove() //implement search feature when a hit is secured, otherwise look at possible
	//areas ships can fit in
{
	int x = 0, y = 0;
	int xhead = 0, yhead = 0;
	int counter = 0;
	int possiblePlaces[2][MAX];
	bool straightLine = true;
	bool checkhorz = true;
	bool checkvert = true;
	bool repeat = true;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			possiblePlaces[i][j] = -1;
		}
	}
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (playerOneBoard[i][j] == "h")
			{
				x = j;
				y = (9 - i);
				possiblePlaces[0][counter] = x;
				possiblePlaces[1][counter] = y;
				counter++;
			}
		}
	} // generally ships will be center, but if they are on edges will be parallel
	if (counter > 1)
	{
		for (int j = 0; j < counter - 1; j++)
		{
			if (possiblePlaces[0][j + 1] != -1 && possiblePlaces[1][j + 1] != -1)
			{
				if (!(possiblePlaces[0][j] == possiblePlaces[0][j + 1]))
				{
					checkvert = false;
				}
				if (!(possiblePlaces[1][j] == possiblePlaces[1][j + 1]))
				{
					checkhorz = false;
				}
			}
		}
		//find straight lines if possible and target ends of them
	}
	if (!checkhorz && !checkvert)
	{
		straightLine = false;
	}
	if (counter == 1)
	{
		if (x == 0 || x == 9)
		{
			if (y >= 5)
			{
				selector(1, -1, x, y);
			}
			else
			{
				selector(1, 1, x, y);
			}
		}
		else if (y == 0 || y == 9)
		{
			if (x >= 5)
			{
				selector(0, -1, x, y);
			}
			else
			{
				selector(0, 1, x, y);
			}
		}
		else
		{
			if (x >= 5)
			{
				if ((y == 4 || y == 5) && x == 5)
				{
					if (y == 5)
					{
						selector(1, -1, x, y);
					}
					else
					{
						selector(1, 1, x, y);
					}
				}
				else if (y >= 5)
				{
					if (x >= y)
					{
						selector(0, 1, x, y);
					}
					else
					{
						selector(1, 1, x, y);
					}

				}
				else
				{
					if (9 - x < y)
					{
						selector(0, 1, x, y);
					}
					else
					{
						selector(1, -1, x, y);
					}
				}
			}
			else
			{
				if ((y == 4 || y == 5) && x == 4)
				{
					if (y == 5)
					{
						selector(0, 1, x, y);
					}
					else
					{
						selector(0, 1, x, y);
					}
				}
				else if (y <= 4)
				{
					if (y <= x)
					{
						selector(1, -1, x, y);
					}
					else
					{
						selector(0, -1, x, y);
					}

				}
				else
				{
					if (x < 9 - y)
					{
						selector(0, -1, x, y);
					}
					else
					{
						selector(1, 1, x, y);
					}
				}
			}
		}
	}
	else if (counter > 1)
	{
		if (straightLine)
		{
			if (checkhorz)
			{
				xhead = possiblePlaces[0][0];
				for (int i = 1; i < counter; i++)
				{
					if (possiblePlaces[0][i] >= 0 && possiblePlaces[0][i] < xhead)
					{
						xhead = possiblePlaces[0][i];
					}
				}
				if (xhead > 0)
				{
					if (xhead <= MAX - xhead - counter)
					{
						selector(0, counter, xhead, y);
					}
					else
					{
						selector(0, -counter, xhead + counter - 1, y);
					}
				}
				else
				{
					selector(0, -counter, xhead + counter - 1, y);
				}
			}
			else
			{
				yhead = possiblePlaces[1][0];
				for (int i = 1; i < counter; i++)
				{
					if (possiblePlaces[1][i] >= 0 && possiblePlaces[1][i] < yhead)
					{
						yhead = possiblePlaces[1][i];
					}
				}
				if (yhead > 0)
				{
					if (yhead <= MAX - yhead - counter)
					{
						selector(0, counter, x, yhead);
					}
					else
					{
						selector(0, -counter, x, yhead + counter - 1);
					}
				}
				else
				{
					selector(0, -counter, x, yhead + counter - 1);
				}
			}
		}
		else
		{
			for (int i = 0; i < counter; i++)
			{
				while (repeat)
				{
					if (possiblePlaces[0][i] - 1 >= 0)
					{
						if (playerOneBoard[possiblePlaces[0][i] - 1][possiblePlaces[1][i]] == "x" ||
							playerOneBoard[possiblePlaces[0][i] - 1][possiblePlaces[1][i]] == "o")
						{
							selector(0, -1, possiblePlaces[0][i], possiblePlaces[1][i]);
							repeat = false;
						}
					}
					else if (possiblePlaces[0][i] + 1 < MAX)
					{
						if (playerOneBoard[possiblePlaces[0][i] + 1][possiblePlaces[1][i]] == "x" ||
							playerOneBoard[possiblePlaces[0][i] + 1][possiblePlaces[1][i]] == "o")
						{
							selector(0, 1, possiblePlaces[0][i], possiblePlaces[1][i]);
							repeat = false;
						}
					}
					else if (possiblePlaces[1][i] - 1 >= 0)
					{
						if (playerOneBoard[possiblePlaces[0][i]][possiblePlaces[1][i] - 1] == "x" ||
							playerOneBoard[possiblePlaces[0][i]][possiblePlaces[1][i] - 1] == "o")
						{
							selector(1, -1, possiblePlaces[0][i], possiblePlaces[1][i]);
							repeat = false;
						}
					}
					else if (possiblePlaces[1][i] + 1 < MAX)
					{
						if (playerOneBoard[possiblePlaces[0][i]][possiblePlaces[1][i] + 1] == "x" ||
							playerOneBoard[possiblePlaces[0][i]][possiblePlaces[1][i] + 1] == "o")
						{
							selector(1, 1, possiblePlaces[0][i], possiblePlaces[1][i]);
							repeat = false;
						}
					}
					else
					{
						cout << "uh oh" << endl;
					}
				}
			}
		}
	}
	else // when there is nothing there
	{
		x = rand() % 12;
		y = rand() % 12;
		if (x == 10)
		{
			x = 0;
		}
		else if (x == 11)
		{
			x = 9;
		}
		else
		{
			cout;
		}

		if (y == 10)
		{
			y = 0;
		}
		else if (y == 11)
		{
			y = 9;
		}
		else
		{
			cout;
		}
		selector(1, 0, x, y);
	}
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (playerTwoTarget[i][j] != computerReference[i][j])
			{
				computerReference[i][j] = playerTwoTarget[i][j];
				if (computerReference[i][j] == "m")
				{
					cout << "Computer targeted (" << j << ", " << (9 - i) << ") and missed" << endl;
				}
				else if (computerReference[i][j] == "h")
				{
					cout << "Computer targeted (" << j << ", " << (9 - i) << ") and hit a ship" << endl;
				}
				else
				{
					cout << "error" << endl;
				}
			}
		}
	}
	return;
}
void gameplay::shipSank() // uses the indexes list to compare 
{
	bool shipDestroyed; // make sure shipDestroyed is set to true after each loopo
	if (round % 2 == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			shipDestroyed = true;
			if (indexes[2][i] == 2)
			{
				if (playerOneTarget[9 - indexes[1][i]][indexes[0][i]] == "h")
				{
					playerTwoBoard[9 - indexes[1][i]][indexes[0][i]] == "s";
					playerOneTarget[9 - indexes[1][i]][indexes[0][i]] == "s";
					//computerReference[9 - indexes[1][i]][indexes[0][i]] == "s";
					cout << names[0] << "'s ship of length " << (i + 1) << " was sunk!\n\n" << endl;
				}
			}
			else if (indexes[2][i] == 1) // vertical orientation
			{
				for (int j = 0; j < i + 1; j++)
				{
					if (!(playerOneTarget[9 - indexes[1][i] - j][indexes[0][i]] == "h"))
					{
						shipDestroyed = false;
					}
				}
				if (shipDestroyed)
				{
					for (int k = 0; k < i; k++)
					{
						playerTwoBoard[9 - indexes[1][i] - k][indexes[0][i]] == "s";
						playerOneTarget[9 - indexes[1][i] - k][indexes[0][i]] == "s";
						//computerReference[9 - indexes[1][i] - k][indexes[0][i]] == "s";
						cout << names[0] << "'s ship of length " << (i + 1) << " was sunk!\n\n" << endl;
					}
				}
			}
			else
			{
				for (int j = 0; j < i + 1; j++)
				{
					if (!(playerOneTarget[9 - indexes[1][i]][indexes[0][i] + j] == "h"))
					{
						shipDestroyed = false;
					}
				}
				if (shipDestroyed)
				{
					for (int k = 0; k < i; k++)
					{
						playerTwoBoard[9 - indexes[1][i]][indexes[0][i] + k] == "s";
						playerOneTarget[9 - indexes[1][i]][indexes[0][i] + k] == "s";
						//computerReference[9 - indexes[1][i]][indexes[0][i] + k] == "s";
						cout << names[0] << "'s ship of length " << (i + 1) << " was sunk!\n\n" << endl;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 5; i < MAX; i++)
		{
			shipDestroyed = true;
			if (indexes[2][i] == 2)
			{
				if (playerTwoTarget[9 - indexes[1][i]][indexes[0][i]] == "h")
				{
					playerOneBoard[9 - indexes[1][i]][indexes[0][i]] == "s";
					playerTwoTarget[9 - indexes[1][i]][indexes[0][i]] == "s";
					cout << names[1] << "'s ship of length " << (i - 4) << " was sunk!\n\n" << endl;
				}
			}
			else if (indexes[2][i] == 1) // vertical orientation
			{
				for (int j = 0; j < i - 4; j++)
				{
					if (!(playerTwoTarget[9 - indexes[1][i] - j][indexes[0][i]] == "h"))
					{
						shipDestroyed = false;
					}
				}
				if (shipDestroyed)
				{
					for (int k = 0; k < i - 4; k++)
					{
						playerOneBoard[9 - indexes[1][i] - k][indexes[0][i]] == "s";
						playerTwoTarget[9 - indexes[1][i] - k][indexes[0][i]] == "s";
						cout << names[1] << "'s ship of length " << (i - 4) << " was sunk!\n\n" << endl;
					}
				}
			}
			else
			{
				for (int j = 0; j < i - 4; j++)
				{
					if (!(playerTwoTarget[9 - indexes[1][i]][indexes[0][i] + j] == "h"))
					{
						shipDestroyed = false;
					}
				}
				if (shipDestroyed)
				{
					for (int k = 0; k < i - 4; k++)
					{
						playerOneBoard[9 - indexes[1][i]][indexes[0][i] + k] == "s";
						playerTwoTarget[9 - indexes[1][i]][indexes[0][i] + k] == "s";
						cout << names[1] << "'s ship of length " << (i - 4) << " was sunk!\n\n" << endl;
					}
				}
			}
		}
	}
	return;
}
bool gameplay::shipsLeft()
{
	if (round % 2 == 1)
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (playerTwoBoard[i][j] == "o")
				{
					return true;
				}
			}
		}
		return false;
	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (playerOneBoard[i][j] == "o")
				{
					return true;
				}
			}
		}
		return false;
	}
}
void gameplay::outOfBounds(int& var)
{
	while (var < 0 || var > 9)
	{
		cout << "Please input a valid coordinate value." << endl;
		cin >> var;
	}
	return;
}
void gameplay::selector(int axis, int number, int x, int y)
{
	bool whole = true;
	bool parta = false;
	bool partb = false;
	bool repeat = true;
	while (whole)
	{
		if (number == 1 || number == -1)
		{
			if ((axis == 0 || parta) && !partb)
			{
				if (x + number < MAX)
				{
					if (playerOneBoard[9 - y][x + number] == "x")
					{
						playerTwoTarget[9 - y][x + number] = "m";
						playerOneBoard[9 - y][x + number] = "m";
						whole = false;
					}
					else if (playerOneBoard[9 - y][x + number] == "o")
					{
						playerTwoTarget[9 - y][x + number] = "h";
						playerOneBoard[9 - y][x + number] = "h";
						whole = false;
					}
					else if (x - number >= 0)
					{
						if (playerOneBoard[9 - y][x - number] == "x")
						{
							playerTwoTarget[9 - y][x - number] = "m";
							playerOneBoard[9 - y][x - number] = "m";
							whole = false;
						}
						else if (playerOneBoard[9 - y][x - number] == "o")
						{
							playerTwoTarget[9 - y][x - number] = "h";
							playerOneBoard[9 - y][x - number] = "h";
							whole = false;
						}
						else
						{
							partb = true;
						}
					}
					else
					{
						partb = true;
					}
				}
				else
				{
					partb = true;
				}
			}
			if ((axis == 1 || partb) && !parta)
			{
				if (y + number < MAX)
				{
					if (playerOneBoard[9 - y - number][x] == "x")
					{
						playerTwoTarget[9 - y - number][x] = "m";
						playerOneBoard[9 - y - number][x] = "m";
						whole = false;
					}
					else if (playerOneBoard[9 - y - number][x] == "o")
					{
						playerTwoTarget[9 - y - number][x] = "h";
						playerOneBoard[9 - y - number][x] = "h";
						whole = false;
					}
					else if (y - number >= 0)
					{
						if (playerOneBoard[9 - y + number][x] == "x")
						{
							playerTwoTarget[9 - y + number][x] = "m";
							playerOneBoard[9 - y + number][x] = "m";
							whole = false;
						}
						else if (playerOneBoard[9 - y + number][x] == "o")
						{
							playerTwoTarget[9 - y + number][x] = "h";
							playerOneBoard[9 - y + number][x] = "h";
							whole = false;
						}
						else
						{
							parta = true;
						}
					}
					else
					{
						parta = true;
					}
				}
				else
				{
					parta = true;
				}
			}
		}
		else if (number > 1)
		{
			if ((axis == 0 || parta) && !partb)
			{
				if (x - 1 >= 0)
				{
					if (playerOneBoard[9 - y][x - 1] == "x")
					{
						playerTwoTarget[9 - y][x - 1] = "m";
						playerOneBoard[9 - y][x - 1] = "m";
						whole = false;
					}
					else if (playerOneBoard[9 - y][x - 1] == "o")
					{
						playerTwoTarget[9 - y][x - 1] = "h";
						playerOneBoard[9 - y][x - 1] = "h";
						whole = false;
					}
					else
					{
						if (x + number - 1 < MAX)
						{
							if (playerOneBoard[9 - y][x + number - 1] == "x")
							{
								playerTwoTarget[9 - y][x + number - 1] = "m";
								playerOneBoard[9 - y][x + number - 1] = "m";
								whole = false;
							}
							else if (playerOneBoard[9 - y][x + number - 1] == "o")
							{
								playerTwoTarget[9 - y][x + number - 1] = "h";
								playerOneBoard[9 - y][x + number - 1] = "h";
								whole = false;
							}
							else
							{
								partb = true;
							}
						}
						else
						{
							partb = true;
						}
					}
				}
				else
				{
					if (x + number - 1 < MAX)
					{
						if (playerOneBoard[9 - y][x + number - 1] == "x")
						{
							playerTwoTarget[9 - y][x + number - 1] = "m";
							playerOneBoard[9 - y][x + number - 1] = "m";
							whole = false;
						}
						else if (playerOneBoard[9 - y][x + number - 1] == "o")
						{
							playerTwoTarget[9 - y][x + number - 1] = "h";
							playerOneBoard[9 - y][x + number - 1] = "h";
							whole = false;
						}
						else
						{
							partb = true;
						}
					}
					else
					{
						partb = true;
					}
				}
			}
			if ((axis == 1 || partb) && !parta)
			{
				if (y - 1 >= 0)
				{
					if (playerOneBoard[MAX - y][x] == "x")
					{
						playerTwoTarget[MAX - y][x] = "m";
						playerOneBoard[MAX - y][x] = "m";
						whole = false;
					}
					else if (playerOneBoard[MAX - y][x] == "o")
					{
						playerTwoTarget[MAX - y][x] = "h";
						playerOneBoard[MAX - y][x] = "h";
						whole = false;
					}
					else
					{
						if (y + number - 1 < MAX)
						{
							if (playerOneBoard[MAX - y - number][x] == "x")
							{
								playerTwoTarget[MAX - y - number][x] = "m";
								playerOneBoard[MAX - y - number][x] = "m";
								whole = false;
							}
							else if (playerOneBoard[MAX - y - number][x] == "o")
							{
								playerTwoTarget[MAX - y - number][x] = "h";
								playerOneBoard[MAX - y - number][x] = "h";
								whole = false;
							}
							else
							{
								parta = true;
							}
						}
						else
						{
							parta = true;
						}
					}
				}
				else
				{
					if (y + number - 1 < MAX)
					{
						if (playerOneBoard[MAX - y - number][x] == "x")
						{
							playerTwoTarget[MAX - y - number][x] = "m";
							playerOneBoard[MAX - y - number][x] = "m";
							whole = false;
						}
						else if (playerOneBoard[MAX - y - number][x] == "o")
						{
							playerTwoTarget[MAX - y - number][x] = "h";
							playerOneBoard[MAX - y - number][x] = "h";
							whole = false;
						}
						else
						{
							parta = true;
						}
					}
					else
					{
						parta = true;
					}
				}
			}
		}
		else if (number < -1)
		{
			if ((axis == 0 || parta) && !partb)
			{
				if (x + 1 < MAX)
				{
					if (playerOneBoard[9 - y][x + 1] == "x")
					{
						playerOneBoard[9 - y][x + 1] = "m";
						playerTwoTarget[9 - y][x + 1] = "m";
						whole = false;
					}
					else if (playerOneBoard[9 - y][x + 1] == "o")
					{
						playerTwoTarget[9 - y][x + 1] = "h";
						playerOneBoard[9 - y][x + 1] = "h";
						whole = false;
					}
					else
					{
						if (x + number >= 0)
						{
							if (playerOneBoard[9 - y][x + number] == "x")
							{
								playerTwoTarget[9 - y][x + number] = "m";
								playerOneBoard[9 - y][x + number] = "m";
								whole = false;
							}
							else if (playerOneBoard[9 - y][x + number] == "o")
							{
								playerTwoTarget[9 - y][x + number] = "h";
								playerOneBoard[9 - y][x + number] = "h";
								whole = false;
							}
							else
							{
								partb = true;
							}
						}
						else
						{
							partb = true;
						}
					}
				}
				else
				{
					if (x + number >= 0)
					{
						if (playerOneBoard[9 - y][x + number] == "x")
						{
							playerTwoTarget[9 - y][x + number] = "m";
							playerOneBoard[9 - y][x + number] = "m";
							whole = false;
						}
						else if (playerOneBoard[9 - y][x + number] == "o")
						{
							playerTwoTarget[9 - y][x + number] = "h";
							playerOneBoard[9 - y][x + number] = "h";
							whole = false;
						}
						else
						{
							partb = true;
						}
					}
					else
					{
						partb = true;
					}
				}
			}
			if ((axis == 1 || partb) && !parta)
			{
				if (y + 1 < MAX)
				{
					if (playerOneBoard[8 - y][x] == "x")
					{
						playerTwoTarget[8 - y][x] = "m";
						playerOneBoard[8 - y][x] = "m";
						whole = false;
					}
					else if (playerOneBoard[8 - y][x] == "o")
					{
						playerTwoTarget[8 - y][x] = "h";
						playerOneBoard[8 - y][x] = "h";
						whole = false;
					}
					else
					{
						if (y + number >= 0)
						{
							if (playerOneBoard[9 - y - number][x] == "x")
							{
								playerTwoTarget[9 - y - number][x] = "m";
								playerOneBoard[9 - y - number][x] = "m";
								whole = false;
							}
							else if (playerOneBoard[9 - y - number][x] == "o")
							{
								playerTwoTarget[9 - y - number][x] = "h";
								playerOneBoard[9 - y - number][x] = "h";
								whole = false;
							}
							else
							{
								parta = true;
							}
						}
						else
						{
							parta = true;
						}
					}
				}
				else
				{
					if (y + number >= 0)
					{
						if (playerOneBoard[9 - y - number][x] == "x")
						{
							playerTwoTarget[9 - y - number][x] = "m";
							playerOneBoard[9 - y - number][x] = "m";
							whole = false;
						}
						else if (playerOneBoard[9 - y - number][x] == "o")
						{
							playerTwoTarget[9 - y - number][x] = "h";
							playerOneBoard[9 - y - number][x] = "h";
							whole = false;
						}
						else
						{
							parta = true;
						}
					}
					else
					{
						parta = true;
					}
				}
			}
		}
		else
		{
			if (playerOneBoard[9 - y][x] == "x")
			{
				playerTwoTarget[9 - y][x] = "m";
				playerOneBoard[9 - y][x] = "m";
			}
			else if (playerOneBoard[9 - y][x] == "o")
			{
				playerTwoTarget[9 - y][x] = "h";
				playerOneBoard[9 - y][x] = "h";
			}
			else
			{
				while (repeat)
				{
					x = rand() % 12;
					y = rand() % 12;
					if (x == 10)
					{
						x = 0;
					}
					else if (x == 11)
					{
						x = 9;
					}
					else
					{
						cout;
					}

					if (y == 10)
					{
						y = 0;
					}
					else if (y == 11)
					{
						y = 9;
					}
					else
					{
						cout;
					}
					if (x >= 0 && x < MAX && y>= 0 && y < MAX)
					{
						if (playerOneBoard[9 - y][x] == "x")
						{
							playerTwoTarget[9 - y][x] = "m";
							playerOneBoard[9 - y][x] = "m";
							repeat = false;
						}
						else if (playerOneBoard[9 - y][x] == "o")
						{
							playerTwoTarget[9 - y][x] = "h";
							playerOneBoard[9 - y][x] = "h";
							repeat = false;
						}
					}
				}
			}
			whole = false;
		}

	}
	return;
}
int gameplay::winner()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (playerOneBoard[i][j] == "o")
			{
				return 1;
			}
		}
	}
	return 0;
}
void gameplay::printABoard()
{
		for (int i = 0; i < MAX; i++)
		{
			cout << (9-i) << " ";
			for (int j = 0; j < MAX; j++)
			{
				if (round % 2 == 1)
				{
					cout << playerOneTarget[i][j] << " ";
				}
				else
				{
					cout << playerTwoTarget[i][j] << " ";
				}
			}
			cout << endl;
		}
		cout << "  ";
		for (int k = 0; k < MAX; k++)
		{
			cout << k << " ";
		}
		cout << endl;
}