// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char *word = malloc(LENGTH + 1); //might have to allocate memory

    while (fscanf(file, "%s", word) != EOF) //might have to reset word array
    {
        int hashN = hash(word) - 1;

        if (table[hashN]->next == NULL)
        {
            node *pWord = malloc(sizeof(node));
            strcpy(pWord->word, word);
            pWord->next = NULL;
            table[hashN]->next = pWord;
            free(pWord);
            continue;
        }

        node *pWord = malloc(sizeof(node));
        strcpy(pWord->word, word);
        pWord->next = table[hashN]->next;
        table[hashN]->next = pWord;
        free(pWord);
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
