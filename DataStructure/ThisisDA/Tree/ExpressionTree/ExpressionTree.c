#include "ExpressionTree.h"

ETNode* ET_CreateNode( ElementType NewData )
{
    ETNode* NewNode = (ETNode*)malloc( sizeof(ETNode) );
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;

    return NewNode;
}

void ET_DestroyNode( ETNode* Node )
{
    free(Node);
}

void ET_DestroyTree( ETNode* Root )
{
    if ( Root == NULL )
        return;
    // 후위 순회
    ET_DestroyTree( Root->Left );
    ET_DestroyTree( Root->Right );
    ET_DestroyNode( Root );
}

void ET_PreorderPrintTree( ETNode* Node )
{
    if ( Node == NULL )
        return;

    printf( " %c", Node->Data );

    ET_PreorderPrintTree( Node->Left );
    ET_PreorderPrintTree( Node->Right );
}

void ET_InorderPrintTree( ETNode* Node )
{
    if ( Node == NULL )
        return;
    
    printf( "(" );
    ET_InorderPrintTree( Node->Left );

    printf( "%c", Node->Data );

    ET_InorderPrintTree( Node->Right );
    printf( ")" );
}

void ET_PostorderPrintTree( ETNode* Node )
{
    if ( Node == NULL )
        return;
    
    ET_PostorderPrintTree( Node->Left );
    ET_PostorderPrintTree( Node->Right );
    printf( " %c", Node->Data );
}

void ET_BuildExpressionTree( char* PostfixExpression, ETNode** Node )
{
    int  len        = strlen( PostfixExpression );
    // Token 후위 식 가장 뒤에서부터 읽는다.
    char Token      = PostfixExpression[ len -1 ];
    // Token에 값을 복사하고 NULL문자를 넣어, 다음 재귀호출 때 len이 줄어들게 한다.
    PostfixExpression[ len-1 ] = '\0';

    switch ( Token ) 
    {
        //  연산자인 경우 
        case '+': case '-': case '*': case '/':
            (*Node) = ET_CreateNode( Token );
            ET_BuildExpressionTree( PostfixExpression, &(*Node)->Right );
            ET_BuildExpressionTree( PostfixExpression, &(*Node)->Left  );
            break;

        //  피연산자인 경우 
        default :
            (*Node) = ET_CreateNode( Token);
            break;
    }
}

double ET_Evaluate( ETNode* Tree )
{
    char Temp[2];
    
    double Left   = 0;
    double Right  = 0;
    double Result = 0;

    if ( Tree == NULL )
        return 0;

    switch ( Tree->Data ) 
    {
        //  연산자인 경우 
        case '+': case '-': case '*': case '/':
            Left  = ET_Evaluate( Tree->Left );
            Right = ET_Evaluate( Tree->Right );

                 if ( Tree->Data == '+' ) Result = Left + Right;
            else if ( Tree->Data == '-' ) Result = Left - Right;
            else if ( Tree->Data == '*' ) Result = Left * Right;
            else if ( Tree->Data == '/' ) Result = Left / Right;            

            break;

        //  피연산자인 경우 
        default :
            // memset을 통해서 0으로 2개짜리 배열 채우기(초기화) (시작주소, 채울 값, 채울 양)
            memset(Temp, 0, sizeof(Temp));
            Temp[0] = Tree->Data;
            Result = atof(Temp);  
            break;
    }

    return Result;
}
