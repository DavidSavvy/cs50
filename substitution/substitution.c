#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

    

}