#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string substitute(string key, string plainText);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./substitution key");
        return 1;
    }

    string key = argv[1];
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.");
    }

    string plainText = get_string("plain text: ");

    string cipherText = substitute(key, plainText);

    printf("ciphertext: %s", cipherText);
}

string substitute(string key, string plainText)
{
    for (int i = 0; i < strlen(plainText); i++)
    {
        char temp = plainText[i];

        if (isupper(plainText[i]))

    }
}

/*

SUBSTITUTE:

-Go through every char in the plaintext string
-Set char
-Case sensitive ciphertext

*/