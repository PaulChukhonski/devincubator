#include <iostream>
using namespace std;
#define SIDE 3
#define SIZE SIDE*SIDE
#define STR "|"
#define X 'X'
#define O 'O'
#define EMPTY '-'
#define CONVERT '0'
#define SIDE_CASES_NUM '3'
#define TURN_CASES_NUM '3'
#define MAIN_CASES_NUM '4'

void initializeGameField(char cells[]);
void initializeNumeratedField(char cells[]);
void showField(char cells[]);
void showAllFields(char cells[], char numeratedCells[]);
string inputPosition(string str, bool isPlayerX);
bool isCorrectInput(string str, char last);
int strToInt(string str);
bool isCanPlay(char cells[]);
bool isCellEmpty(char cells[], int pos);
void swap(char cells[], int pos, char symbol);
char scanTheFieldToGetWinner(char cells[]);
char scanTheRows(char cells[], char symbol, bool flag);
char scanTheColumns(char cells[], char symbol, bool flag);
char scanTheDiagonals(char cells[], char symbol, int flag);
int compare(char cell, char symbol);
char checkWinner(char winner, int countX, int countO, int amount);
char scanTheField(char cells[], char symbol);
char checkPreWinner(char preWinner, int countX, int countO, int countEmpty, int index);
char logicRandom(char cells[], char symbol, int i);
char chooseRandomCell(char cells[], char symbol);
void showMainMenu(int priority, bool isPlayerX);
void showSideMenu(bool isPlayerX);
void showTurnMenu(int priority);
string getChoice();
void showCurrentTurn(int priority);
void showCurrentSide(bool isPlayerX);
int convertAndCheckChoice(string str, char last, int sideChoice);

int main()
{
	char gameCells[SIZE] = {}; 
    char numeratedCells[SIZE] = {};		
    string str;
	int priority = 1, pos, mainChoice, sideChoice, turnChoice;
	bool isPlayerX = true, mainMenu = true, sideMenu, turnMenu, playMenu;
	char playerSymbol, pcSymbol;
	
	while(mainMenu)
	{	
		showMainMenu(priority, isPlayerX);
		str = getChoice();
		mainChoice = convertAndCheckChoice(str, MAIN_CASES_NUM, -1);	

		switch(mainChoice)
		{
			case 1:
				sideMenu = true;
				
				while(sideMenu)
				{
					showSideMenu(isPlayerX);
					str = getChoice();
					sideChoice = convertAndCheckChoice(str, SIDE_CASES_NUM, -1);	
					
					switch(sideChoice)
					{
						case 1:
							isPlayerX = true;
							sideMenu = false;
							break;
						case 2:
							isPlayerX = false;
							sideMenu = false;
							break;
						case 3:
							sideMenu = false;
							break;			
						default:
							cout << "Incorrect input. Enter number 1..." << SIDE_CASES_NUM << "!" << endl;
							system("pause");
							break;	
					}					
				}
								
				break;
			case 2:
				turnMenu = true;
									
				while(turnMenu)
				{
					showTurnMenu(priority);
					str = getChoice();
					turnChoice = convertAndCheckChoice(str, TURN_CASES_NUM, -1);					
					
					switch(turnChoice)
					{
						case 1:
							priority = 1;
							turnMenu = false;
							break;
						case 2:
							priority = 2;
							turnMenu = false;
							break;
						case 3:
							turnMenu = false;
							break;			
						default:
							cout << "Incorrect input. Enter number 1..." << TURN_CASES_NUM << "!" << endl;
							system("pause");
							break;	
					}					
				}
				
				break;
			case 3:
				initializeGameField(gameCells);
				initializeNumeratedField(numeratedCells);	
				showAllFields(gameCells, numeratedCells);
				
				if(isPlayerX)
				{
					playerSymbol = X;
					pcSymbol = O;
				}
				else
				{
					playerSymbol = O;
					pcSymbol = X;
				}	
				
			    while(isCanPlay(gameCells))
			    {	
					if(priority % 2 == 1)
					{	
				    	str = inputPosition(str, isPlayerX);
				    	
				    	if(!isCorrectInput(str, numeratedCells[SIZE-1]))
				    	{
				    		cout << "No such field! Please, choose correct field."	<< endl;
							system("pause");	
						}
						else
						{
							pos = strToInt(str) - 1;
							
							if(isCellEmpty(gameCells, pos))
							{
								swap(gameCells, pos, playerSymbol);
								priority++;			
							}
							else
							{
								cout << "Field isn't empty! Please, choose an empty field."	<< endl;
								system("pause");
							}			
						}
						
						showAllFields(gameCells, numeratedCells);
						
						if(scanTheFieldToGetWinner(gameCells) != EMPTY)
						{
							break;
						}		
					}
					
					if(priority % 2 == 0)
					{
						if(scanTheField(gameCells, pcSymbol) != pcSymbol)
						{
							pos = scanTheField(gameCells, pcSymbol) - CONVERT;
						}
						else if(scanTheField(gameCells, playerSymbol) != playerSymbol)
						{
							pos = scanTheField(gameCells, playerSymbol) - CONVERT;
						}	
						else if(scanTheDiagonals(gameCells, pcSymbol, 2) != pcSymbol)
						{
							pos = scanTheDiagonals(gameCells, pcSymbol, 2) - CONVERT;
						}											
						else if(chooseRandomCell(gameCells, EMPTY) != EMPTY)
						{
							pos = chooseRandomCell(gameCells, EMPTY) - CONVERT;
						}
			
						if(isCellEmpty(gameCells, pos))
						{
							swap(gameCells, pos, pcSymbol);						
							priority++;	
							showAllFields(gameCells, numeratedCells);							
						}			
						
						if(scanTheFieldToGetWinner(gameCells) != EMPTY)
						{
							break;
						}			
					}	
				}	
				
				if(scanTheFieldToGetWinner(gameCells) == EMPTY)
				{
					cout << "Draw!"	<< endl;
				}
				else
				{
					cout << "Won " << scanTheFieldToGetWinner(gameCells) << "!" << endl;
				}
				
				priority = 1;
				isPlayerX = true;
				
				system("pause");
				
				break;
			case 4:
				mainMenu = false;
				break;			
			default:
				cout << "Incorrect input. Enter number 1..." << MAIN_CASES_NUM << "!" << endl;
				system("pause");
				break;	
		}	
	}
		
	return 0;
}

