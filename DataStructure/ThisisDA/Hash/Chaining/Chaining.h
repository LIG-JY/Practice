#ifndef CHAINING_H
#define CHAINING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;

/* 노드 구조체 */
typedef struct tagNode
{
    KeyType   Key;
    ValueType Value;

    struct tagNode* Next;
} Node;

/* 노드로 연결리스트 만들기 */
typedef Node* List;

/* 테이블에 각 주소에 해당하는 연결리스트에 대한 포인터 올리기 */
typedef struct tagHashTable 
{
    int    TableSize;
    List*  Table;
} HashTable;

HashTable* CHT_CreateHashTable( int TableSize );
void       CHT_DestroyHashTable( HashTable* HT);

Node*      CHT_CreateNode( KeyType Key, ValueType Value );
void       CHT_DestroyNode( Node* TheNode );

void       CHT_Set( HashTable* HT, KeyType Key, ValueType Value );
ValueType  CHT_Get( HashTable* HT, KeyType Key );
int        CHT_Hash( KeyType Key, int KeyLength, int TableSize );

#endif
