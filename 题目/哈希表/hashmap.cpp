#include <iostream>

#define HASHSIZE 10
typedef unsigned int uint;
typedef struct Node
{
    const char * key;
    const char * value;
    Node * next;
}Node;

class HashNode
{
private:
    Node * node[HASHSIZE];

public:
    HashTable();
    uint hash(const char* key);
    Node* lookup(const char* key);
    bool install(const char* key,const char* value);
    const char* get(const char* key);
    void display();
};

HashTable::HashTable(){
    for (int i = 0; i < HASHSIZE; ++i)
    {
        node[i] = NULL;
    }
}

uint HashTable::hash(const char* key){
    uint hash=0;
    for (; *key; ++key)
    {
        hash=hash*33+*key;
    }
    return hash%HASHSIZE;
}

Node* HashTable::lookup(const char* key){
    Node *np;
    uint index;
    index = hash(key);
    for(np=node[index];np;np=np->next){
        if(!strcmp(key,np->key))
            return np;
    }
    return NULL;
}

bool HashTable::install(const char* key,const char* value){
    uint index;
    Node *np;
    if(!(np=lookup(key))){
        index = hash(key);
        np = (Node*)malloc(sizeof(Node));
        if(!np) return false;
        np->key=key;
        np->next = node[index];
        node[index] = np;
    }
    np->value=value;
    return true;
}