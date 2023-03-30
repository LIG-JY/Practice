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

        /* 배열 초기화 용도 */
        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        MSTVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;
        i++;

        CurrentVertex  = CurrentVertex->Next;
    }
    /* StartNode는 입력값으로 정해지는 노드이다. Addvertex 순서와 무관하다. */
    // 1. 임의의 정점을 최소 신장 트리에 추가
    PQ_Enqueue ( PQ, StartNode );

    /* Index는 AddVertex를 보면 그래프에 속한 Vertex수와 정비례한다. 추가되는 순서가 곧 Index이다. */
    Weights[StartVertex->Index] = 0;
    
    // 2. 우선 순위큐에 노드를 삽입과 제거 반복
    while(! PQ_IsEmpty(PQ))
    {
        PQNode  Popped;
        
        /* Popped 변수에 PriorityQueue에서 뽑아낸 노드를 저장한다. 
           현재 PQ에서 가장 가중치가 낮은 Edge를 뽑는다. */
        PQ_Dequeue(PQ, &Popped);
        /* PQNode의 데이터는 Vertex의 포인터이다. */
        CurrentVertex = (Vertex*)Popped.Data;
        
        /* Fringes를 왜 사용할까? -> MST에서 중복이 있으면 안 되기 때문에 확인용 */
        Fringes[CurrentVertex->Index] = CurrentVertex;

        // 3. 각 PriorityQueue에서 뽑은 Vertex(Node)의 인접 Edge를 순회해서 가중치가 작은 Edge를 찾는 작업
        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;
            /* Fringes 확인하고 */ 
            if ( Fringes[TargetVertex->Index] == NULL &&
                 CurrentEdge->Weight < Weights[TargetVertex->Index] ) 
                 // Weights 초기화는 MAX_WEIGHT라 처음은 무조건 만족하게 되어있다.
                 // 2번째 조건 때문에 Cycle을 방지할 수 있다. 같은 Vertex를 가리키는 Edge중 가중치가 작은 Edge 하나만 택하니까!
                 // adjacement edge를 모두 순회하면서 PQ에 넣는다.
            {
                // 우선 순위 큐에 넣을 노드 만들기, 가중치가 우선 순위가 된다.
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                // 우선 순위 큐에 넣기
                PQ_Enqueue ( PQ, NewNode );

                // 최소 신장 트리 완성하기 위해서 From vertex와 가중치를 기록하는 배열
                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index]     = CurrentEdge->Weight;                
            }
            
            CurrentEdge = CurrentEdge->Next;
        }
    }

    // 새로 Graphg 구축
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
