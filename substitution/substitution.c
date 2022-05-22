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
    //printf("%s", key);
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    

    string plainText = get_string("plain text: ");

    string cipherText = substitute(key, plainText);

    printf("ciphertext: %s\n", cipherText);

    return 0;
}

string substitute(string key, string plainText) //problem with space and comma
{
    for (int i = 0; i < strlen(plainText); i++)
    {
        char temp;

        if (!isalpha(plainText[i]))
        {
            continue;
        }

        if (isupper(plainText[i]))
        {
            temp = key[plainText[i] - 65];
            temp = toupper(temp);
            plainText[i] = temp;
        }
        else
        {
            temp = key[plainText[i] - 97];
            temp = tolower(temp);
            plainText[i] = temp;
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