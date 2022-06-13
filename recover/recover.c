#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const int BLOCKSIZE = 512;
    if (argc != 2)
    {
        printf("Usage: ./recover infile.raw");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Invalid file");
        return 1;
    }
    
}