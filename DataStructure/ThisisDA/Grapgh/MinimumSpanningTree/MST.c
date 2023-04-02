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
    DisjointSet** VertexSet     = (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
                         
    PriorityQueue* PQ      = PQ_Create(10);

    i = 0;
    // 입력받은 G(그래프) 구조체의 Vertices 연결리스트 순서대로 순회를 하게 된다.
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        Edge* CurrentEdge;

        
        /* 
        1. DisjointSet 확인용 집합의 배열
        G 구조체의 Vertices 연결리스트의 순서와 Vertexset vertex포인터의 배열의 순서가 동일하다.
        MakeSet으로 동적할당하기 때문에 free가 필요하다. 
        */
        VertexSet[i]   = DS_MakeSet( CurrentVertex ); 
        /* 
        2. 최소신장트리를 만들기 위해서 Vertex의 값만 복사해서 새로운 Vertex객체로 배열을 만든다. 
        vertex 포인터의 배열을 통해서 각 vertex에서 최소 신장 트리를 만족하는 edge만 연결하기 위함
        vertex 구조체는 인접 edge배열을 연결리스트 형태로 가지고 있다.
        */
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        /* 
        3. input으로 받은 MST(graph 포인터)에 Vertices배열 만들기(모든 Vertex 포함)
        그래프구조체는 Vertices 배열을 연결리스트로 가지고 있다. 
        */
        AddVertex( MST, MSTVertices[i] );

        // CurrentVertex에서 인접 Edge모두 순회하면서 PQ에 삽입하는 과정
        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            // 중복으로 edge가 들어가는지 debug, 우선 순위 큐에는 중복으로 들어가는 것이 확인되었다.
            printf("enqueue! %c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );
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

        // PQ에서 가중치 최소값을 가지는 edge를 뽑는다.
        PQ_Dequeue( PQ, &Popped );
        CurrentEdge = (Edge*)Popped.Data;

        printf("%c - %c : %d\n", 
            CurrentEdge->From->Data, 
            CurrentEdge->Target->Data, 
            CurrentEdge->Weight );

        // 입력받은 G에 addVertex를 하면서 각 Vertex의 index값을 활용한다.
        FromIndex = CurrentEdge->From->Index;
        ToIndex   = CurrentEdge->Target->Index;

        /* 
        입력받은 G의 Vertex리스트의 index에 해당하는 vertex와, Vertexset의 index의 해당하는 vertex가 동일함을 이용한다.

        예를들어 CurrentEdge의 From Vertex의 값이 A, to Vertex의 값이 B이면
        G 구조체와 Addvertex 결과 A값을 갖는 Vertex, B값을 갖는 Vertex의 index를
        VertexSet에 넣으면 A값을 갖는 vertex, B값을 갖는 vertex가 나온다. 

        물론 G 구조체의 Vertex 구조체와 VertexSet에서 나오는 vertex구조체는 다른 구조체다.
        달라야 하는 이유는 Vertexset으로 얻어낸 새로운 Vertex에 오직 하나의 Edge만 Add해서 최소신장 트리를 완성해야하기 때문이다.

        각 Vertex가 같은 집합인지 확인한다. 우선 순위 큐에 A,B를 연결하는 Edge와 B,A를 연결하는 Edge가 중복될 것같지만 상관없다.
        A값을 가지는 Vertex와 B값을 가지는 Vertex가 Union set이 되기 때문에 A,B를 연결하는 Edge(CurrentEdge)를 처리하는 과정 후에
        B,A를 연결하는 CurrentEdge를 처리할 때 조건문에서 탈락한다.
        */
        if ( DS_FindSet( VertexSet[FromIndex] ) != DS_FindSet( VertexSet[ToIndex] ) )
        {
            /* 
            값 A를 갖는 Vertex에 하나의 Edge를 추가.
            Vertex 구조체의 인접Edge 연결리스트에 최소 가중치의 Edge만 남게된다. 
            */
            AddEdge( MSTVertices[FromIndex], 
                     CreateEdge( MSTVertices[FromIndex], 
                                 MSTVertices[ToIndex], 
                                 CurrentEdge->Weight ) );
            /* 
            값 B를 갖는 Vertex에 하나의 Edge를 추가.
            Vertex 구조체의 인접Edge 연결리스트에 최소 가중치의 Edge만 남게된다. 
            */
            AddEdge( MSTVertices[ToIndex], 
                     CreateEdge( MSTVertices[ToIndex], 
                                 MSTVertices[FromIndex], 
                                 CurrentEdge->Weight ) );
            // 두 Vertex를 같은 집합으로 만든다.
            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );
        }
    }

    for ( i=0; i<G->VertexCount; i++ )
        DS_DestroySet( VertexSet[i] );

    free( VertexSet );
    free( MSTVertices );
}
