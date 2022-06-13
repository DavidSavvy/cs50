#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <cs50.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    const int BLOCKSIZE = 512;
    int jpgN = 0;
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

    char *name = malloc(8);
    FILE *image = NULL;
    int isJPG = 0;
    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, file) == BLOCKSIZE)
    {
        printf("%i\n", ftell(file));
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            if (!isJPG)
            {
                sprintf(name, "%03i.jpg", jpgN);
                image = fopen(name, "w");
                fwrite(file, sizeof(BYTE), BLOCKSIZE, image); //might need to take next block
                jpgN++;
                isJPG = 1;
            }
            else if (isJPG)
            {
                fclose(image);
                sprintf(name, "%03i.jpg", jpgN);
                image = fopen(name, "w");
                fwrite(file, sizeof(BYTE), BLOCKSIZE, image);
                jpgN++;
            }



        }
        else if (isJPG)
        {
            fwrite(file, sizeof(BYTE), BLOCKSIZE, image);
        }
    }
    free(name);
    fclose(image);

}