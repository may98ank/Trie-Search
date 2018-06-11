/**
 * Implements a dictionary's functionality.
 */
#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include "dictionary.h"

// Make a Structure for Trie
typedef struct Node{
    bool Isword;
    struct Node* children[27];
}Node;
// A integer to count words
int numWords = 0;
// A root node to remember the starting point of Trie
Node* root;
// Some Helper Function
void unloadHelp(Node* node);

bool addWord( Node* node, char* word, int vdx);

bool checkHelp( Node* node,const char* word, int vdx);

void Getinitialized(Node* node){
    node->Isword = false;
    for(int i = 0; i < 27; i++){
        node->children[i] = NULL;
    }
}

//Some Helper Function

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    return checkHelp( root, word, 0);
}

bool checkHelp( Node* node,const char* word, int vdx){
    if(word[vdx] == '\0'){
        return node->Isword;
    }
    char ch = word[vdx];
    if(ch >= 65 && ch <= 90){
        ch = ch - 65 + 97;
    }else if(ch == '\''){
        ch = 26 + 97;
    }
    Node* child = node->children[ch - 97];
    if(child != NULL){
        return checkHelp( child, word, vdx + 1);
    }else{
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    const char* input = dictionary;
    // Open the Input Dictionary
    FILE* inptr = fopen(input, "r");
    
    //Check for Success
    if(inptr == NULL){
        fclose(inptr);
        return false;
    }
    
    // Making First Node i.e. Root
    root = malloc(sizeof(Node));
    Getinitialized(root);
    // Check For Success
    if(root == NULL){
        fclose(inptr);
        return false;
    }
    char* word = malloc(sizeof(char)*46);
    while(fscanf( inptr, "%s", word) != EOF){
        // Do Work
        Node* node = root;
        int i = 0;
        while(word[i] != '\0'){
            char ch = word[i];
            if(ch == '\''){
                ch = 26 + 97;
            }
            if(node->children[ch-97] == NULL){
                Node* child = malloc(sizeof(Node));
                Getinitialized(child);
                if(child == NULL){
                    return false;
                }
                node->children[ch-97] = child;
                node = node->children[ch-97];
                i++;
            }else{
                node = node->children[ch-97];
                i++;
            }
        }
        node->Isword = true;
        numWords++;
    }
    free(word);
    // close the Dictionary
    fclose(inptr);
    // return to main with Boolean Result
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return numWords;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    unloadHelp(root);
    return true;
}

void unloadHelp(Node* node){
    for(int i = 0; i < 27; i++){
        Node* child = node->children[i];
        if(child != NULL){
            unloadHelp(child);
        }
    }
    free(node);
    
    
}
