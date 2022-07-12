#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string text = get_string("plaintext: ");

    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        // Rotate the character if it's a letter
        printf("%c", rotate(text[i], key));
    }
    printf("\n");
}

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    if (islower(c))
    {
        int shift = (int)('a');
        return (char)((c - shift + n) % 26 + shift);
    }
    else if (isupper(c))
    {
        int shift = (int)('A');
        return (char)((c - shift + n) % 26 + shift);
    }
    return c;
}