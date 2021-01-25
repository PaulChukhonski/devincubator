#include <iostream>
using namespace std;
#define SIZE 128
#define END '0'
#define EVEN_SYMBOL '+'
#define UNEVEN_SYMBOL '-'

bool isDigit(char c);
int strLength(char str[]);
void move(char text[], int i, int number, int size, char symbol);

int main()
{
    char text[SIZE];
	char symbol;
	int number; int size;
	
    cout << "Input text: ";
    cin.getline(text, SIZE);

    for (int i = 0; text[i] != '\0'; i++) 
	{
        if (isDigit(text[i])) 
		{
			number = text[i]-END;
			size = strLength(text);
			
			if(number % 2 == 0 && number != 0)
			{
				move(text, i, number, size, EVEN_SYMBOL);			
			}

			if(number % 2 == 1)
			{
				move(text, i, number, size, UNEVEN_SYMBOL);										
			}	
			
			if(number == 0)
			{				
				for(int j = i; j < size-1; j++)
				{
					text[j] = text[j+1];	
				}
			    		    
			    text[size-1] = 0;
				i--;												
			}																		
        }
    }
    
    cout << "Result: " << text;

    return 0;
}

bool isDigit(char c)
{
    char s[] = "0123456789";
    for (int i = 0; s[i] != '\0'; i++) 
        if (c == s[i])
            return true;
    return false;
}

int strLength(char str[])
{
	int i = 0;
	
	while(str[i] != '\0')
	{
		i++;
	}

	return i;
}

void move(char text[], int i, int number, int size, char symbol)
{
	for(int k = size-1, l = k+number-1; k > i; k--, l--)
	{
		text[l] = text[k];		
	}	
				
	for(int j = 0; j < number; j++)
	{	    			    		
		text[i] = symbol;
		i++;		
	}
}
