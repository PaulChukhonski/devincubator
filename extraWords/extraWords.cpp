#include <iostream>
using namespace std;
#define SIZE 128

bool isSeparator(char c);
bool strCompare(char s1[], char s2[]);
int strLength(char str[]);

int main()
{
    char text[SIZE], word[SIZE], prevWord[SIZE] = "";
    int i, iw = 0;

    cout << "Input text: ";
    cin.getline(text, SIZE);

    for (i = 0; text[i] != '\0'; i++) 
	{
        if (!isSeparator(text[i])) 
		{
            word[iw] = text[i];
            iw++;
            
            if (isSeparator(text[i+1]) || text[i+1] == '\0') 
			{
                word[iw] = '\0';
                
				if(!strCompare(prevWord, word))
				{
					prevWord[iw] = 0;
					
	            	for(int j = 0; j < iw; j++)
					{
						prevWord[j] = word[j]; 
					}					
				}
				else
				{					
	            	for(int j = i-iw+1; j <= i; j++)
					{
						text[j] = ' '; 
					}							
				}
				
				iw = 0;
            }
        }
    }
 
    for (i = 0; text[i] != '\0'; i++) 
	{
		for(;text[i] == ' ' && text[i+1] == ' ';)
		{
			for(int j = i; j < strLength(text)-1; j++)
			{
				text[j] = text[j+1];	
			}
		    		    
		    text[strLength(text)-1] = 0;						
		}
    } 
    
    cout << text << endl;
    
    return 0;
}

bool isSeparator(char c)
{
    char s[] = ",.! ?";
    for (int i = 0; s[i] != '\0'; i++) 
        if (c == s[i])
            return true;
    return false;
}

bool strCompare(char s1[], char s2[])
{
	int i = 0;
	bool flag = true;
	
	while(s1[i] != '\0')
	{
		if(s2[i] != s1[i])
		{
			flag = false;
		}
		i++; 
	}	
	
	if(strLength(s1) != strLength(s2))
	{
		flag = false;
	}
	
	return flag;
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
