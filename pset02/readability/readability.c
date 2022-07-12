#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // L is the average number of letters per 100 words
    float L = letters / (float)words * 100;
    // S is the average number of sentences per 100 words
    float S = sentences / (float)words * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("index: %f\n", index);
    // printf("letters: %i, words: %i, sentences: %i\n", letters, words, sentences);

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", (int)round(index));
    }
    printf("\n");
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if isalpha(text[i])
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if isspace(text[i])
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}