void initializeGameField(char cells[])
{
	for(int i = 0; i < SIZE; i++)
	{
		cells[i] = EMPTY;
	}	
}

void initializeNumeratedField(char cells[])
{
	for(int i = 0; i < SIZE; i++)
	{
		cells[i] = i + 1 + CONVERT;
	}	
}

void showField(char cells[])
{
	for(int i = 0; i < SIZE; i++)
	{
		cout << cells[i] << STR;
			
		if(i % SIDE == SIDE-1)	
		{
			cout << endl;	
		}
	}	
}

void showAllFields(char cells[], char numeratedCells[])
{
	system("cls");
    cout << "Position numbers!" << endl;
	showField(numeratedCells);
	cout << "Game field!" << endl;
    showField(cells);	
}

string inputPosition(string str, bool isPlayerX)
{	
	if(isPlayerX)
	{
		cout << "Enter a position number you want to mark with X: ";
		cin >> str;
	}
	else
	{
		cout << "Enter a position number you want to mark with O: ";
		cin >> str;
	}	

	return str;
}

bool isCorrectInput(string str, char last)
{
	return str[0] >= '1' && str[0] <= last && str.length() == 1;
}

int strToInt(string str)
{
	return str[0] - CONVERT;					
}

bool isCanPlay(char cells[])
{
	bool check = false;
	
	for(int i = 0; i < SIZE; i++)
	{
		if(cells[i] == EMPTY)	
		{
			check = true;
		}
	}
	
	return check;
}

bool isCellEmpty(char cells[], int pos)
{
	return cells[pos] == EMPTY;
}

void swap(char cells[], int pos, char symbol)
{
	cells[pos] = symbol;
}

char scanTheFieldToGetWinner(char cells[])
{
	char winner = EMPTY;
	
	if(winner == EMPTY)	
	{
		winner = scanTheRows(cells, winner, false);
	}
	
	if(winner == EMPTY)	
	{
		winner = scanTheColumns(cells, winner, false);
	}
	
	if(winner == EMPTY)	
	{
		winner = scanTheDiagonals(cells, winner, 0);		
	}

	return winner;
}

