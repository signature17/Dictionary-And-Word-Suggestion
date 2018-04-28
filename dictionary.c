
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define ALPHABET_SIZE 26

#define false 0
#define true 1

struct trie tree;

struct trie_node
{
    char *value;

    struct trie_node *children[ALPHABET_SIZE];
     //bool isWordEnd;
};

struct trie
{
    struct trie_node root;
};


int letter_to_int(char letter)
{
    if (letter>='A'&&letter<='Z')
    {
        return letter - 'A' + 26;
    }
    else if (letter>='a'&&letter <='z')
    {
        return letter -'a';
    }
    return -1;
}


void print_invalid_word(const char *word, int index)
{
    printf("  word: \"%s\"\n", word);
    printf("         ");
    int i;
    for (i = 0;i<index;i++)
    {
        printf(" ");
    }
    printf("^\n");
}


int trie_insert(struct trie_node *node, const char *word, char *description)
{
    int i;
    for (i = 0;i<strlen(word);i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter==-1)
        {

            printf("failed to insert due to invalid character in word\n");
            print_invalid_word(word, i);
            printf("  description: \"%s\"\n", description);
            return false;
        }

        struct trie_node *parent = node;
        node = node->children[letter];

        if (!node)
        {
            node = malloc(sizeof(struct trie_node));
            //node -> children = (trie_node *)malloc( 26 * sizeof(trie_node*));
            parent->children[letter] = node;
        }
    }


    int len = strlen(description);
    node->value = malloc(len + 1);
    strncpy(node->value,description,len);
    return true;
}


char *trie_get(struct trie_node *node, const char *word)
{
    int i;
    for (i = 0;i<strlen(word);i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter == -1)
        {
            return false;
        }

        node = node->children[letter];
        if (!node)
        {
            return false; 
        }
    }
    return node->value;
}

void dictionary_initialise()
{
    tree = (struct trie) {}; 
}

int dictionary_read_from_file(const char * filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("could not find/open file \"%s\"\n",filename);
        return false;
    }

    char word[MAX_WORD_SIZE];
    char desc[MAX_DESC_SIZE];

    int count = 0;

    while (fscanf(file,"%s %[^\n]",word,desc) > 1)
    {
        if (!trie_insert(&tree.root, word, desc))
        {
            fclose(file);
            return false;
        }
        else
        {
            count++;
        }
    }

    fclose(file);
    printf("parsed file \"%s\" with %i entries\n", filename, count);
    return true;
}

int dictionary_lookup(const char *word, char *meaning)
{
    int i;
    for (i = 0;i<strlen(word);i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter == -1)
        {
            printf("invalid character in word\n");
            print_invalid_word(word, i);
            return false;
        }
    }
    char *description = trie_get(&tree.root, word);

    if (!description)
    {
        return false;
    }

    strcpy(meaning, description);

    return true;
}
