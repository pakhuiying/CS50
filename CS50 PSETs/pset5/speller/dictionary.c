// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //character array that stores the length of the word. random access every character in word
    //e.g. char cat[3+1]: cat[0] = c; cat[1] = a; cat[2] = t
    struct node *next; //pointer that points to the next word
}
node;

// Number of buckets in hash table
const unsigned int N = 26*26; //can change N

// Hash table.
//declares table as an array of N pointers. Thus, each element in table, holds a pointer to an int value.
node *table[N]; //create an array of pointers/nodes

// Returns true if word from text file is in dictionary else false
//char *word = string word in text file
bool check(const char *word) //4th
{
    //compare words stored in hashtable
    int index = hash(word);

    //loop through every linked list to look for word
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)//continue loop if pointer is not NULL
    {
        if (strcasecmp(word,tmp->word)==0)
        {
            return true;
        }

    }
    return false;
}

// Hashes word to a number. take a word, run a hash function on it, return an integer
//assigns a number to every input. associate each word with a specific numbered bucket
//takes word as an input. convert this word to a number so it knows which bucket & linked list to go to.
//char *word = string word. (word from dictionary)
unsigned int hash(const char *word) //2nd
{

    //char c = word[0]; //look at first character of string
    //if (isalpha(c) && c < 97)//|| ispunct(c)
    //{
        //if capital letters
        //c = tolower(c); //change to lower case
    //}

    //all alphabets in dictionary are lower case
    //int index = c - 97; //normalise characters and change to integer corresponding to positions
    //should return an integer that indicates the position of table pointer

    //return index;
    char c1 = word[0];
    char c2 = word[1];
    
    if (!isalpha(c2))//if c2 is not an alphabet e.g. space e.g. a
    {
        c2 = c1;
    }
    
    if (isalpha(c1) && c1 < 97) //if they are alphabet and capital letters
    {
        //if capital letters
        c1 = tolower(c1); //change to lower case        
    }
    
    if (c2 < 97)
    {
        //if capital letters
        c2 = tolower(c2); //change to lower case        
    }    
    
    int index1 = c1 - 97;
    int index2 = c2 - 97;
    int count = 0;
    int position = 0;
    
    for (int i = 0; i < 26; i++)//first alphabet
    {
        for (int j = 0; j < 26; j++)//second alphabet
        {
            if (i == index1 && j == index2) //if first 2 alphabet matches
            {
                position = count; //rmb the count
            }
            
            count++;
        }
    }
    
    return position;
    
}

// Loads dictionary into memory, returning true if successful else false
//load words into a data structure i.e. hash table
//hash table: array of linked list
//a dictionary is a list of words. so u have to hash each word in the dictionary to laod the entire dictionary
//has to call hash function
bool load(const char *dictionary) //1st
{
    // Open file
    FILE *file = fopen(dictionary, "r");

    if (file==NULL)
    {
        printf("Unable to open file %s\n",dictionary);
        return false;
    }

    char word[LENGTH + 1]; //character array
    //int index = 0 ;
    //for each string, hash it and load it into memory using hash function;

    //read strings from file
    while (fscanf(file,"%s",word) != EOF)
    {
        //everytime a word is read, malloc for the node that contains the word and its node
        //create a new node for each word
        node *n = malloc(sizeof(node)); //define a temp node pointer that mallocs for node

        if (n==NULL)
        {
            printf("No space for malloc!\n");
            return false;
        }

        strcpy(n->word, word); //go to the word in node and copy the word into
        n->next = NULL; //idk what the next word is but dictionary is alr alphabetically ordered

        //hash word to identify which position of hashtable it should insert into
        int index = hash(word);

        //insert node into hashtable
        //hash table is an array of linked list
        //loop through all the linked pointers
        //table[index] is the header node
        //header cant point to new node becus previous links will be lost
        //*node *tmp = table[index]; //assign a temp to point whereever header is pointing at
        //update pointer
        //*n->next = tmp->next;
        //*table[index]->next = n;
        //add new node to that linked list
        //keep pushing back older words and add new words behind header

        if (table[index]==NULL) //if index array is empty, give it a new node
        {
            table[index] = n;
        }

        else //if table is not NULL
        {
            node *tmp = table[index]->next;
            n->next = tmp;
            table[index]->next = n;
        }

    }

    fclose(file);

    //when fully loaded all words, return true.
    return true;

    //return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) //3rd
{
    //use hash table to determine number of words in each array

    int counter = 0;
    //loop through hash table array
    for (int i = 0; i < N; i++)
    {//loop through each linked list in each array
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)//continue loop if pointer is not NULL
        {
            if (table[i]==NULL)
            {
                return 0;
            }
            counter++;
        }
    }

    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) //5th
{

    for (int i = 0; i < N; i++)
    {//loop through each linked list in each array
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;

            if (table[i]==NULL)
            {
                return false;
            }

            free(table[i]); //free the previous link one by one
            table[i] = tmp;
        }

        //for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)//continue loop if pointer is not NULL
        //{
            //free(tmp);
        //}
    }
    return true;
}