char scanTheRows(char cells[], char symbol, bool flag)
{
	int start, end, step, countX, countO, countEmpty, pos;
	char custom = symbol;
	
	end = SIDE;
	countX = 0, countO = 0, countEmpty = 0, pos = -1;
		
	for(start = 0; start < SIZE; start += SIDE)
	{
		for(int j = start; j < end; j++)
		{
			countX += compare(cells[j], X);
			countO += compare(cells[j], O);	
			countEmpty += compare(cells[j], EMPTY);	
			
			if(flag && countEmpty == 1 && compare(cells[j], EMPTY) == 1)
			{			
				pos = j;					
			}				
		}
		
		if(flag)
		{			
			symbol = checkPreWinner(symbol, countX, countO, countEmpty, pos);				
			
			if(symbol != custom)
			{
				break;	
			}	
		}
		
		if(!flag)
		{
			symbol = checkWinner(symbol, countX, countO, SIDE);	
		}
		
		countX = 0, countO = 0, countEmpty = 0, pos = -1;
		end += SIDE;
	}
		
	return symbol;
}

char scanTheColumns(char cells[], char symbol, bool flag)
{
	int start, end, step, countX, countO, countEmpty, pos;
	char custom = symbol;
	
	end = SIZE - SIDE;
	countX = 0, countO = 0, countEmpty = 0, pos = -1;
	
	for(start = 0; start < SIDE; start++)
	{
		for(int j = start; j <= end; j += SIDE)
		{
			countX += compare(cells[j], X);
			countO += compare(cells[j], O);	
			countEmpty += compare(cells[j], EMPTY);	
			
			if(flag && countEmpty == 1 && compare(cells[j], EMPTY) == 1)
			{			
				pos = j;					
			}			
		}
		
		if(flag)
		{			
			symbol = checkPreWinner(symbol, countX, countO, countEmpty, pos);					
			
			if(symbol != custom)
			{
				break;	
			}	
		}
		
		if(!flag)
		{
			symbol = checkWinner(symbol, countX, countO, SIDE);	
		}	
		
		countX = 0, countO = 0, countEmpty = 0, pos = -1;
		end++;
	}
		
	return symbol;
}

char scanTheDiagonals(char cells[], char symbol, int flag)
{
	int start, end, step, countX, countO, countEmpty, pos;
	char custom = symbol, symbolX = EMPTY, symbolO = EMPTY;
	
	end = SIZE, step = SIDE+1;
	countX = 0, countO = 0, countEmpty = 0, pos = -1;

	for(start = 0; start < SIDE; start += SIDE-1)
	{
		for(int j = start; j < end; j += step)
		{
			countX += compare(cells[j], X);
			countO += compare(cells[j], O);	
			countEmpty += compare(cells[j], EMPTY);	

			if(flag == 1 && countEmpty == 1 && compare(cells[j], EMPTY) == 1)
			{			
				pos = j;					
			}
			
			if(flag == 2 && SIDE == 3)
			{	
			 	if(custom == X)
			 	{
			 		symbolX = custom;
				}
			 	
				if(custom == O)
			 	{
			 		symbolO = custom;
				}	
				
				if((compare(cells[(SIZE-1)/2], symbolX) == 1 && countX == 1 && countO == SIDE-1) || (compare(cells[(SIZE-1)/2], symbolO) == 1 && countO == 1  && countX == SIDE-1))		
				{
					pos = j-1;
				}						
			}			
		}	
		
		if(flag == 0)
		{
			symbol = checkWinner(symbol, countX, countO, SIDE);	
		}		
		
		if(flag == 1)
		{			
			symbol = checkPreWinner(symbol, countX, countO, countEmpty, pos);					
			
			if(symbol != custom)
			{
				break;	
			}	
		}	
	
		if(flag == 2 && pos != -1)
		{			
			symbol = pos + CONVERT;					
			
			if(symbol != custom)
			{
				break;	
			}	
		}	

		countX = 0, countO = 0, countEmpty = 0, pos = -1;
		step = SIDE-1;
		end -= SIDE-1;
	}
		
	return symbol;
}

