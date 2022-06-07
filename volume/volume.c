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

    int16_t sample;
    int16_t *pSample = &sample;

    long start;
    long end;
    while (true)
    {
        start = ftell(input);
        fread(pSample, sizeof(int16_t), 1, input);
        end = ftell(input);

        if (start == end)
        {
            break;
        }

        *pSample *= factor;
        fwrite(pSample, sizeof(int16_t), 1, output);
    }
    // TODO: Read samples from input file and write updated data to output file

    // Close files
    free(pHeader);
    fclose(input);
    fclose(output);
}
