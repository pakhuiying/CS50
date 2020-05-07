#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    string text = get_string("Text: \n");
    int letters = 0;
    int words = 0;
    int sentences = 0;
    float L = 0;
    float S = 0;
    int index = 0;
    float hundred = 100.00;//need to make float becus otherwise division will give an integer

    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    L = letters*hundred/words;//need to multiply first then divide
    S = sentences*hundred/words;
    index = round(0.0588*L - 0.296*S - 15.8);

    if (index<1)
    {
        printf("Before Grade 1\n");
    }

    else if (index>16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }

   // printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n%.2f L\n%.2f S\n%i Grade\n", letters, words, sentences, L, S, index);
}

int count_letters(string text)
{
   // int sumLetter = 0;
    int count = 0;

        for (int i=0; i < strlen(text); i++)
    {
        if (isalpha(text[i])) //check if character is an alphabetic
        {
            count++;
        }

        else
        {
            count = count + 0;
        }

    }

   return (count);
}

int count_words(string text)
{

    int count = 0;

        for (int i=0; i < strlen(text); i++)
    {
        if (isspace(text[i])) //check if text has space
        {
            count++;
        }

        else
        {
            count = count + 0;
        }

    }

    count = count + 1; //number of spaces is always one less than number of words

   return (count);
}

int count_sentences(string text)
{

    int count = 0;

        for (int i=0; i < strlen(text); i++)
    {
        if (text[i]=='!' || text[i]=='?' || text[i]=='.') //check if text has period/excl/questn mark
        {
            count++;
        }

        else
        {
            count = count + 0;
        }

    }

   return (count);
}