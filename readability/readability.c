#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string input);
int count_words(string input);

int main(void)
{
    string input = get_string("Text: ");
    count_letters(input);
    count_words(input);
}

int count_letters(string input)
{
    int letters = 0;
    for (int i = 0; i < strlen(input); i++) //might bring issue wit \0
    {
        if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
        {
            letters++;
        }
    }
    printf("%i\n", letters);
    return letters;
}

int count_words(string input)
{
    int words = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == 32)
        {
            words++;
        }
    }
    printf("%i\n", words + 1);
    return words + 1;
}