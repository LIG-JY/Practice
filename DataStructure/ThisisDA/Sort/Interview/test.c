#include "Point.h"
 
  
/* 내림차순으로 비교 */
int ComparePoint( const void *_elem1, const void *_elem2 ) 
{ 
    /* 형변환 */
    Point* elem1 = (Point*)_elem1; 
    Point* elem2 = (Point*)_elem2; 
    
    if ( elem1->point > elem2->point) 
        return -1; 
    else if ( elem1->point < elem2->point) 
        return 1; 
    else 
        return 0;     
} 
 
int main( void ) 
{   
    int Length = sizeof DataSet / sizeof DataSet[0];     
    int i = 0;
    Point result;
    
    /* 대상 배열 주소, 배열 길이, 요소의 크기(바이트), 비교함수의 주소 */
    qsort((void*)DataSet, Length, sizeof (DataSet[0]), ComparePoint ); 
    
    /* 전체 출력 */
    for ( i=0; i<Length; i++ ) 
    { 
        printf("ID : %d, Score:  %lf\n", DataSet[i].id ,DataSet[i].point);
        if (i == 14141)
        {
            result = DataSet[i];
        } 
    } 
    
    printf("\n");

    printf("정답은 ID : %d, Score:  %lf\n", result.id ,result.point);
 
    return 0; 
}