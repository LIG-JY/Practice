#include "TopologicalSort.h"

void TopologicalSort( Vertex* V, Node** List ) // graph->vertices를 인자로 받음
{
    while ( V != NULL )
    {
        if (V->Visited == NotVisited)
            TS_DFS( V, List );
        /* 진입 간선이 없는 정점에 대해 DFS를 호출하는 것이 원리이다. 
        하지만 graph의 Vertices로 순회 그래프에 정점을 추가할 때, 즉 호출한 AddVertex의 순서로 순회 하도록 구현했다.
        예제에서는 AddVertex로 넣은 순서대로 V(A),V(B) 가 마침 진입 간선이 없는 정점이다. 
        결국 모든 Vertex에 대해 호출하지만, Visited 를 통해서 케이스를 줄여나간다.
        따라서 삽입 순서가 바뀌면 정렬을 제대로 못한다.*/
        V = V->Next; 
    }
}

void TS_DFS( Vertex* V, Node** List )
{
    Node* NewHead = NULL;
    Edge* E = NULL;

    V->Visited = Visited;

    E = V->AdjacencyList;

    while ( E != NULL ) // 종료조건: 간선 순회 종료. 즉 더 돌 간선이 없을 때
    {
        /* Edge(간선)마다 DFS 호출 */
        if ( E->Target != NULL && E->Target->Visited == NotVisited )
            TS_DFS( E->Target, List );

        E = E->Next; // 간선 순회 코드
    }

    printf("%c\n", V->Data );

    NewHead = SLL_CreateNode( V );
    SLL_InsertNewHead( List, NewHead );
}