#include <stdio.h>
#include <cs50.h>

bool valid_triangle(int a, int b, int c);

int main(void)
{
    int sideA = get_int("Side A: ");
    int sideB = get_int("Side B: ");
    int sideC = get_int("Side C: ");

    bool isTriangle = valid_triangle(sideA,sideB,sideC);

    if (isTriangle)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }



}

bool valid_triangle(int a, int b, int c)
{
    if (a > 0 && b > 0 && c > 0)
    {
        if (a + b > c && a + c > b && b + c > a)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}