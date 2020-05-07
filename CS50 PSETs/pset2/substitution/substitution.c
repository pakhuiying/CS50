#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

int match(string ciphertext);
int main(int argc, string argv[])
{
    string outcome =0;

    if (argc==2)
    {
        if (strlen(argv[1])!=26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        else //if key contains 26 characters
        {
                char upperchar = 0;
                int sumupper = 0;
    
            for (int i=0; i<strlen(argv[1]); i++)
            {
                if (!isalpha(argv[1][i])) //check if string has non-alphabetical character
                {
                    printf("Key contains non-alphabetical character\n");
                    return 1;
                }

                upperchar=toupper(argv[1][i]); //change all toupper so ascii sum will be consistent
                sumupper+=upperchar;
                
                if (argv[1][i]==argv[1][i+1]) //Key contains adjacent duplicate alphabetic character becus sum can still be 2015
                {
                    printf("Key contains adjacent duplicate alphabetic character\n");
                    return 1;
                }

            }
            
            if (sumupper==2015) //2015 is the sum of upper ascii int of all distinct alphabets
            {
                match(argv[1]);
                return 0;

            }
            
            else
            {
                printf("Key contains duplicate alphabetic character\n");
                return 1;
            }

        }
    }

    else //if argc!=2
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

int match(string ciphertext) //function to match alphabets to new ciphertext. ciphertext = argv[1]
{
    int ascii = 0;

    string text = get_string("plaintext: ");
    printf("ciphertext:  ");

    for (int i=0; i<strlen(text); i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            ascii = text[i] - 97;
            text[i] = ciphertext[ascii];
            text[i] = tolower(text[i]);
        }

        else if (text[i] >= 'A' && text[i] <= 'Z' )
        {
            ascii = text[i] - 65;
            text[i] = ciphertext[ascii];
            text[i] = toupper(text[i]);
        }

        else
        {
            ascii =  text[i] + 0;
        }

        printf("%c", text[i]);
    }

    printf("\n");

    return 0;
}