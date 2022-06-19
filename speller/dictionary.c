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

void unloadHelper(node *pointer);

// TODO: Choose number of buckets in hash table
const unsigned int N = 52;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char *wordCpy = malloc(LENGTH + 1);

    strcpy(wordCpy, word);
    for (int i = 0; i < strlen(wordCpy); i++)
    {
        wordCpy[i] = tolower(wordCpy[i]);
    }
    int hashN = hash(wordCpy);

    if (table[hashN] == NULL)
    {
        return false;
    }

    node *temp = table[hashN];
    if (strcmp(temp->word, word) == 0)
    {
        return true;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;

        if (strcmp(temp->word, wordCpy) == 0)
        {
            free(wordCpy);
            return true;
        }
    }
    free(wordCpy);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += word[i];
    }
    sum %= 52;
    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //char *word = malloc(LENGTH + 1); //might have to allocate memory
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF) //might have to reset word array
    {
        int hashN = hash(word);

        if (table[hashN] == NULL)
        {
            node *pWord = malloc(sizeof(node));
            strcpy(pWord->word, word);
            pWord->next = NULL;
            table[hashN] = pWord;
            continue;
        }

        node *pWord = malloc(sizeof(node));
        strcpy(pWord->word, word);
        pWord->next = table[hashN];
        table[hashN] = pWord;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int numberWord = 0;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            numberWord++;
            node *temp = table[i];
            while (temp->next != NULL)
            {
                numberWord++;
                temp = temp->next;
            }
        }
    }
    return numberWord; //implement the else 0 if needed
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        node *temp = table[i];
        unloadHelper(temp);
    }
    return true;
}

void unloadHelper(node *pointer)
{
    if (pointer->next == NULL)
    {
        free(pointer);
        return;
    }

    unloadHelper(pointer->next);
    free(pointer);
}
