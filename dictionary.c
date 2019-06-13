// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    
    // node of the alphabet being computed
    node *current;
    
    // previous node for experimental purposes
    node *previous;
    
    char *alphabet = "abcdefghijklmnopqrstuvwxyz'";

    // Insert words into trie
    // fgets() = get the word in each line
    while (fgets(word, LENGTH + 1, file) != NULL)
    {
        // for each letter in the word
        for (int i = 0; i < strlen(word) - 1; i++)
        {
            // find the corresponding index of the letter in the string alphabet
            char *letter = strchr(alphabet, word[i]);
            int index = (int)(letter - alphabet);
            
            // for the first letter in each word 
            if (i == 0)
            {
                // allocate memory for the children
                if (!root->children[index])
                {
                    root->children[index] = malloc(sizeof(node));
                }
                // children of the root
                current = root->children[index];
            }
            
            // if not the first letter in word
            else
            {
                // previous node for experimental purposes
                previous = current;
                
                // if children node doesn't exist
                if (!current->children[index])
                {
                    current->children[index] = malloc(sizeof(node));
                }
                
                // update current to represent root->children->children....->children
                current = current->children[index];
            }
        }
        root->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
