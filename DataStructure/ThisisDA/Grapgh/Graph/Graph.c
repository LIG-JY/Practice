#include "Graph.h"

Graph* CreateGraph()
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->Vertices = NULL; // 정점 리스트에 대한 포인터.
    graph->VertexCount = 0; // 정점 수
    return graph;
}

void DestroyGraph(Graph* G)
{
    while (G->Vertices != NULL)
    {
        Vertex* Vertices = G->Vertices->Next;        
        DestroyVertex(G->Vertices);
        G->Vertices = Vertices;        
    }
    free(G);
}

Vertex* CreateVertex(VElementType Data)
{
    Vertex* V = (Vertex*)malloc(sizeof(Vertex));
    
    V->Data = Data;
    V->Next = NULL;
    V->AdjacencyList = NULL;
    V->Visited = NotVisited;
    V->Index = -1;

    return V;
}

void DestroyVertex( Vertex* V )
{
    while (V->AdjacencyList != NULL)
    {
        Edge* Edge = V->AdjacencyList->Next;
        DestroyEdge(V->AdjacencyList);
        V->AdjacencyList = Edge;
    }
    free(V);    
}

/* 단방향임 From -> Target */
Edge*   CreateEdge(Vertex* From, Vertex* Target, int Weight)
{
    Edge* E   = (Edge*)malloc(sizeof(Edge));
    E->From   = From;
    E->Target = Target;
    E->Next   = NULL;
    E->Weight = Weight;

    return E;
}

void    DestroyEdge(Edge* E)
{
    free(E);
}

void AddVertex(Graph* G, Vertex* V)
{
    /* 그래프 구조체에 Vertice의 목록에 추가 */
    Vertex* VertexList = G->Vertices;

    if (VertexList == NULL) 
    {
        G->Vertices = V;
    } 
    else
    {
        while (VertexList->Next != NULL)
            VertexList = VertexList->Next;

        VertexList->Next = V;
    }
    /* 정점 구조체의 인덱스 갱신 */
    V->Index = G->VertexCount++; // Index는 0부터 시작하기 때문에 기존에 VertexCount를 더해주면 된다.
}

void AddEdge(Vertex* V, Edge* E)
{
    if (V->AdjacencyList == NULL)
    {
        V->AdjacencyList = E;
    } 
    else
    {
        Edge* AdjacencyList = V->AdjacencyList;

        while (AdjacencyList->Next != NULL)
            AdjacencyList = AdjacencyList->Next;

        AdjacencyList->Next = E;
    }
}

void PrintGraph ( Graph* G )
{
    Vertex* V = NULL;
    Edge*   E = NULL;

    if ((V = G->Vertices) == NULL)
        return;

    while (V != NULL)
    {
        printf( "%c : ", V->Data );        
        
        if ( (E = V->AdjacencyList) == NULL ) 
        {
            V = V->Next;
            printf("\n");
            continue;
        }

        while ( E != NULL )
        {
            printf("%c[Weight: %d] ", E->Target->Data, E->Weight );
            E = E->Next;
        }

        printf("\n");

        V = V->Next;    
    }   

    printf("\n");
}
