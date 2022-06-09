#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void blur(int height, int width, int image[3][3][3]);




int main(void)
{
    int image[3][3][3] =
    {
        {
            {
                255, 0, 0
            },
            {
                128, 0, 128
            },
            {
                0, 0, 255
            }
        },
        {
            {
                255, 0, 0
            },
            {
                128, 0, 128
            },
            {
                0, 0, 255
            }
        },
        {
            {
                255, 0, 0
            },
            {
                128, 0, 128
            },
            {
                0, 0, 255
            }
        }
    };


    
    return 0;
}








// Detect edges
void edges(int height, int width, int image[3][3][3])
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



    int imageCpy[height][width][3];

    //memcpy(imageCpy, image, sizeof(RGBTRIPLE) * (height * width));


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCpy[i][j][0] = image[i][j][0];
            imageCpy[i][j][1] = image[i][j][1];
            imageCpy[i][j][2] = image[i][j][2];
        }
    }

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
                for (int col = j - 1; col <= i + 1; col++)
                {
                    if (row > -1 && row < height && col > -1 && col < width)
                    {
                        sobxRed += (imageCpy[row][col][2] * gx[row - i + 1][col - i + 1]);
                        sobyRed += (imageCpy[row][col][2] * gy[row - i + 1][col - i + 1]);

                        sobxGreen += (imageCpy[row][col][1] * gx[row - i + 1][col - i + 1]);
                        sobyGreen += (imageCpy[row][col][1] * gy[row - i + 1][col - i + 1]);



                        sobxBlue += (imageCpy[row][col][0]* gx[row - i + 1][col - i + 1]);
                        sobyBlue += (imageCpy[row][col][0] * gy[row - i + 1][col - i + 1]);

                    }

                }
            }
            sobRed = sqrt((sobxRed^2 + sobyRed^2) * 1.0);
            sobRed = round(sobRed);
            if (sobRed > 255)
            {
                sobRed = 255;
            }

            sobGreen = sqrt((sobxGreen^2 + sobyGreen^2) * 1.0);
            sobGreen = round(sobGreen);
            if (sobGreen > 255)
            {
                sobGreen = 255;
            }

            sobBlue = sqrt((sobxBlue^2 + sobyBlue^2) * 1.0);
            sobBlue = round(sobBlue);
            if (sobBlue > 255)
            {
                sobBlue = 255;
            }
            image[i][j][2] = sobRed;
            image[i][j][1] = sobGreen;
            image[i][j][0] = sobBlue;
        }
    }




    return;
}
