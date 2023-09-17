#include "KarpRabin.h"
#include <stdio.h>
#include <math.h>

int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize )
{
    int i = 0;
    int j = 0;
    int Coefficient = pow( 2, PatternSize - 1 ); // 2^(patternsize - 1)
    int HashText    = Hash( Text,    PatternSize ); // i = 0, 초항 구하기
    int HashPattern = Hash( Pattern, PatternSize );

    for ( i=Start; i<=TextSize - PatternSize; i++ )
    {
        HashText = ReHash( Text, i, PatternSize, HashText, Coefficient);

        if ( HashPattern == HashText )
        {
            for ( j=0; j<PatternSize; j++ )
            {
                if ( Text[i+j] != Pattern[j] )
                    break;
            }

            if ( j >= PatternSize )
                return i;
        }
    }

    return -1;
}
/* 
@복습: Hash 직접 구현해보자. 등비수열을 활용하자
int의 오버플로우 덕분에 해시 값을 일정범위에 가둘 수 있다. 
*/
int Hash( char* String, int Size ) // i == 0, from 0 to Size-1 인덱스까지 String을 조각낸다고 생각합시다.
{
    int i = 0;
    int HashValue = 0;

    for ( i=0; i<Size; i++ )
    {
        HashValue = String[i] + ( HashValue * 2 );
    }

    return HashValue;
}

int ReHash( char* String, int Start, int Size, int HashPrev, int Coefficient ) // i > 0
{
    if ( Start == 0 )
        return HashPrev;
    
    return String[ Start + Size - 1] + ( (HashPrev - Coefficient * String [Start-1] ) * 2 );
}
