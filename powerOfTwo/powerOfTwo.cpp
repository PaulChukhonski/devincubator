#include <iostream>
#include <cstdlib>
using namespace std;
#define BASE 2
#define SIZE 1000
#define THOUSAND 1000

void initializeArray(int array[]);
bool isPowOfTwo(int num);
void showPowOfTwoElemnents(int array[]);

int main()
{
	int array[SIZE] = {0};
	
	initializeArray(array);
	showPowOfTwoElemnents(array);
	
	return 0;
}

void initializeArray(int array[])
{
	for(int i = 0; i < SIZE; i++)
	{
		array[i] = rand() % THOUSAND;
	}
}

bool isPowOfTwo(int num)
{
	bool check = true;
	
	while(num)
	{	
		if(num == BASE || num == 1)
		{
			break;
		}
		
		if(num % BASE == 1)
		{
			check = false;
			break;
		}
		
		num /= BASE;
	}

	if(num == 0)
	{
		check = false;
	}

	return check;
}

void showPowOfTwoElemnents(int array[])
{
	for(int i = 0; i < SIZE; i++)
	{
		if(isPowOfTwo(array[i]))
		{		
			cout << "Element " << i << ": " << array[i] << endl;
		}		
	}
}
