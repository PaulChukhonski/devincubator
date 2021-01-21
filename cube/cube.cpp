#include <iostream>
#include <cstdlib>
using namespace std;
#define TRANSPARENT '-'
#define PAINTED '+'
#define SIDE 3
#define SIZE SIDE*SIDE

void partInitialization(char part[]);
void partShow(char part[]);
void cubeShow(char part1[], char part2[], char part3[]);
bool partScan(char part[]);
bool partScanRows(char part[]);
bool partScanColumns(char part[]);
bool cubeScan(char part1[], char part2[], char part3[]);

int main()
{
	char part1[SIZE] = {TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT};
	char part2[SIZE] = {TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT};
	char part3[SIZE] = {TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT,TRANSPARENT};
	
	partInitialization(part1);
	partInitialization(part2);
	partInitialization(part3); 
	
	cubeShow(part1, part2, part3);
		
	if(partScan(part1) == true || partScan(part2) == true || partScan(part3) == true || cubeScan(part1, part2, part3) == true)
	{
		cout << "Cube has got at least one TRANSPARENT line." << endl;
	}	
	else
	{
		cout << "Cube hasn't got any TRANSPARENT line." << endl;
	}
	
	return 0;
}

void partInitialization(char part[])
{
	for(int i = 0; i < SIZE; i++)
	{
		if(rand() % 2 == 1)
		{
			part[i] = PAINTED;	
		}
	}	
}

void partShow(char part[])
{
	for(int i = 0; i < SIZE; i++)
	{	
		cout << part[i]; 
		
		if(i % SIDE == SIDE-1)	
		{
			cout << endl;	
		}
	}	
}

void cubeShow(char part1[], char part2[], char part3[])
{
	partShow(part1);
	cout << endl;
	partShow(part2);
	cout << endl;
	partShow(part3);
	cout << endl;			
}

bool partScan(char part[])
{
	bool check = false;
	
	if(partScanRows(part) == true || partScanColumns(part) == true)
	{
		check = true;
	}
	
	return check;
}

bool partScanRows(char part[])
{
	int start, end, countTransparent;
	bool check = false;
	
	end = SIDE;
	countTransparent = 0;
		
	for(start = 0; start < SIZE; start += SIDE)
	{
		for(int j = start; j < end; j++)
		{
			if(part[j] == TRANSPARENT)
			{
				countTransparent += 1;
			}					
		}
	
		if(countTransparent == SIDE)
		{
			check = true;
			break;
		}
	
		countTransparent = 0;
		end += SIDE;
	}
		
	return check;
}

bool partScanColumns(char part[])
{
	int start, end, countTransparent;
	bool check = false;
	
	end = SIZE - SIDE;
	countTransparent = 0;
	
	for(start = 0; start < SIDE; start++)
	{
		for(int j = start; j <= end; j += SIDE)
		{
			if(part[j] == TRANSPARENT)
			{
				countTransparent += 1;
			}			
		}

		if(countTransparent == SIDE)
		{
			check = true;
			break;
		}

		countTransparent = 0;
		end++;
	}
		
	return check;
}

bool cubeScan(char part1[], char part2[], char part3[])
{
	bool check = false;
	
	for(int i = 0; i < SIZE; i++)
	{		
		if(part1[i] == TRANSPARENT && part1[i] == part2[i] && part2[i] == part3[i])	
		{
			check = true;
			break;
		}		
	}	
	
	return check;	
}
