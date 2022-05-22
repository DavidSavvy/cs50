#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string substitute(string key, string plainText);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    printf("%s", key);
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
    }

    string plainText = get_string("plain text: ");

    string cipherText = substitute(key, plainText);

    printf("ciphertext: %s\n", cipherText);
}

string substitute(string key, string plainText) //problem with space and comma
{
    for (int i = 0; i < strlen(plainText); i++)
    {
        char temp = plainText[i];

        if (isupper(plainText[i]))
        {
            plainText[i] = key[i - 65];
        }
        else
        {
            plainText[i] = key[i - 97];
        }
    }
    return plainText;

}

/*

SUBSTITUTE:

-Go through every char in the plaintext string
-Set char
-Case sensitive ciphertext

*/