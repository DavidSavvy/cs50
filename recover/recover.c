#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
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
    BYTE *buffer = malloc(BLOCKSIZE);
    if (buffer == NULL)
    {
        return 1;
    }
    fread(buffer, sizeof(BYTE), BLOCKSIZE, file);
}