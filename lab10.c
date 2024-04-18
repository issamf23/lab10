#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

struct TrieNode
{
    int count;
    struct TrieNode *children[ALPHABET_SIZE];
};

struct Trie
{
    struct TrieNode *root;
};

struct TrieNode *createNode()
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (index < 0 || index >= ALPHABET_SIZE)
        {
            continue;
        }
        if (current->children[index] == NULL)
        {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct TrieNode *current = pTrie->root;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (index < 0 || index >= ALPHABET_SIZE)
        {
            return 0;
        }
        if (current->children[index] == NULL)
        {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

void deallocateNode(struct TrieNode *node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        deallocateNode(node->children[i]);
    }

    free(node);
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    deallocateNode(pTrie->root);
    free(pTrie);
    return NULL;
}

struct Trie *createTrie()
{
    struct Trie *newTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (newTrie == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newTrie->root = createNode();
    return newTrie;
}

void processInput(struct Trie *pTrie)
{
    int numWords;
    scanf("%d", &numWords);

    char word[100];
    for (int i = 0; i < numWords; i++)
    {
        scanf("%s", word);
        insert(pTrie, word);
    }
}

void queryTrie(struct Trie *pTrie)
{
    char *pWords[] = {"not", "note", "ucf", "notaword", "notawordeither", "notaword", "ucf", "note", "ucf", "notawordeithereither", "not", "ucf"};
    int numQueries = sizeof(pWords) / sizeof(pWords[0]);

    for (int i = 0; i < numQueries; i++)
    {
        printf("%s %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
}

int main(void)
{
    struct Trie *pTrie = createTrie();

    processInput(pTrie);

    queryTrie(pTrie);

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
    {
        printf("There is an error in this program.\n");
    }

    return 0;
}