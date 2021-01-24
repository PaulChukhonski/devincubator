#include <iostream>
using namespace std;
#define WORD_SIZE 8
#define FIELD_SIZE WORD_SIZE-1
#define INPUT_SIZE 128
#define WORD "MYSTERY"
#define SEPARATOR '|'
#define EMPTY '-'
#define END '0'
#define CONVERT 32
#define A 'A'
#define a 'a'
#define Z 'Z'
#define z 'z'

void initializeGameField(char cells[]);
void initializeNumeratedField(char cells[]);
void showField(char cells[]);
void showAllFields(char cells[], char numeratedCells[]);
bool isCanPlay(char cells[]);
void inputString(char str[]);
bool isCorrectStrLength(char str[]);
bool isCorrectLetter(char letter);
char convertLetters(char letter, char similarLetter);

int main()
{
	char gameCells[FIELD_SIZE] = {}, numeratedCells[FIELD_SIZE] = {};
	char word[WORD_SIZE] = WORD;
	char str[INPUT_SIZE];
	char letter, similarLetter;
	bool flag; 
	
	initializeGameField(gameCells);
	initializeNumeratedField(numeratedCells);	
	showAllFields(gameCells, numeratedCells);
	
	while(isCanPlay(gameCells))
	{
		flag = false;
		inputString(str);
		
		if(!isCorrectStrLength(str))
		{
			cout << "Not a letter! Please, enter a letter."	<< endl;
			system("pause");
		}
		else
		{
			letter = str[0];
			
			if(!isCorrectLetter(letter))
			{
				cout << "Not a letter! Please, enter a letter."	<< endl;
				system("pause");
			}
			else
			{
				similarLetter = convertLetters(letter, similarLetter);
				
				for(int i = 0; i < FIELD_SIZE; i++)
				{
					if(word[i] == letter)
					{
						gameCells[i] = letter;
						flag = true;
					}
	
					if(word[i] == similarLetter)
					{
						gameCells[i] = similarLetter;
						flag = true;
					}				
				}
				
				if(flag)
				{
					cout << "Succeed!" << endl;								
				}	
				else
				{
					cout << "No such letter!" << endl;					
				}
				
				system("pause");	
			}		
		}	
		
		showAllFields(gameCells, numeratedCells);	
	}
	
	cout << "You guessed the word!";
	
	return 0;
}

void initializeGameField(char cells[])
{
	for(int i = 0; i < FIELD_SIZE; i++)
	{
		cells[i] = EMPTY;
	}	
}

void initializeNumeratedField(char cells[])
{
	for(int i = 0; i < FIELD_SIZE; i++)
	{
		cells[i] = i+1+END;
	}	
}

void showField(char cells[])
{
	for(int i = 0; i < FIELD_SIZE; i++)
	{
		cout << cells[i] << SEPARATOR;
	}	
	cout << endl;
}

void showAllFields(char cells[], char numeratedCells[])
{
	system("cls");
	cout << "Field of Dreams!" << endl << "You need to guess the word by entering letters." << endl;
	showField(numeratedCells);
    showField(cells);	
}

bool isCanPlay(char cells[])
{
	bool check = false;
	
	for(int i = 0; i < FIELD_SIZE; i++)
	{
		if(cells[i] == EMPTY)	
		{
			check = true;
		}
	}
	
	return check;
}

void inputString(char str[])
{
	cout << "Enter a letter: ";
    cin >> str;
}

bool isCorrectStrLength(char str[])
{
	bool check = true;
	int i = 0;
	
	while(str[i] != '\0')
	{
		i++;
	}

	if(i != 1)
	{
		check = false;
	}

	return check;
}

bool isCorrectLetter(char letter)
{
	return (letter >= A && letter <= Z) || (letter >= a && letter <= z);
}

char convertLetters(char letter, char similarLetter)
{
	if(letter >= A && letter <= Z)
	{
		similarLetter = letter + CONVERT;
	}	

	if(letter >= a && letter <= z)
	{
		similarLetter = letter - CONVERT;
	}	

	return similarLetter;
}
