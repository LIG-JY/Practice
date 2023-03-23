#include <stdlib.h> 
#include <stdio.h>
#include "Point.h"

int ComparePoint( const void *_elem1, const void *_elem2 ) 
{ 
    Point* elem1 = (Point*)_elem1; 
    Point* elem2 = (Point*)_elem2; 
 
    if ( elem1->point > elem2->point ) 
        return 1; 
    else if ( elem1->point < elem2->point ) 
        return -1; 
    else 
        return 0;     
} 


int main( void )
{
    int Length = sizeof DataSet / sizeof DataSet[0];     
    Point  target;
    Point* found  = NULL;
 
    //  구매포인트의 오름차순으로 정렬 
    qsort( (void*)DataSet, Length, sizeof (Point), ComparePoint );

    //  구매포인트가 671.78점인 고객 찾기 
    target.id     = 0;
    target.point  = 671.78;

    // 첫번째 인자로 위에서 구성한 값을 가진 구조체의 주소를 넘기면 된다. 
    found = bsearch( 
             (void*)&target, 
             (void*)DataSet, 
             Length, 
             sizeof (Point), 
             ComparePoint );
    
    printf("found... ID: %d, Point: %f \n", found->id, found->point );
 
    return 0;
}
