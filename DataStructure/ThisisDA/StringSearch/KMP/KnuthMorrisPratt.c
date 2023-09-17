#include "KnuthMorrisPratt.h"
#include <stdio.h>

/* 
경계 정보를 사전에 기록해두는 테이블을 만드는 함수

@param arg1 Patten 문자열(찾을 대상)
@param arg2 Patter 문자열의 길이
@param arg3 테이블의 포인터

*/
void Preprocessor( char* Pattern, int PatternSize, int* Border)
{

	int i = 0; // Border index
	int j = -1; // Border value(최대 경계 너비)

	Border[0] = -1 // 첫 번째 문자는 일치 접두부가 존재하지 않는다. 따라서 Border의 너비를 -1로 간주한다. 일치 접두부가 존재하면서 너비가 0인 경우와 구분하기 위함이다.
}