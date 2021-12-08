#include <iostream>
#include <windows.h>
#include <random>
#include <ctime>

using namespace std;

//Dummy functions:

//Used for repetition of game
int main2(int& playerOneWins, int& playerTwoWins, int& ties);
//Drawing the board
int DrawBoard(char spaces[7][6], int color[7][6]);
//Randomizing which player goes first
int SelectPlayer();
//Welcome message
int Welcome();
//Fills given arrays with spaces and zeros respectively
int EmptyBoard(char(&spaces)[7][6], int(&color)[7][6]);
//Plays the game
int Play(char(&spaces)[7][6], int(&color)[7][6], int player, int playerOneWins, int playerTwoWins, int ties, int choice);
//Checks a column for empty space and fills it
int CheckColumn(char(&spaces)[7][6], int(&color)[7][6], int column, int player);
//Switches from player 1 to 2 or 2 to 1
int SwitchPlayers(int& player);
//Checks for winning condition
int CheckForWin(int(&color)[7][6]);
//Sub-function used by CheckForWin
int CheckPlaceForWin(int(&color)[7][6], int x, int y);
//"Play again?" prompt
int PlayAgain(int& playerOneWins, int& playerTwoWins, int& ties);
//Used for testing tying
int PopulateTieMoves(int(&tieMoves)[42]);
//Used for animation of falling tiles
void Animate(int color, int xToAnimate, int yValue, char spaces[7][6], int colors[7][6]);

int main()
{
	//Win vars, no global variables :(
	int playerOneWins = 0, playerTwoWins = 0, ties = 0;
	//Calls the repeatable function
	main2(playerOneWins, playerTwoWins, ties);
}

int main2(int& playerOneWins, int& playerTwoWins, int& ties)
{
	//Array for storing the pieces
	char spaces[7][6];
	//Array that stores integer values for every space which will represent its color
	int color[7][6];
	//Selects player and welcomes
	int player = Welcome();
	//Clears board
	EmptyBoard(spaces, color);
	//Draws initial (blank) board
	DrawBoard(spaces, color);
	//Starts the game
	Play(spaces, color, player, playerOneWins, playerTwoWins, ties, 16);
	//Mandatory return
	return(0);
}

int DrawBoard(char spaces[7][6], int color[7][6])
{
	//Sets default color to white
	int localColor = 15;
	cout << endl;
	//Prints 1 - 7 above the board
	for (int a = 1; a <= 7; a++)
	{
		cout << "  " << a << " ";
	}
	//Sets color to blye to print board
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << endl << "-----------------------------" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int y = 0; y < 6; y++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "| ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int x = 0; x < 7; x++)
		{
			//Sets color based on which player made the move
			if (color[x][y] == 1)
			{
				localColor = 12;
			}
			else if (color[x][y] == 2)
			{
				localColor = 14;
			}
			else if (color[x][y] == 10)
			{
				localColor = 10;
			}
			//Sets color to output player piece
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
			cout << spaces[x][y];
			//Sets color to draw board
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << " | ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		//Sets color to draw board
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << endl << "-----------------------------" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	return(0);
}

int SelectPlayer()
{
	//Selects either player one or two
	srand(time(NULL));
	return(rand() % 2 + 1);
}

int Welcome()
{
	int localColor = 14;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//Introduction
	cout << "                        Welcome to Connect4                               " << endl;
	cout << "Win by getting four piece in a row diagonally, horizontally, or veritcally" << endl;
	//Selects player
	int player = SelectPlayer();
	//Sets local color
	if (player == 1)
	{
		localColor = 12;
	}
	//Outputs which player is first
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << endl << "Player ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
	cout << player;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " has been selected to go first." << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


	return(player);
}

int EmptyBoard(char(&spaces)[7][6], int(&color)[7][6])
{
	//Y for
	for (int y = 0; y < 6; y++)
	{
		//X for
		for (int x = 0; x < 7; x++)
		{
			//Fills board with spaces
			spaces[x][y] = ' ';
			color[x][y] = 0;
		}
	}
	return(0);
}

void Animate(int color, int xToAnimate, int yValue, char spaces[7][6], int colors[7][6])
{
	char animateArray[7][6];
	int animateColorArray[7][6];
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			animateArray[x][y] = spaces[x][y];
			animateColorArray[x][y] = colors[x][y];
		}
	}

	animateArray[xToAnimate][yValue] = 'O';
	animateColorArray[xToAnimate][yValue] = color;
	//Sets default color to white
	int localColor = 15;
	cout << endl;
	//Prints 1 - 7 above the board
	for (int a = 1; a <= 7; a++)
	{
		cout << "  " << a << " ";
	}
	//Sets color to gray to print board
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << endl << "-----------------------------" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int y = 0; y < 6; y++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "| ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int x = 0; x < 7; x++)
		{
			//Sets color based on which player made the move
			if (animateColorArray[x][y] == 1)
			{
				localColor = 12;
			}
			else if (animateColorArray[x][y] == 2)
			{
				localColor = 14;
			}
			//Sets color to output player piece
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
			cout << animateArray[x][y];
			//Sets color to draw board
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << " | ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		//Sets color to draw board
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << endl << "-----------------------------" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}

