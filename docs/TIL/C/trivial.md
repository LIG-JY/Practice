# Trivial

## C에서 "trivial"의 의미

- C++ 표준에서 정의
- trivial 타입의 의미는 기본 생성자, 복사 생성자, 복사 할당 연산자, 이동 생성자, 이동 할당 연산자, 또는 소멸자가 사용자 정의되지 않은 타입, 또는 이러한 생성자나 연산자가 기본적으로 제공되는 타입을
  의미함
    - 이러한 타입은 메모리 할당, 해제, 복사, 이동 등을 위한 단순한 비트 단위의 연산이 가능함
    - int 같은 기본 타입도 이 조건을 만족함

## mbstate_t 문서에서 "trivial"

> The type mbstate_t is a trivial non-array type that can represent any of the conversion states that can occur in an
> implementation-defined set of supported multibyte character encoding rules. Zero-initialized value of mbstate_t
> represents the initial conversion state, although other values of mbstate_t may exist that also represent the initial
> conversion state.

- mbstate_t는 implementation-defined set로 표준에서 명확하게 정의하는 것이 아님, 컴파일러나 라이브러리 구현자가 정의함
- 다만 `trivial non-array type`라는 기본 특성까지만 기준을 제시함

## reference

https://stackoverflow.com/questions/76911855/what-does-the-term-trivial-formally-mean-in-c