#include "helpers.h"
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int row = 0; row < height; row++)
    {
        for (int i = 0, j = width - 1; i < j; i++)
        {
            BYTE tempR = image[row][i].rgbtRed;
            BYTE tempG = image[row][i].rgbtGreen;
            BYTE tempB = image[row][i].rgbtBlue;

            image[row][i].rgbtRed = image[row][j].rgbtRed;
            image[row][j].rgbtRed = tempR;

            image[row][i].rgbtGreen = image[row][j].rgbtGreen;
            image[row][j].rgbtGreen = tempG;

            image[row][i].rgbtBlue = image[row][j].rgbtBlue;
            image[row][j].rgbtBlue = tempB;

            j--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];
    memcpy(imageCpy, image, sizeof(RGBTRIPLE) * (width * height));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgR = 0;
            int avgG = 0;
            int avgB = 0;
            int count = 0;
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    if (row > -1 && row < height && col > -1 && col < width)
                    {
                        avgR += imageCpy[row][col].rgbtRed;
                        avgG += imageCpy[row][col].rgbtGreen;
                        avgB += imageCpy[row][col].rgbtBlue;
                        count++;
                    }
                }
            }
            avgR /= (double)count;
            avgR = round(avgR);
            if (avgR > 255)
            {
                avgR = 255;
            }
            avgG /= (double)count;
            avgG = round(avgG);
            if (avgG > 255)
            {
                avgG = 255;
            }
            avgB /= (double)count;
            avgB = round(avgB);
            if (avgB > 255)
            {
                avgB = 255;
            }
            image[i][j].rgbtRed = (BYTE)avgR;
            image[i][j].rgbtGreen = (BYTE)avgG;
            image[i][j].rgbtBlue = (BYTE)avgB;
        }
    }
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

    int sobxRed;
    int sobxGreen;
    int sobxBlue;

    int sobyRed;
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
                for (int col = j - 1; col <= j + 1; col++)
                {
                    if (row > -1 && row < height && col > -1 && col < width)
                    {
                        sobxRed += (imageCpy[row][col].rgbtRed * gx[row - i + 1][col - j + 1]);
                        sobyRed += (imageCpy[row][col].rgbtRed * gy[row - i + 1][col - j + 1]);

                        sobxGreen += (imageCpy[row][col].rgbtGreen * gx[row - i + 1][col - j + 1]);
                        sobyGreen += (imageCpy[row][col].rgbtGreen * gy[row - i + 1][col - j + 1]);

                        sobxBlue += (imageCpy[row][col].rgbtBlue * gx[row - i + 1][col - j + 1]);
                        sobyBlue += (imageCpy[row][col].rgbtBlue * gy[row - i + 1][col - j + 1]);
                    }
                }
            }
            sobRed = pow(sobxRed, 2) + pow(sobyRed, 2);
            sobRed = round(sqrt((double)sobRed));
            if (sobRed > 255)
            {
                sobRed = 255;
            }

            sobGreen = pow(sobxGreen, 2) + pow(sobyGreen, 2);
            sobGreen = round(sqrt((double)sobGreen));
            if (sobGreen > 255)
            {
                sobGreen = 255;
            }

            sobBlue = pow(sobxBlue, 2) + pow(sobyBlue, 2);
            sobBlue = round(sqrt((double)sobBlue));
            if (sobBlue > 255)
            {
                sobBlue = 255;
            }

            image[i][j].rgbtRed = sobRed;
            image[i][j].rgbtGreen = sobGreen;
            image[i][j].rgbtBlue = sobBlue;
        }
    }
    return;
}
