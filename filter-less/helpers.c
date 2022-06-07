#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            if (sepBlue < 256)
            {
                image[i][j].rgbtBlue = sepBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
            if (sepGreen < 256)
            {
                image[i][j].rgbtGreen = sepGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepRed < 256)
            {
                image[i][j].rgbtRed = sepRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tempBlue;
    BYTE tempGreen;
    BYTE tempRed;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++)
        {
            tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = tempBlue;

            tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = tempGreen;

            tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = tempRed;

            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avgB;
    int avgG;
    int avgR;
    int surroundingCount;

    RGBTRIPLE imageCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgB = 0;
            avgG = 0;
            avgR = 0;
            surroundingCount = 0;

            avgB += imageCopy[i][j].rgbtBlue;
            avgG += imageCopy[i][j].rgbtGreen;
            avgR += imageCopy[i][j].rgbtRed;
            surroundingCount++;

            if (i + 1 < height)
            {
                avgB += imageCopy[i + 1][j].rgbtBlue;
                avgG += imageCopy[i + 1][j].rgbtGreen;
                avgR += imageCopy[i + 1][j].rgbtRed;
                surroundingCount++;
            }
            if (j + 1 < width)
            {
                avgB += imageCopy[i][j + 1].rgbtBlue;
                avgG += imageCopy[i][j + 1].rgbtGreen;
                avgR += imageCopy[i][j + 1].rgbtRed;
                surroundingCount++;
            }
            if (i - 1 >= 0)
            {
                avgB += imageCopy[i - 1][j].rgbtBlue;
                avgG += imageCopy[i - 1][j].rgbtGreen;
                avgR += imageCopy[i - 1][j].rgbtRed;
                surroundingCount++;
            }
            if (j - 1 >= 0)
            {
                avgB += imageCopy[i][j - 1].rgbtBlue;
                avgG += imageCopy[i][j - 1].rgbtGreen;
                avgR += imageCopy[i][j - 1].rgbtRed;
                surroundingCount++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                avgB += imageCopy[i + 1][j + 1].rgbtBlue;
                avgG += imageCopy[i + 1][j + 1].rgbtGreen;
                avgR += imageCopy[i + 1][j + 1].rgbtRed;
                surroundingCount++;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                avgB += imageCopy[i - 1][j + 1].rgbtBlue;
                avgG += imageCopy[i - 1][j + 1].rgbtGreen;
                avgR += imageCopy[i - 1][j + 1].rgbtRed;
                surroundingCount++;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                avgB += imageCopy[i + 1][j - 1].rgbtBlue;
                avgG += imageCopy[i + 1][j - 1].rgbtGreen;
                avgR += imageCopy[i + 1][j - 1].rgbtRed;
                surroundingCount++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                avgB += imageCopy[i - 1][j - 1].rgbtBlue;
                avgG += imageCopy[i - 1][j - 1].rgbtGreen;
                avgR += imageCopy[i - 1][j - 1].rgbtRed;
                surroundingCount++;
            }
            image[i][j].rgbtBlue = round(avgB / (double)surroundingCount);
            image[i][j].rgbtGreen = round(avgG / (double)surroundingCount);
            image[i][j].rgbtRed = round(avgR / (double)surroundingCount);
        }
    }
    return;
}
