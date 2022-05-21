#include <stdio.h>
#include <cs50.h>

int main(void)
{

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
}