#include "MST.h"

void Prim(Graph* G, Vertex* StartVertex, Graph* MST )
{
    int i = 0;

    PQNode         StartNode = { 0, StartVertex };
    PriorityQueue* PQ        = PQ_Create(10);

    Vertex*  CurrentVertex = NULL;
    Edge*    CurrentEdge   = NULL; 

    int*     Weights       = (int*) malloc( sizeof(int) * G->VertexCount );
    Vertex** MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );

    /* Graph 구조체의 Vertices 포인터 순회한다. AddVertex를 보면 그래프에 정점을 추가한 순서로 순회한다. */
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex);

        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        MSTVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;        
        CurrentVertex  = CurrentVertex->Next;
        i++;
    }
    /* StartNode는 입력값으로 정해지는 노드이다. Addvertex 순서와 무관하다. */
    PQ_Enqueue ( PQ, StartNode );

    /* Index는 AddVertex를 보면 그래프에 속한 Vertex수와 정비례한다. 추가되는 순서가 곧 Index이다. */
    Weights[StartVertex->Index] = 0;
    
    while( ! PQ_IsEmpty( PQ ) )
    {
        PQNode  Popped;
        
        /* Popped 변수에 PriorityQueue에서 뽑아낸 노드를 저장한다. (최우선순위) */
        PQ_Dequeue(PQ, &Popped);
        /* PQNode의 데이터는 Vertex의 포인터이다. */
        CurrentVertex = (Vertex*)Popped.Data;
        
        /* Fringes를 왜 사용할까? -> 사이클 형성되는 경우 확인하려고? or 중복 확인? */
        Fringes[CurrentVertex->Index] = CurrentVertex;

        /* PriorityQueue에서 뽑은 Vertex의 인접 Edge를 순회해서 가중치가 작은 Edge를 찾는 작업 */
        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;
            /* Fringes 확인하고 */ 
            if ( Fringes[TargetVertex->Index] == NULL &&
                 CurrentEdge->Weight < Weights[TargetVertex->Index] )
            {
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                PQ_Enqueue ( PQ, NewNode );

                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index]     = CurrentEdge->Weight;                
            }
            
            CurrentEdge = CurrentEdge->Next;
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
    {
        int FromIndex, ToIndex;

        if ( Precedences[i] == NULL )
            continue;

        FromIndex = Precedences[i]->Index;
        ToIndex   = i;

        AddEdge( MSTVertices[FromIndex], 
            CreateEdge( MSTVertices[FromIndex], MSTVertices[ToIndex],   Weights[i] ) );

        AddEdge( MSTVertices[ToIndex],   
            CreateEdge( MSTVertices[ToIndex],   MSTVertices[FromIndex], Weights[i] ) );
    }

    free( Fringes );
    free( Precedences );
    free( MSTVertices );
    free( Weights );

    PQ_Destroy( PQ );
}

void Kruskal(Graph* G, Graph* MST )
{
    int           i;
    Vertex*       CurrentVertex = NULL;
    Vertex**      MSTVertices   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    DisjointSet** VertexSet     = 
                         (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
    
    PriorityQueue* PQ      = PQ_Create(10);

    i = 0;    
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Edge* CurrentEdge;

        VertexSet[i]   = DS_MakeSet( CurrentVertex );
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, MSTVertices[i] );

        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            PQ_Enqueue( PQ, NewNode );

            CurrentEdge = CurrentEdge->Next;
        }

        CurrentVertex  = CurrentVertex->Next;        
        i++;
    }

    while ( !PQ_IsEmpty( PQ ) )
    {
        Edge*  CurrentEdge;
        int    FromIndex;
        int    ToIndex;
        PQNode Popped;

        PQ_Dequeue( PQ, &Popped );
        CurrentEdge = (Edge*)Popped.Data;

        printf("%c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );

        FromIndex = CurrentEdge->From->Index;
        ToIndex   = CurrentEdge->Target->Index;

        if ( DS_FindSet( VertexSet[FromIndex] ) != DS_FindSet( VertexSet[ToIndex] ) )
        {
            AddEdge( MSTVertices[FromIndex], 
                     CreateEdge( MSTVertices[FromIndex], 
                                 MSTVertices[ToIndex], 
                                 CurrentEdge->Weight ) );

            AddEdge( MSTVertices[ToIndex], 
                     CreateEdge( MSTVertices[ToIndex], 
                                 MSTVertices[FromIndex], 
                                 CurrentEdge->Weight ) );

            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
        DS_DestroySet( VertexSet[i] );

    free( VertexSet );
    free( MSTVertices );
}