int Play(char(&spaces)[7][6], int(&color)[7][6], int player, int playerOneWins, int playerTwoWins, int ties, int tieVar)
{
	//Array used for storing tying moves
	int tieMoves[42];
	//Vars
	int choice, moves = 0, localColor = 15;
	bool validChoice = false, goodChoice, win = false, tie = true;
	//Move set for testing tying
	PopulateTieMoves(tieMoves);
	do
	{
		//Sets local color for player text
		if (player == 1)
		{
			localColor = 12;
		}
		else
		{
			localColor = 14;
		}
		//First run (main sends a 16)
		if (tieVar == 16)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
			cout << "\nPlayer #" << player << "'s";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << " turn. " << "Choose a column (1-7):\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cin >> choice;
		}
		//Used for tie test
		else
		{
			choice = 16;
		}
		do
		{
			//Takes user input
			//If the user wants to test the tie, set that up
			if (choice == 16)
			{
				tieVar = 15;
			}
			//If the user wanted to tie, that happens here,
			//choice is set to a certain move set
			if (choice == 16 && tieVar != 16)
			{
				choice = tieMoves[moves];
			}
			//Checks if input is out of bounds
			if ((choice > 7 || choice < 1) && choice != 16)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << endl << "Invalid move, ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
				cout << "Player #" << player;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << ", choose a column (1-7):\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				validChoice = false;
			}

			else
			{
				//Stops loop
				validChoice = true;
			}
		} while (validChoice == false);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//Checks for which column slot to fill, and fills it
		goodChoice = CheckColumn(spaces, color, choice, player);
		if (goodChoice == false)
		{
			//Informs user of their error
			cout << "\nYou attempted to fill a column that is full. You lose your turn!\n";
			DrawBoard(spaces, color);
			SwitchPlayers(player);
		}
		else
		{
			//Adds to move count
			moves++;
			//Win is only possible after the seventh move
			if (moves >= 7)
			{
				//Checks for win, returns a boolean value
				win = CheckForWin(color);
				if (win == true)
				{
					//Draws board with green tiles
					DrawBoard(spaces, color);
					if (player == 1)
					{
						localColor = 12;
						playerOneWins++;
					}
					else
					{
						localColor = 14;
						playerTwoWins++;
					}
					//Outputs winner
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), localColor);
					cout << "Player " << player << " wins!";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					PlayAgain(playerOneWins, playerTwoWins, ties);
				}
			}
			//Redraws board and switches players
			DrawBoard(spaces, color);
			SwitchPlayers(player);
		}


		//Only goes to 42 moves (maximum)
	} while (moves < 42);

	//Adds to ties
	ties++;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Tie!";
	PlayAgain(playerOneWins, playerTwoWins, ties);
	return(0);

}

