#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (!(height > 0 && height < 9));

    int currentHeight = 1;
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }

        for (int j = 1; j < 3; j++)
        {
            for (int k = 1; k < currentHeight + 1; k++)
            {
                printf("#");
            }
            if (j == 1)
            {
                printf("  ");
            }

        }

        printf("\n");
        currentHeight++;
    }
}