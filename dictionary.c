// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;


// Hash table
node *table[N];










//hashing function
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash_value = toupper(word[0]) - 'A';
    return hash_value;
}









// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Scans dictionary word by word (populating hash table with nodes containing words found in dictionary)
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Mallocs a node for each new word (i.e., creates node pointers)
        node *new_node = malloc(sizeof(node));
        // Checks if malloc succeeded, returns false if not
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // Copies word into node if malloc succeeds
        strcpy(new_node->word, word);

        // Initializes & calculates index of word for insertion into hashtable
        int h = hash(new_node->word);

        // Initializes head to point to hashtable index/bucket
        node *head = table[h];

        // Inserts new nodes at beginning of lists
        if (head == NULL)
        {
            table[h] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = table[h];
            table[h] = new_node;
            word_count++;
        }
    }
    fclose(file);
    return true;
}






// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    // TODO
    return word_count;
}







// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    int hash_value = hash(word);
    // Access linked list at that index in hash table
    node *cursor = table[hash_value];
    // Traverse linked list, looking for word (strcasecomp)
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
return false;
}







// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp,*cursor;
    for(int i = 0; i < 26; i++)
    {
        tmp = table[i];
        cursor = table[i];
        
        while(cursor == NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
            
        }
    }
    return true;
}  