int compare(char cell, char symbol)
{
	int count = 0;
	
	if(cell == symbol)
	{
		count = 1;
	}
	
	return count;
}

char checkWinner(char winner, int countX, int countO, int amount)
{	
	if(countX == amount)
	{
		winner = X;
	}
	else if(countO == amount)
	{
		winner = O;
	}
		
	return winner;
}

char scanTheField(char cells[], char symbol)
{	
	char custom = symbol;

	if(symbol == custom)
	{
		symbol = scanTheRows(cells, symbol, true);
	}
	
	if(symbol == custom)
	{
		symbol = scanTheColumns(cells, symbol, true);
	}	
	
	if(symbol == custom)
	{
		symbol = scanTheDiagonals(cells, symbol, 1);
	}	
	
	return symbol;
}

char checkPreWinner(char preWinner, int countX, int countO, int countEmpty, int index)
{	
 	char symbolX = EMPTY, symbolO = EMPTY;
 	
 	if(preWinner == X)
 	{
 		symbolX = preWinner;
	}
 	
	if(preWinner == O)
 	{
 		symbolO = preWinner;
	}
	
	if(countEmpty == 1)
	{		
		if(countX == SIDE-1 && symbolX != EMPTY)
		{
			preWinner = index + CONVERT;
		}
		
		if(countO == SIDE-1 && symbolO != EMPTY)
		{
			preWinner = index + CONVERT;
		}
	}
	
	return preWinner;
}

char logicRandom(char cells[], char symbol, int i)
{	
	for(; i < SIZE; i += 2)
	{		
		if(cells[i] == EMPTY)
		{
			symbol = i + CONVERT;
			break;
		}
	}	
	
	return symbol;
}

char chooseRandomCell(char cells[], char symbol)
{
	if(symbol == EMPTY && SIDE % 2 == 1)
	{
		if(cells[(SIZE-1)/2] == EMPTY)
		{
			symbol = (SIZE-1)/2 + CONVERT; 
		}
	}
	
	if(symbol == EMPTY)
	{
		symbol = logicRandom(cells, symbol, 0);
	}
	
	if(symbol == EMPTY)
	{
		symbol = logicRandom(cells, symbol, 1);
	}
	
	return symbol;
}

void showMainMenu(int priority, bool isPlayerX)
{
	system("cls");
	cout << "Tic Tac Toe " << endl;
	cout << "----------------------" << endl;
	showCurrentTurn(priority);
	showCurrentSide(isPlayerX);
	cout << "----------------------" << endl;
	cout << "1. Choose side" << endl;
	cout << "2. Choose turn" << endl;	
	cout << "3. Play" << endl;
	cout << "4. Exit" << endl;	
}

void showSideMenu(bool isPlayerX)
{
	system("cls");
	cout << "Choose side: " << endl;
	cout << "----------------" << endl;
	showCurrentSide(isPlayerX);
	cout << "----------------" << endl;
	cout << "1. X" << endl;
	cout << "2. O" << endl;
	cout << "3. Back" << endl;
}

void showTurnMenu(int priority)
{
	system("cls");
	cout << "Choose turn" << endl;
	cout << "----------------------" << endl;
	showCurrentTurn(priority);
	cout << "----------------------" << endl;
	cout << "1. Player" << endl;
	cout << "2. Computer" << endl;
	cout << "3. Back" << endl;	
}

void showCurrentSide(bool isPlayerX)
{
	if(isPlayerX)
	{
		cout << "Current side: X" << endl;	
	}
	
	if(!isPlayerX)
	{
		cout << "Current side: O" << endl;	
	}	
}

void showCurrentTurn(int priority)
{
	if(priority == 1)
	{
		cout << "Current turn: player" << endl;
	}
	
	if(priority == 2)
	{
		cout << "Current turn: computer" << endl;
	}		
}

string getChoice()
{
	string choice;
	
	cout << "Your choice: ";
	cin >> choice;
	
	return choice;
}

int convertAndCheckChoice(string str, char last, int sideChoice)
{
	if(isCorrectInput(str, last))
	{
		sideChoice = strToInt(str);
	}
	
	return sideChoice;
}
