#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX]; //array

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair; //pairs[i].winner = _ ; pairs[i].loser_

// Array of candidates
string candidates[MAX]; //name of candidates
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1]; //name of candidates
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{   //vote(j, name, ranks. rank=j. j=candidate_count[i]. looping over candidate
    // ranks[i] is voter's ith preference

    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j])==0) //scan which name matches which candidate index j.
        {
            ranks[rank] = j; //index of candidate (j) is the ranks[i] for a voter
            //printf("Rank%i: %i\n",rank, ranks[rank]);
            //printf("j:%i\n",j);
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // update the global preferences array to add the current voter’s preferences.
    //preferences[i][j] should represent the number of voters who prefer candidate i over candidate j
    //int num_preference = candidate_count * (candidate_count - 1);
    //int num_preference[candidate_count][candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++) //if set j = 0, it will skip the first output
        {

                preferences[ranks[i]][ranks[j]]++; //need set preferences as 0?

        }
    }

   //for (int i = 0; i < candidate_count; i++)
   //{
       //for (int j = 0; j < candidate_count; j++)
       //{
           //printf("i:%i,j:%i. All preferences:%i\n", i, j,preferences[i][j]);
       //}
   //}
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //add all pairs of candidates where one candidate is preferred to the pairs array.
    //A pair of candidates who are tied should not be added to the array.
    //update the global variable pair_count to be the number of pairs of candidates.
    //(The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
    int count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            //pair_count = candidate_count * (candidate_count - 1)/2;

                if (preferences[i][j] > preferences[j][i]) //if not tied
                {
                    pairs[count].winner = i;
                    pairs[count].loser = j;
                    count++;
                    pair_count++;
                    //pair_count = candidate_count * (candidate_count - 1)/2;

                }

                else if (preferences[i][j] < preferences[j][i]) //if not tied
                {
                    pairs[count].winner = j;
                    pairs[count].loser = i;
                    count++;
                    pair_count++;
                    //pair_count = candidate_count * (candidate_count - 1)/2;
                }

                else if (preferences[i][j] == preferences[j][i]) //if tied
                {

                    pair_count--;
                }
        }
    }

    printf("Pair_count:%i, Count%i\n",pair_count,count);
    return;
}

// Sort pairs in decreasing order by strength of victory //largest to smallest
void sort_pairs(void)
{
    //int wins[pair_count][pair_count];
    int unsortedwins[pair_count];
    int wins[pair_count];
    int temp; //temp variable to store ????
    int temp_winner;
    int temp_loser;
    //where wins[w][l] = wins defined by winner and loser of each pair


    for (int i = 0; i < pair_count; i++)
    {
        unsortedwins[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        //printf("W:%i,L:%i. Unsorted:%i\n",pairs[i].winner,pairs[i].loser, unsortedwins[i]);
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i+1; j < pair_count; j++)
        {
            if (unsortedwins[i]<unsortedwins[j])
            {
                temp = unsortedwins[i];
                temp_winner = pairs[i].winner;
                temp_loser = pairs[i].loser;
                unsortedwins[i] = unsortedwins[j];
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                unsortedwins[j] = temp;
                pairs[j].winner = temp_winner;
                pairs[j].loser = temp_loser;

            }
        }
        //printf("W:%i,L:%i. sorted:%i\n",pairs[i].winner,pairs[i].loser, unsortedwins[i]);
    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //locked[i][j] means i is locked in over j
    //so long as the edge would not create a cycle

    int min = pair_count - 1; //min number is the last position of pair count
    int k = 0; //keep track of number of true
    int count = 0;
    int sum[pair_count];

    //if (cycle(pairs[0].winner,pairs[0].loser)==false) //if no cycle
    //{
        for (int i = 0; i < pair_count; i++)
        {
            int w = pairs[i].winner; //candidate index of winner
            int l = pairs[i].loser; //candidate index of loser
            locked[w][l] = true; //lock all pairs

            cycle(pairs[0].winner,pairs[0].loser);

            //for (int j = 0; j < pair_count; j++)
            //{
                //printf("locked:%i\n",locked[i][j]);
            //}
        }
    //}


    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner;
    int source;

    for (int i = 0; i < candidate_count; i++)
    {
        winner = true; //set all candidates as true first
        for (int j = 0; j < candidate_count; j++){

            //if (pairs[i].winner!=pairs[j].loser)
            if (locked[j][i]==true) //if any pair is lock, winner is flip to false as j changes while i is const
            {
                winner = false;

            }
        }

        if (winner==true)
        {
            source = i;
        }
    }

    printf("Winner:%s\n",candidates[source]);
    return;
}

bool cycle(int w, int l) //return true/false
{//step is the count of each joining/not joing edge process
//if every winner is also a loser then there is a cycle
//locked winner to loser= true, locked loser to winner is true also --> cycle
    if (locked[l][w]==true) //initially locked[w][l]=true
    {
        return true; //for cycle to exists w-->l must have l-->w. cycle exists
    }

    for (int i = 0; i < pair_count; i++)//going by pair sequence
    {
        if (locked[l][pairs[i].winner]==true) //where i is assumed to be winner
        {
            //if (cycle(l,i)==true) //if loser is winner and i is loser, check if i is checked with other candidate
            //if locked i with other winner candidate is true, return true again.
            //if (cycle(i,w)==true)
            if (cycle(w,pairs[i].winner)==true) //if loser i locks onto winner then it will return true
            {
                //locked[pairs[w].winner][pairs[i].loser]==false;
                locked[pairs[i].winner][w]=false; //
                return true;
            }
        }
    }


    return false;


}