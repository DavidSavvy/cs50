#include <cs50.h>
#include <stdio.h>

bool Luhn(long creditCardNumber);

int main(void)
{
    long number = get_long("Number: ");
    long tempNumber = number;

    if (Luhn(number))
    {

        if (number / 10000000000000 == 34 || number / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (number / 1000000000000 == 4 || number / 1000000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (number / 100000000000000 == 51 || number / 100000000000000 == 52 || number / 100000000000000 == 53
                 || number / 100000000000000 == 54 || number / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}

bool Luhn(long creditCardNumber)
{
    int sum = 0;
    int remainder;
    int count = 1;
    int countLocal = 1;
    long localTempNumber = creditCardNumber;

    while (creditCardNumber != 0)
    {
        if (count % 2 == 1)
        {
            creditCardNumber /= 10;
            count++;
        }
        else if (count % 2 == 0)
        {

            int remainder2;
            remainder = creditCardNumber % 10;
            remainder *= 2;

            if (remainder % 10 != 0 || remainder == 10)
            {
                remainder2 = remainder % 10;
                sum += remainder2;
                remainder /= 10;
                sum += remainder;
            }
            else
            {
                sum += remainder;
            }

            creditCardNumber /= 10;
            count++;
        }
    }

    while (localTempNumber)
    {
        if (countLocal % 2 == 1)
        {
            remainder = localTempNumber % 10;
            sum += remainder;
            localTempNumber /= 10;
            countLocal++;
        }
        else
        {
            localTempNumber /= 10;
            countLocal++;
        }
    }

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }


}