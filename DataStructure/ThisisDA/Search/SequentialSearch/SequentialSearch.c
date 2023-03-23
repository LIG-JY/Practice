#include "LinkedList.h"

Node* SLL_SequentialSearch(Node* Head, int Target)
{
    Node* Current = Head; 
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        if ( Current->Data == Target )
        {
            Match = Current; 
            break;
        }
        else
            Current = Current->NextNode;
    }

    return Match;
}

Node* SLL_MoveToFront(Node** Head, int Target)
{
    Node* Current	= (*Head); 
    Node* Previous = NULL; 
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        if ( Current->Data == Target )
        {
            Match = Current;
            if ( Previous != NULL )
            {
                //	자신의 앞 노드와 다음 노드를 연결
                Previous->NextNode = Current->NextNode;

                //	자신을 리스트의 가장 앞으로 옮기기
                Current->NextNode = (*Head);
                (*Head) = Current; //  이 코드 때문에 parameter로 Node**을 사용한다. 값의 변경
            }
            break;
        }
        else
        {
            Previous = Current;
            Current	= Current->NextNode;
        }
    }
    return Match;
}

Node* SLL_Transpose(Node** Head, int Target)
{
    Node* Current	= (*Head);
    Node* PPrevious	= NULL; //	이전 노드의 이전 노드
    Node* Previous	= NULL; //	이전 노드
    Node* Match	= NULL;

    while ( Current != NULL )
    {
        /* 탐색을 성공할 경우 */
        if ( Current->Data == Target )
        {
            Match = Current;
            if ( Previous != NULL )
            {
                /* Current 앞에 PPrevious가 존재한다.*/
                if ( PPrevious != NULL ) 
                    PPrevious->NextNode = Current;
                /* Current가 가장 앞으로 가니까 head의 변화가 발생함 */
                else
                    (*Head) = Current;
                /* current->previous순으로 배치 */
                Previous->NextNode = Current->NextNode;
                Current->NextNode = Previous;
            }
            break;
        }
        /* 아직 못 찾았으면 이동 */
        else
        {
            if ( Previous != NULL ) 
                PPrevious = Previous;

            Previous = Current;
            Current	= Current->NextNode;
        }
    }
    return Match;
}

/* 계수법 */
Node * FrequenCountMethod(Node** Head, int Target)
{
    // 탐색코드
    // 탐색을 성공하면, map에 key-value로 빈도 저장 or 노드를 변경해서 노드 구조체에 빈도를 넣어도 좋음
    // value 에 따라 map 정렬 or 노드 구조체의 빈도로 비교해서 노드를 삽입할 위치를 찾고, 제거, 삽입 과정
    // 디테일하게 빈도가 3이면 3의 가장 오른쪽 즉 첫번째로 만나는 빈도가 2인 노드의 왼쪽에 삽입
}


int main( void )
{
    int   i       = 0;
    int   Count   = 10;
    Node* List    = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;
    Node* Match   = NULL;

    int   InitValue[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};

    //  리스트 초기화
    for ( i = 0; i<Count; i++ )
    {
        NewNode = SLL_CreateNode(InitValue[i]);
        SLL_AppendNode(&List, NewNode);
    }

    // 순차 탐색
    printf("Simple Sequential Search...\n");
    
    Match =  SLL_SequentialSearch(List, 9);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전진 이동법
    printf("Move To Front...\n");

    Match =  SLL_MoveToFront(&List, 4);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전위법
    printf("Transpose...\n");

    Match =  SLL_Transpose(&List, 7);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);


    //  모든 노드를 메모리에서 제거     
    printf("Destroying List...\n");

    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, 0);

        if ( Current != NULL ) 
        {
            SLL_RemoveNode(&List, Current);
            SLL_DestroyNode(Current);
        }
    }

    return 0;
}
