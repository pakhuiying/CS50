#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; //argv[1]=1st candidate's name, argv[2]=2nd candidate's name etc
        candidates[i].votes = 0; //initialise all starting votes as 0
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i].name)==0)
        {
            candidates[i].votes++;
            return true;
        }
        
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int last_number = candidate_count + 1;
    int arr[last_number];
    arr[last_number]=0; //initialise last number as 0
    
    for (int i = 0; i < candidate_count; i++)
    {
        arr[i] = candidates[i].votes;
        //printf("Vote counts: %i\n",arr[i]);
        //printf("Vote counts: %i\n",candidates[i].votes);
        
    }
    
    for (int i = 0; i < candidate_count; i++) 
    {
        if (arr[last_number] < arr[i])
        {
            arr[last_number] = arr[i];
        }
        
        if (arr[last_number]==candidates[i].votes)
        {
            printf("%s\n",candidates[i].name);
        }
            
    }
    
    //return 0;
}

