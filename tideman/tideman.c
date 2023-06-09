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
bool check_locked(pair targetPair, pair lockedPairs[pair_count], int lockedPairCount, int indexChain[pair_count], int indexChainCount);
bool check_cycle(int indexChain[pair_count], int indexChainCount);


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
    /*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    */

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
            }
            else
            {
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

    pair_count = 0;
    for (int i = 0, j = candidate_count; i < candidate_count; i++)
    {
        for (int k = candidate_count - 1; k > candidate_count - j - 1; k--)
        {
            if (preferences[i][k] > preferences[k][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = k;
                pair_count++;
            }
            else if (preferences[i][k] < preferences[k][i])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = i;
                pair_count++;
            }

        }
        j--;
    }

    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
//Bubble sort used
void sort_pairs(void)
{

    int switchCount;
    do
    {
        switchCount = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                switchCount++;
            }

        }
    }
    while (switchCount != 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    int lockedPairCount = 0;
    //printf("Pair Count: %i\n", pair_count);


    pair lockedPairs[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        int indexChainCount = 0;
        int indexChain[pair_count];
        if (check_locked(pairs[i], lockedPairs, lockedPairCount, indexChain, indexChainCount)) //If given all clear by check_locked, locks pair
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            lockedPairs[i] = pairs[i];
            lockedPairCount++;
            //printf("Locked %s -> %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
        else
        {
            //printf("Did not lock %s -> %s\n", candidates[pairs[i].winner], candidates[pairs[i].loser]);
            continue;
        }
    }



}

bool check_locked(pair targetPair, pair lockedPairs[pair_count], int lockedPairCount, int indexChain[pair_count], int indexChainCount)
{
    if (indexChainCount == 0) //Sets up first pair in the chain.
    {
        indexChain[indexChainCount] = targetPair.winner;
        indexChain[indexChainCount + 1] = targetPair.loser;
        indexChainCount += 2;
    }

    for (int i = 0; i < lockedPairCount; i++)
    {
        if (targetPair.loser == lockedPairs[i].winner)
        {

            indexChain[indexChainCount ] = lockedPairs[i].loser;
            indexChainCount++;

            if (check_cycle(indexChain, indexChainCount)) //Cycle checked every time, not quite necessary, could be at the end
            {
                return false; //Don't add pair
            }

            if (!(check_locked(lockedPairs[i], lockedPairs, lockedPairCount, indexChain, indexChainCount))) //Attempts to guard against recursion problems by checking return value.
            {
                return false; //Makes sure the highest level of the function returns false if need be.
            }

        }
        else
        {
            continue; //If it cannot find the next step in chain, lock pair
        }
    }
    /*
    if (check_cycle(indexChain, indexChainCount))
    {
        return false; //Don't add pair
    }
    */
    return true; //Means that function is acting on first locked pair, so it adds it

}

bool check_cycle(int indexChain[pair_count], int indexChainCount) //Searches through chain to see if the first index (target) is repeated or cycled.
{
    for (int i = 1; i < indexChainCount; i++)
    {
        if (indexChain[0] == indexChain[i])
        {
            return true;
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void) //Checks for a column with no true values going down to determine source/winner.
{

    for (int i = 0; i < candidate_count; i++)
    {
        int trueCount = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked [j][i] == true)
            {
                trueCount++;
            }

        }
        if (trueCount == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }


    // TODO

}