int CheckColumn(char(&spaces)[7][6], int(&color)[7][6], int column, int player)
{
	for (int i = 6; i >= 1; i--)
	{
		//Checks if selected column has an empty space
		if (spaces[column - 1][i - 1] == ' ')
		{
			int xAnimate = (column - 1);
			int yValue = i - 1;
			for (int yPass = 0; yPass < yValue; yPass++)
			{
				system("CLS");
				cout << flush;
				Animate(player, xAnimate, yPass, spaces, color);
				Sleep(125);
				system("CLS");
				cout << flush;
			}
			color[column - 1][i - 1] = player;
			spaces[column - 1][i - 1] = 'O';
			return(true);
		}
	}
	return(false);
}

int SwitchPlayers(int& player)
{
	//1 to 2 and 2 to 1
	switch (player)
	{
	case 1:
		player = 2;
		break;
	case 2:
		player = 1;
		break;
	}
	return(0);
}

int CheckForWin(int(&color)[7][6])
{
	//Default so that loop starts
	bool win = false;
	//Y for loop
	for (int y = 0; y < 6; y++)
	{
		//X for loop
		for (int x = 0; x < 7; x++)
		{
			//If the tile has been changed
			if (color[x][y] == 1 || color[x][y] == 2)
			{
				win = CheckPlaceForWin(color, x, y);
				if (win == true)
				{
					return(true);
				}
			}
		}
	}
	return(0);
}
int CheckPlaceForWin(int(&color)[7][6], int x, int y)
{
	//Var used to track which tests have been completed
	int testNumber = 1;
	while (testNumber <= 8)
	{
		switch (testNumber)
		{
		case 1:
			//Checks for out-of-bounds errors
			if (x + 3 <= 0 || y - 3 <= 0)
			{
				break;
			}
			// Vertical UP
			if (color[x][y] == color[x][y - 1] && color[x][y - 1] == color[x][y - 2] && color[x][y - 2] == color[x][y - 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x][y - 1] = 10;
				color[x][y - 2] = 10;
				color[x][y - 3] = 10;
				return(true);
			}
			break;
		case 2:
			//Checks for out-of-bounds errors
			if (x + 3 >= 7 || y - 3 <= 0)
			{
				break;
			}
			// Diagonal UP RIGHT
			if (color[x][y] == color[x + 1][y - 1] && color[x + 1][y - 1] == color[x + 2][y - 2] && color[x + 2][y - 2] == color[x + 3][y - 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x + 1][y - 1] = 10;
				color[x + 2][y - 2] = 10;
				color[x + 3][y - 3] = 10;
				return(true);
			}
			break;
		case 3:
			//Checks for out-of-bounds errors
			if (x + 3 >= 7)
			{
				break;
			}
			// Horizontal RIGHT
			if (color[x][y] == color[x + 1][y] && color[x + 1][y] == color[x + 2][y] && color[x + 2][y] == color[x + 3][y])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x + 1][y] = 10;
				color[x + 2][y] = 10;
				color[x + 3][y] = 10;
				return(true);
			}
			break;
		case 4:
			//Checks for out-of-bounds errors
			if (x + 3 >= 7 || y + 3 >= 6)
			{
				break;
			}
			// Diagonal DOWN RIGHT
			if (color[x][y] == color[x + 1][y + 1] && color[x + 1][y + 1] == color[x + 2][y + 2] && color[x + 2][y + 2] == color[x + 3][y + 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x + 1][y + 1] = 10;
				color[x + 2][y + 2] = 10;
				color[x + 3][y + 3] = 10;
				return(true);
			}
			break;
		case 5:
			//Checks for out-of-bounds errors
			if (y + 3 >= 6)
			{
				break;
			}
			// Vertical DOWN
			if (color[x][y] == color[x][y + 1] && color[x][y + 1] == color[x][y + 2] && color[x][y + 2] == color[x][y + 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x][y + 1] = 10;
				color[x][y + 2] = 10;
				color[x][y + 3] = 10;
				return(true);
			}
			break;
		case 6:
			//Checks for out-of-bounds errors
			if (x - 3 <= 0 || y + 3 >= 6)
			{
				break;
			}
			// Diagonal DOWN LEFT
			if (color[x][y] == color[x - 1][y + 1] && color[x - 1][y + 1] == color[x - 2][y + 2] && color[x - 2][y + 2] == color[x - 3][y + 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x - 1][y + 1] = 10;
				color[x - 2][y + 2] = 10;
				color[x - 3][y + 3] = 10;
				return(true);
			}
			break;
		case 7:
			//Checks for out-of-bounds errors
			if (x - 3 <= 0)
			{
				break;
			}
			// Horizontal LEFT
			if (color[x][y] == color[x - 1][y] && color[x - 1][y] == color[x - 2][y] && color[x - 2][y] == color[x - 3][y])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x - 1][y] = 10;
				color[x - 2][y] = 10;
				color[x - 3][y] = 10;
				return(true);
			}
			break;
		case 8:
			//Checks for out-of-bounds errors
			if (x - 3 <= 0 || y - 3 <= 0)
			{
				break;
			}
			// Diagonal UP LEFT
			if (color[x][y] == color[x - 1][y - 1] && color[x - 1][y - 1] == color[x - 2][y - 2] && color[x - 2][y - 2] == color[x - 3][y - 3])
			{
				//Player has won, set the color of the tiles to green
				color[x][y] = 10;
				color[x - 1][y - 1] = 10;
				color[x - 2][y - 2] = 10;
				color[x - 3][y - 3] = 10;
				return(true);
			}
			break;
		}
		//Moves to the next test
		testNumber++;
	}
	return(false);
}

