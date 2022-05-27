#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
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
        candidates[i] = argv[i + 1];
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

    //Tests array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
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
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    }
    return false;
    // TODO

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) //Cycles through candidates
    {
        for (int j = 0; j < candidate_count; j++) //Cycles through ranks array
        {
            if (i != ranks[j])
            {
                preferences[ranks[j]][i]++;

                /*
                for (int k = 0; k < candidate_count; k++)
                {
                    for (int l = 0; l < candidate_count; l++)
                        {
                            printf("%i ", preferences[l][k]);
                        }
                        printf("\n");
                }
                printf("\n");
                */
            }
            else
            {
                /*
                for (int k = 0; k < candidate_count; k++)
                {
                    for (int l = 0; l < candidate_count; l++)
                        {
                            printf("%i ", preferences[l][k]);
                        }
                        printf("\n");
                }
                */


                break;
            }
        }

    }

    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //TRY IF (I>0) and (J<1) THEN continue;
    //Maybe try recursion... look at ipad diagram
    //Find pair number, then go through i loop

    //RECURSION to find pair number

    pair_count = 0;
    for (int i = 0, j = candidate_count; i < candidate_count; i++)
    {
        for (int k = candidate_count - 1; k > candidate_count - j - 1; k--)
        {
            if (preferences[i][k] > preferences[k][i])
            {
                pairs[x].winner = i;
                pairs[x].loser = k;
                pair_count++;
            }
            else if (preferences[i][k] < preferences[k][i])
            {
                pairs[x].winner = k;
                pairs[x].loser = i;
                pair_count++;
            }
            /*
            else
            {
                continue;
            }
            */
        }
        j--;
    }

    //pair_count++;
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}