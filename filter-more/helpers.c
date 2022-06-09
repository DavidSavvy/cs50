#include "helpers.h"
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };



    RGBTRIPLE imageCpy[height][width];

    memcpy(imageCpy, image, sizeof(RGBTRIPLE) * (height * width));

    /*
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCpy[i][j] = image[i][j];
        }
    }
    */
    int sobxRed ;
    int sobxGreen;
    int sobxBlue;

    int sobyRed ;
    int sobyGreen;
    int sobyBlue;

    int sobRed;
    int sobGreen;
    int sobBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobxRed = 0;
            sobxGreen = 0;
            sobxBlue = 0;
            sobyRed = 0;
            sobyGreen = 0;
            sobyBlue = 0;
            sobRed = 0;
            sobGreen = 0;
            sobBlue = 0;
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= i + 1; col++)
                {
                    if (row > -1 && row < height && col > -1 && col < width)
                    {
                        sobxRed += (image[row][col].rgbtRed * gx[row - i + 1][col - i + 1]);
                        sobyRed += (image[row][col].rgbtRed * gy[row - i + 1][col - i + 1]);
                        sobRed = sqrt(sobxRed^2 + sobyRed^2);
                        sobRed = round(sobRed);
                        if (sobRed > 255)
                        {
                            sobRed = 255;
                        }

                        sobxGreen += (image[row][col].rgbtGreen * gx[row - i + 1][col - i + 1]);
                        sobyGreen += (image[row][col].rgbtGreen * gy[row - i + 1][col - i + 1]);
                        sobGreen = sqrt(sobxGreen^2 + sobyGreen^2);
                        sobGreen = round(sobGreen);
                        if (sobGreen > 255)
                        {
                            sobGreen = 255;
                        }

                        sobxBlue += (image[row][col].rgbtBlue * gx[row - i + 1][col - i + 1]);
                        sobyBlue += (image[row][col].rgbtBlue * gy[row - i + 1][col - i + 1]);
                        sobBlue = sqrt(sobxBlue^2 + sobyBlue^2);
                        sobBlue = round(sobBlue);
                        if (sobBlue > 255)
                        {
                            sobBlue = 255;
                        }

                    }

                }
            }
            imageCpy[i][j].rgbtRed = sobRed;
            imageCpy[i][j].rgbtGreen = sobGreen;
            imageCpy[i][j].rgbtBlue = sobBlue;
        }
    }
    memcpy(image, imageCpy, sizeof(RGBTRIPLE) * (height * width));



    return;
}
