# 코틀린 스크립트 실행하기

## 코틀린 스크립트를 작성하고 작성한 스크립트를 코틀린에서 실행하기

- 실행 가능한 코틀린 코드가 포함된 소스 파일 .kts 확장자를 사용해 스크립트로 정의할 수 있음

```sum.kts
val numbers = listOf(1, 2, 3, 4, 5)
var sum = 0

for (number in numbers) {
    sum += number
}

println("Sum of numbers: $sum")
```

```shell
kotlinc -script sum.kts
>>
Sum of numbers: 15
```

- 코틀린 스크립트는 main 함수가 필요없음
- 다른 스크립트 언어처럼 파일의 최상위 레벨에서 순차적으로 실행됨
  - 함수나, 클래스 내부에 포함되지 않음

