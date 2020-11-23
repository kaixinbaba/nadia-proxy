#include "hashmap.h"

MAP_INSTANCE *init_hashmap(unsigned int size){
    if(size <=0){
        size = DEFAULT_INITIAL_CAPACITY;
    }
    NODE **nodes = calloc(size,sizeof(NODE*));
    MAP_INSTANCE *map = malloc(sizeof(MAP_INSTANCE));
    map->size = size;
    map->nodes = nodes;
    map->put = &put_hashmap;
    map->get = &get_hashmap;
    return map;
}

//todo 需要考虑并发安全
void put_hashmap(MAP_INSTANCE *map ,int key,void *value){
    fprintf(stderr, "into put_hashmap key=%d \n", key);
    int hashcode = hash(map,key);
    NODE *headNode = map->nodes[hashcode];
    if(headNode == NULL){
        fprintf(stderr, "put_hashmap create new node hashcode=%d key=%d \n", hashcode,key);
        NODE *node = malloc(sizeof(NODE));
        node->data = value;
        node->hash = hashcode;
        node->key = key;
        node->next = NULL;
        map->nodes[hashcode] = (NODE *)&node;
    }else{
        while (1){
            NODE *entry = headNode;
            if(entry->hash == hashcode && entry->key == key){
                fprintf(stderr, "put_hashmap update node hashcode=%d key=%d \n", hashcode,key);
                entry->data = value;
                return;
            }else if(entry == NULL){
                fprintf(stderr, "put_hashmap insert node hashcode=%d key=%d \n", hashcode,key);
                NODE *newNode = malloc(sizeof(NODE));
                newNode->data = value;
                newNode->hash = hashcode;
                newNode->key = key;
                newNode->next = headNode;
                map->nodes[hashcode] = newNode;
                return;
            }
            entry = entry->next;
        }
    }
}

//todo 需要考虑并发安全
void *get_hashmap(MAP_INSTANCE *map ,int key){
    fprintf(stderr, "get_hashmap key=%d \n", key);
    int hashcode = hash(map,key);
    NODE *headNode = map->nodes[hashcode];
    if(headNode == NULL){
        return NULL;
    }else{
        while(1){
            NODE *entry = headNode;
            fprintf(stderr, "entry hash=%d key=%d \n", entry->hash,entry->key);
            if(entry->hash == hashcode && entry->key == key){
                return entry->data;
            }else if(entry == NULL){
                return NULL;
            }
            entry = entry->next;
        }
    }
}

int hash(MAP_INSTANCE *map ,int key){
    unsigned int size = map->size;
    return key % size;
}