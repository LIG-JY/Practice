#include "ShortestPath.h"

// 시간복잡도 : O(V)
void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath )
{
    int i = 0;

    PQNode         StartNode = { 0, StartVertex };
    PriorityQueue* PQ        = PQ_Create(10);

    Vertex*  CurrentVertex = NULL;
    Edge*    CurrentEdge   = NULL; 

    int*     Weights       = (int*) malloc( sizeof(int) * G->VertexCount );
    Vertex** ShortestPathVertices = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );                         
    Vertex** Fringes       = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    Vertex** Precedences   = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );

    /* 
    입력받은 그래프 G 구조체는 vertex 배열을 가진다. 이 배열에서 vertex의 순서와 
    새로 만들어지는 그래프인 ShortestPath에서 vertex의 순서는 동일하다. 
    O(V)
    */
    CurrentVertex = G->Vertices;
    while ( CurrentVertex != NULL )
    {
        /* 
        Vertex의 데이터를 복사해서 새로운 vertex를 만들고 ShortestPath에 삽입힌디. 
        G와 순서가 동일하다.
        따라서 G의 vertex의 Index와 ShortesPath의 vertex의 Index는 동일하다.
        */
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( ShortestPath, NewVertex);

        Fringes[i]     = NULL;
        Precedences[i] = NULL;
        ShortestPathVertices[i] = NewVertex;        
        Weights[i]     = MAX_WEIGHT;        
        CurrentVertex  = CurrentVertex->Next;
        i++;
    }

    // 우선순위 큐에 함수의 파라미터로 입력받은 시작하는 Vertex를 넣는다.
    PQ_Enqueue ( PQ, StartNode );

    // 자기 자신과의 거리는 0이다. 따라서 경로 가중치의 합은 0
    Weights[StartVertex->Index] = 0;
    
    // O(V * E) 보다 작다.
    while( ! PQ_IsEmpty( PQ ) )
    {
        PQNode  Popped;
        
        // PQ에서 뽑은 Vertex에서 향하는 Edge를 순회한다.
        PQ_Dequeue(PQ, &Popped);
        CurrentVertex = (Vertex*)Popped.Data;
        
        // Fringe의 용도? ,From이 중복된느 것을 방지하는 용도다. Target Vertex는 중복이 될 수 밖에 없다. 따라서 비교해서 최소를 찾는다.
        Fringes[CurrentVertex->Index] = CurrentVertex;

        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL )
        {            
            Vertex* TargetVertex = CurrentEdge->Target;

            /*  
            1. Fringes조건
            Fringes는 From을 중복해서 확인하는 것을 방지하는 것이다. PQ에 중복된 값이 들어갈 수 있다.
            예를 들어 From Vertex(A)에서 to Vertex를 찾다 보면 E가 PQ에 들어간다.
            From Vertex(F)에서 to Vertex를 찾아보면 E가 또 PQ에 들어간다.
            PQ에서 Pop을 하면 Vertex(E)를 여러번 뽑게 되는데, From E부터의 경로를 여러번 연산할 필요가 없다.
            한 From Vertex에서 확인은 한 번이면 충분하다.
            2.
            From Vertex에서 확인은 한 번이면 충분하지만 To Vertex에서는 경로의 값을 비교해서 최소값을 찾아야한다.
            지금 Vertex(B)를 우선순위 큐에서 뽑아서 B의 주변 Edge를 순회한다고 하면
            CurrentVertex = B, CurrentEdge = B에서 TargetVertex으로 향하는 Edge
            CurrentVertex->Index를 통해서 B까지 누적된 경로 가중치의 합의 최소값을 확인할 수 있다.
            TargetVertex->Index를 통해서 Target까지 누적된 경로 가중치의 합의 최소값을 확인할 수 있다.
            "결국 B->target으로 가면서 Edge의 가중치를 더할 때(B를 거치고 target으로 갈 때의 거리)"와
            "지금까지 구한 어떤 경로의 target으로 갈 때의 거리"를 계산해서 비교한다.
            이를 통해서 target까지의 경로를 갱신할지 말지를 결정할 수 있다.
            */
            if ( Fringes[TargetVertex->Index] == NULL &&
                 Weights[CurrentVertex->Index] + CurrentEdge->Weight < 
                               Weights[TargetVertex->Index] )
            // ⬇️경로 갱신 과정
            {
                // 1. TargetVertex를 PQ에 넣는다.
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                PQ_Enqueue ( PQ, NewNode );

                // 2. 그래프 자료구조인 ShortestPath 경로를 완성하기 위해 From을 알 수 있도록 Precedences 배열에 기록한다. 
                Precedences[TargetVertex->Index] =  CurrentEdge->From;
                // 3. TargetVertex의 index로 Weights배열의 값을 갱신한다. 사실 key가 index고 계산한 최소거리가 value인 해쉬 테이블이다. 
                Weights[TargetVertex->Index]     =  
                               Weights[CurrentVertex->Index] + CurrentEdge->Weight; 
            }
            
            CurrentEdge = CurrentEdge->Next;
        }
    }

    // 그래프를 만드는 코드, Vertex 개수만큼 반복한다. O(V)
    for ( i=0; i<G->VertexCount; i++ )
    {
        int FromIndex, ToIndex;

        if ( Precedences[i] == NULL )
            continue;

        FromIndex = Precedences[i]->Index;
        ToIndex   = i;

        /* 
        1. ShortestPathVertices[FromIndex]로 Vertex 구조체를 찾는다. 
        이 구조체는 Vertex의 Data만 가지고 있고, 연결된 Edge는 없는 상태이다.
        24에서 40까지 반복문에서 만든 결과를 사용
        2. CreateEdge(ShortestPathVertices[FromIndex], ShortestPathVertices[ToIndex], Weights[i]))
        Edge를 만든다.
        3. AddEdge 함수를 호출해 ShortestPathVertices[FromIndex] Vertex에 Edge를 연결한다.
        */
        AddEdge( ShortestPathVertices[FromIndex], 
            CreateEdge( 
                ShortestPathVertices[FromIndex], 
                ShortestPathVertices[ToIndex],   
                Weights[i] ) );
    }

    free( Fringes );
    free( Precedences );
    free( ShortestPathVertices );
    free( Weights );

    PQ_Destroy( PQ );
}