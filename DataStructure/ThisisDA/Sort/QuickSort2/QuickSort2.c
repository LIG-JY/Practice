#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
  
/* 내림차순으로 비교 */
int ComparePoint( const void *_elem1, const void *_elem2 ) 
{ 
    /* 형변환 */
    int* elem1 = (int*)_elem1; 
    int* elem2 = (int*)_elem2; 
    
    if ( *elem1 > *elem2) 
        return -1; 
    else if ( *elem1 < *elem2) 
        return 1; 
    else 
        return 0;     
} 
 
int main( void ) 
{ 
    int DataSet[] = {6, 4, 2, 3, 1, 5}; 
    int Length = sizeof DataSet / sizeof DataSet[0];     
    int i = 0; 
 
    qsort((void*)DataSet, Length, sizeof (int), ComparePoint ); 
 
    for ( i=0; i<Length; i++ ) 
    { 
        printf("%d ", DataSet[i]); 
    } 
 
    printf("\n"); 
 
    return 0; 
}
