#include "GraphTraversal.h"

void DFS( Vertex* V )
{
    Edge* E = NULL;

    printf("%d ", V->Data);

    V->Visited = Visited;

    E = V->AdjacencyList;

    while ( E != NULL )
    {
        if ( E->Target != NULL && E->Target->Visited == NotVisited )
            DFS( E->Target );

        E = E->Next;
    }
}

void BFS( Vertex* V, LinkedQueue* Queue )
{
    Edge* E = NULL;

    printf("%d ", V->Data);
    /* 방문표시 */
    V->Visited = Visited;
    
    /* 큐에 Vertex 삽입 */ 
    LQ_Enqueue( Queue, LQ_CreateNode( V ) );

    /* 큐가 비었는지 확인 */
    while ( !LQ_IsEmpty( Queue ) )
    {
    /* 큐가 비어있지 않다면, 큐에서 빼고 인접 Edge(같은 깊이) 반복 */
        Node* Popped = LQ_Dequeue( Queue );
        V = Popped->Data;
        E = V->AdjacencyList;

        while ( E != NULL )
        {   
            /* 다음 방문할 Vertex 조사 */
            V = E->Target;

            if ( V != NULL && V->Visited == NotVisited )
            {
                printf("%d ", V->Data);
                V->Visited = Visited;
                LQ_Enqueue( Queue, LQ_CreateNode( V ) );
            }
            /* 반복 하게 Edge 밀어주기 */
            E = E->Next;
        }
    }
}
