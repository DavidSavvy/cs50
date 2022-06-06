// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    uint8_t *pHeader = malloc(HEADER_SIZE);
    fread(pHeader, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(pHeader, sizeof(uint8_t), HEADER_SIZE, output);

    //printf("%ld\n", ftell(input));

    uint16_t sample;

    //uint16_t *pSample = malloc(sizeof(uint16_t));
    uint16_t *pSample = &sample;

    uint16_t location;
    /*
    while ((location = fread()) != EOF)
    {
        fread(pSample, sizeof(uint16_t), 1, input);
        *pSample *= factor;
        fwrite(pSample, sizeof(uint16_t), 1, output);
    }
    */


    do
    {
        printf("%ld\n", ftell(input));

        fread(pSample, sizeof(uint16_t), 1, input);
        *pSample *= factor;
        fwrite(pSample, sizeof(uint16_t), 1, output);
    }
    while (*pSample != (uint16_t)(EOF));


    /*
   while (true)
    {
        fread(pSample, sizeof(uint16_t), 1, input);
        if (*pSample == (uint16_t)(EOF))
        {
            break;
        }
        *pSample *= factor;
        fwrite(pSample, sizeof(uint16_t), 1, output);
    }
    */

    // TODO: Read samples from input file and write updated data to output file

    // Close files
    free(pHeader);
    free(pSample);
    fclose(input);
    fclose(output);
}
