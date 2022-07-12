// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 + 26;

// Hash table
node *table[N]; // array of pointers



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // printf("word=%s: ", word);
    unsigned int i = hash(word);
    // printf("i=%i, word=%s - ", i, word);
    node *tmp = table[i];
    // printf("is OK\n");
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        else if (strcasecmp(tmp->word, word) < 0)
        {
            return false;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // // TODO: Improve this hash function
    int a1 = toupper(word[0]) - 'A';
    int a2 = 0;
    if (strlen(word) > 1)
    {
        a2 = toupper(word[1]) - 'A';
        return 27 * a1 + a2 + 1;
    }
    else
    {
        a2 = -1;
    }
    // printf("word=%s, w[0]=%c, w[1]=%c, hash=%i\n", word, word[0], word[1], 27 * a1 + a2 + 1);
    return 27 * a1 + a2 + 1;
    // printf("hash call: word=%s, w[0]=%c, w[1]=%c, hash=%i\n", word, word[0], word[1], a1);
    // return toupper(word[0]) - 'A';
}

void print_linked_list(node *n)
{
    while (n != NULL)
    {
        printf("%s ", n->word);
        n = n->next;
    }
    printf("\n");
}

// void print_table(node *t[])
// {
//     printf("table:\n");
//     int count=0;
//     for (int i = 0; i < N; i++)
//     {
//         printf("%i - ", i);
//         print_linked_list(t[i]);
//         count++;
//         if (count >=3) break;
//     }
// }

bool load(const char *dictionary)
{
    // TODO
    FILE *file_dict_ptr = fopen(dictionary, "r");
    if (file_dict_ptr == NULL)
    {
        // fclose(file_dict_ptr);
        printf("Can't open dict file");
        return false;
    }

    // read words from dictionary (lexicographical order)
    // add to it to the hash table
    char c;
    int index = 0;
    node *n;
    while (fread(&c, sizeof(char), 1, file_dict_ptr))
    {
        if (index == 0)
        {
            n = malloc(sizeof(node));
            n->next = NULL;
        }
        if (n == NULL)
        {
            // free(n);
            // free_table(table);
            unload();
            return false;
        }

        if (c != '\n') // not end of the word
        {
            n->word[index] = c;
            index++;
        }
        else
        {
            n->word[index]='\0';
            // for (int j = index; j < LENGTH + 1; j++)
            // {
            //     n->word[j] = '\0';
            // }
            char *w = n->word;
            if (table[hash(w)] == NULL)
            {
                table[hash(w)] = n;
            }
            else
            {
                node *tmp = table[hash(w)];
                table[hash(w)] = n;
                table[hash(w)]->next = tmp;
            }
            index = 0;
        }
    }
    fclose(file_dict_ptr);

    // print_table(table);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    node *tmp = NULL;
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        while (tmp != NULL)
        {
            count++;
            tmp = tmp->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