int PlayAgain(int& playerOneWins, int& playerTwoWins, int& ties)
{
	//String for input
	string playAgain;
	cout << "\n\nPlay again? (Y/N)\n";
	//Sets color to green for input
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cin >> playAgain;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (playAgain == "Yes" || playAgain == "yes" || playAgain == "Y" || playAgain == "y")
	{
		//Calls game to start again
		main2(playerOneWins, playerTwoWins, ties);
	}
	else
	{
		//Vars for correct grammar
		string extraCharOne = "", extraCharTwo = "", extraCharTies = "", tieGrammar;
		if (playerOneWins > 1 || playerOneWins == 0)
		{
			extraCharOne = "s";
		}
		if (playerTwoWins > 1 || playerTwoWins == 0)
		{
			extraCharTwo = "s";
		}
		if (ties > 1 || ties == 0)
		{
			extraCharTies = "s";
			tieGrammar = "were ";
		}
		else
		{
			tieGrammar = "was ";
		}
		//Outputs wins of both players and ties
		cout << "Player one won " << playerOneWins << " time" << extraCharOne << ". Player two won " << playerTwoWins << " time" << extraCharTwo << ". There " << tieGrammar << ties << " tie" << extraCharTies << "." << endl;

		//Used so that compiler does not dump text in debug mode
		int x = 0;
		while (x != -1)
		{
			cout << "\n\r";
			cin >> x;
		}
	}
	return(0);
}

int PopulateTieMoves(int(&tieMoves)[42])
{
	//First six moves column 1
	for (int i = 0; i < 6; i++)
	{
		tieMoves[i] = 1;
	}
	//Next 6 column 3
	for (int i = 6; i < 12; i++)
	{
		tieMoves[i] = 3;
	}
	//Next 6 column 5
	for (int i = 12; i < 18; i++)
	{
		tieMoves[i] = 5;
	}
	//Next 6 column 7
	for (int i = 18; i < 24; i++)
	{
		tieMoves[i] = 7;
	}
	//Last 18 are sets of {2, 4, 6} repeated
	for (int i = 24; i < 42; i++)
	{
		if (tieMoves[i - 1] == 7 || tieMoves[i - 1] == 6)
		{
			tieMoves[i] = 2;
		}
		else if (tieMoves[i - 1] == 2)
		{
			tieMoves[i] = 4;
		}
		else if (tieMoves[i - 1] == 4)
		{
			tieMoves[i] = 6;
		}
	}
	return (0);
}