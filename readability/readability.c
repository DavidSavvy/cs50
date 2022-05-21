#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string input);

int main(void)
{
    string input = get_string("Text: ");
    count_letters(input);
}

int count_letters(string input)
{
    int letters = 0;
    for (int i = 0, i < strlen(input), i++) //might bring issue wit \0
    {
        if (input[i] > 64 && input[i] < 91 || input[i] > 96 && input[i] < 123) //might bring issue with mixing && and ||
        {
            letters++;
        }
    }
    return letters;
    printf("%i", letters);
}