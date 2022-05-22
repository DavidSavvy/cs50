#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);

int main(void)
{
    string input = get_string("Text: ");
    int letters = count_letters(input);
    int words = count_words(input);
    int sentences = count_sentences(input);

    int index = round(0.0588 * ((float)letters / (float)words * 100) - 0.296 * ((float)sentences / (float)words * 100) - 15.8);


    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string input)
{
    int letters = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
        {
            letters++;
        }
    }
    //printf("%i\n", letters);
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
    //printf("%i\n", words + 1);
    return words + 1;
}

int count_sentences(string input)
{
    int sentences = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == 33 || input[i] == 46 || input[i] == 63)
        {
            sentences++;
        }
    }
    printf("%i\n", sentences);
    return sentences;
}
