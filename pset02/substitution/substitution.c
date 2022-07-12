#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_alpha(string s);
bool only_26chars(string s);
bool only_noduplicated_chars(string s);
char translate(char c, string s);

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Make sure every character in argv[1] is alpha
    if (!only_alpha(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Make sure that characters in argv[1] are 26
    if (!only_26chars(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Make sure that no duplicated characters in argv[1]
    if (!only_noduplicated_chars(argv[1]))
    {
        printf("Key must be different characters.\n");
        return 1;
    }

    // get alphabet
    string alphabet = argv[1];

    // Prompt user for plaintext
    string text = get_string("plaintext: ");

    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        // Rotate the character if it's a letter
        printf("%c", translate(text[i], alphabet));
    }
    printf("\n");
}

bool only_alpha(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool only_26chars(string s)
{
    return strlen(s) == 26;
}

bool only_noduplicated_chars(string s)
{
    for (int i = 0; i < strlen(s) - 1; i++)
    {
        for (int j = i + 1; j < strlen(s); j++)
        {
            if (tolower(s[i]) == tolower(s[j]))
            {
                return false;
            }
        }
    }
    return true;
}

char translate(char c, string s)
{
    if (islower(c))
    {
        for (int i = 0; i < strlen(s); i++)
        {
            int shift = (int)('a');
            if (c == shift + i)
            {
                return tolower(s[i]);
            }
        }
    }
    else if (isupper(c))
    {
        for (int i = 0; i < strlen(s); i++)
        {
            int shift = (int)('A');
            if (c == shift + i)
            {
                return toupper(s[i]);
            }
        }
    }
    return c;
}