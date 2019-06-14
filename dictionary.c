// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N + 1];
}
node;

void clearmemory(node *curr);

// Represents a trie
node *root;

// num of words in dictionary
int numWords = 0;

// node of the alphabet being computed
node *current;
    
// index of current word
int index;

char *alphabet = "abcdefghijklmnopqrstuvwxyz'";

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // num of words immediately after opening a new dicionary is 0; 
    numWords = 0;
    
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
    
    // Insert words into trie
    // fgets() = get the word in each line
    while (fgets(word, LENGTH, file) != NULL)
    {
        // for each letter in the word
        for (int i = 0; i < strlen(word) - 1; i++)
        {
            // find the corresponding index of the letter in the string alphabet
            if (word[i] != '\'')
            {
                char *letter = strchr(alphabet, word[i]);
                index = (int)(letter - alphabet);
            }
            else
            {
                index = 27;
            }
            
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
                // if children node doesn't exist
                if (!current->children[index])
                {
                    current->children[index] = malloc(sizeof(node));
                }
                
                // update current to represent root->children->children....->children
                current = current->children[index];
            }
        }
        current->is_word = true;
        numWords += 1;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (numWords != 0)
    {
        return numWords;
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        // change to lower case
        char currletter = tolower(word[i]);
        
        // find the corresponding index of the letter in the string alphabet
            if (word[i] != '\'')
            {
                char *letter = strchr(alphabet, word[i]);
                index = (int)(letter - alphabet);
            }
            else
            {
                index = 27;
            }
        
        if (i == 0)
        {
            // if the first letter is not in the alphabet or isn't a semicolon
            if (!root->children[index])
            {
                return false;
            }
            else
            {
                current = root->children[index];
            }
        }
        else
        {
            if (!current->children[index])
            {
                return false;
            }
            else
            {
                current = current->children[index];
            }
        }
    }
    if (current->is_word == false)
    {
        return false;
    }
    return true;
}

void clearmemory(node *curr)
{
    for (int i = 0; i < N; i++)
    {
        if (curr->children[i] != NULL)
        {
            clearmemory(curr->children[i]);
        }
    }
    free(curr);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    clearmemory(root);
    return true;
}
