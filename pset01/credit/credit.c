#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

    int digit = 0;
    int previous_digit = 0;
    int count = 0;
    int sum = 0;
    while (n > 0)
    {
        previous_digit = digit;
        digit = n % 10;
        n = n / 10;
        count++;

        if (count % 2 == 0)
        {
            digit = digit * 2;
        }

        sum += digit / 10 + digit % 10;

        if (count % 2 == 0)
        {
            digit = digit / 2;
        }
    }

    // printf("sum=%i, digit=%d, previous_digit=%d, count=%i\n", sum, digit, previous_digit, count);

    if (sum % 10 == 0)
    {
        if ((digit == 3) && ((previous_digit == 4) || (previous_digit == 7)) && (count == 15))
        {
            printf("AMEX\n");
        }
        else if ((digit == 4) && ((count == 13) || (count == 16)))
        {
            printf("VISA\n");
        }
        else if ((digit == 5) && ((previous_digit >= 1) && (previous_digit <= 5)) && (count == 16))
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