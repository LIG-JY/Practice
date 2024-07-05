# equals 함수를 오버로딩할 때 베스트 프렉티스

## 코틀린 표준 라이브러리의 예시

```kotlin
override fun equals(other: Any?): Boolean {
        if (this === other) return true
        val otherVersion = (other as? KotlinVersion) ?: return false
        return this.version == otherVersion.version
    }
```

- ===로 레퍼런스 동등성 확인
- as?로 타입 캐스팅
  - 캐스팅에 성공하면 null이 아닌 개체
  - 캐스팅에 실패하면 null 
- ?: 엘비스 연산자
  - other이 null이 아니면 other을 otherVersion에 대입
  - other이 null이면 return false
- == 연산자는 equals 호출해서 속성의 값을 비교

### [인텔리제이 IDEA에서 자동 생성]

- 자동 생성 기능을 이용해도 좋음