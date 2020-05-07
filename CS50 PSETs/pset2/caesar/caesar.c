#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int crypto(int k);
int alphabet(int ascii, int k, char text);
int main(int argc, string argv[])
{
    string outcome =0; //asign result as string outcome that you can use outside the for loop
    int k =0; //define as int for use in atoi

    if (argc==2)
    {
        for (int i=0; i<strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
            outcome=argv[1];
            }
            
            else
            {
            printf("Usage: %s key\n", argv[0]);
            return 1;
            }
            
        }

        k = atoi(outcome);
        crypto(k);
    }

    else
    {
        printf("%s key\n", argv[0]);
        return 1;
    }

}


int crypto(int k)
{
    if (k>26)
    {
        k=k%26; //if k>26 let it overflow
    }

    else
    {
        k=k+0; //if k<26, k is unchanged
    }


    string text = get_string("plaintext: ");
    printf("ciphertext:  ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            alphabet(96, k, text[i]);

        }

        else if (text[i] >= 'A' && text[i] <= 'Z' )
        {
            alphabet(64, k, text[i]);
        }

        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0; //for every function defined, return 0 so u dont get error
}

int alphabet(int ascii, int k, char text) //make sure text and ascii is either int or char for %c to work. 
//cannot have string text
{
    text = text - ascii; //convert alphabets to 1-26
    text = text + k;
    
    if (text > 26) //if ascii int>127, it will be displayed as empty integer. 
    //have to make sure that prior to adding k, alphabets have to be converted to 1-26
    {
        text = text- 26;
    }
    
    else
    {
        text = text + 0;
    }
    
    printf("%c", text+ascii);//make sure text and ascii is either int or char for %c to work. cannot have string text
    return 0;
}