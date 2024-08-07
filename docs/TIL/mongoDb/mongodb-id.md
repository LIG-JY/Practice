# id

## Spring Data MongoDB Object와 Document의 mapping 시 document의 _id를 다루는 방법

MongoDB에서는 모든 document에 _id 필드가 있어야 함

도메인 모델(객체)에 Id 프로퍼티가 존재하지 않으면 드라이버는 도메인 모델을 고려하지 않고 생성된 값으로 ObjectId를 할당함

-id 필드를 제공하지 않으면 DB서버가 식별자 유형을 인식하지 못하기 때문

MappingMongoConverter을 사용할 때 아래와 같은 규칙에 따라 _id 필드를 매핑함

```text
1. A property or field annotated with @Id (org.springframework.data.annotation.Id) maps to the _id field.

2. A property or field without an annotation but named id maps to the _id field.
```

https://docs.spring.io/spring-data/mongodb/reference/mongodb/template-crud-operations.html#mongo-template.save-insert

## package kotlin.reflect KCallable의 name

Kotlin 리플렉션 API의 KCallable은 KFunction과 KProperty의 상위 인터페이스로 함수나 프로퍼티 같은 '호출 가능한' 엔티티를 나타냄

KCallable를 사용하면 프로그램 실행 중에 클래스의 구조에 대한 정보를 얻거나, 동적으로 함수를 호출하거나, 프로퍼티 값을 가져오고 설정할 수 있음

name은 호출 가능한 엔티티(함수, 프로퍼티)의 이름을 나타내는 문자열

## "The uuidRepresentation has not been specified, so the UUID cannot be encoded."

MongoDB 드라이버에서 UUID와 관련된 데이터를 인코딩하거나 디코딩하는 과정에서 UUID의 표현 방식(uuidRepresentation)이 지정되지 않았을 때 발생함

따라서 MongoDB 드라이버에 UUID의 표현 방식을 명시적으로 설정해야함

https://github.com/spring-projects/spring-data-mongodb/issues/3546

## MongoDB Unique Index

Unique 인덱스는 인덱싱된 필드에 중복 값이 저장되지 않도록 보장함

즉, 인덱싱된 필드는 고유성을 가짐

기본적으로 MongoDB는 컬렉션을 생성하는 동안 _id 필드에 고유 인덱스를 생성함

## MongoDB Index Types

![alt text](image.png)

- 1(asc)

  오름차순 인덱스는 필드의 값을 오름차순(작은 값에서 큰 값으로)으로 정렬하여 인덱싱함. 

  조회 시 해당 필드를 기준으로 오름차순 정렬된 순서로 데이터를 빠르게 접근할 수 있게 해줌

- -1(desc)

  내림차순 인덱스는 필드의 값을 내림차순(큰 값에서 작은 값으로)으로 정렬하여 인덱싱함.
  
  조회 시 해당 필드를 기준으로 내림차순 정렬된 순서로 데이터를 빠르게 접근할 수 있게 해줌

- text

  텍스트는 문자열 필드에 대해 텍스트 검색을 가능함
  
  텍스트 인덱스를 사용하면, MongoDB에서 텍스트 쿼리 연산자($text)를 사용하여 문자열 필드 내의 단어에 대한 검색을 수행할 수 있음

- 2d(2dsphere)

  2차원 지리공간 인덱스
  
  이는 지리공간 쿼리를 위해 2차원 평면에 데이터를 인덱싱함
  
  주로 지도 위의 점들을 나타낼 때 사용되며, 위치 기반 쿼리를 지원함

## 그래서 UUID 인덱스 타입은 뭐로 하는 것이 좋을까

https://stackoverflow.com/questions/71160699/indexing-on-mongodb-uuid-field

UUID가 DB에 문자열로 저장되더라도 text type 인덱스를 쓰는게 좋은게 아님. UUID 문자열 전체가 식별자로 사용되기 때문

text type인덱스는 문자열의 부분을 검색할 때 유용한 기능임

## UUID 프로퍼티가 MongoDB에 저장될 때 Binary.createFromBase64로 저장됨 이 때 subtype이 3임

아래 링크도 비슷한 문제인데...

https://www.mongodb.com/community/forums/t/how-to-store-a-uuid-with-binary-subtype-0x04-using-the-mongodb-java-driver/13184

https://www.mongodb.com/docs/manual/reference/method/Binary.createFromBase64/#definition

## Update 쿼리에서 UUID와 Mongdb의 Binary를 비교해야함.

어떻게 비교할 수 있나요?

아래와 같이 UUID가 생성되면

```text
c099b04a-8fa1-4d75-b1df-585f05bec805
```

쿼리는 다음과 같음

```text
Query: { "positionId" : { "$binary" : { "base64" : "wJmwSo+hTXWx31hfBb7IBQ==", "subType" : "04"}}}, Fields: {}, Sort: {}
```

결론은 `UUID 사용 안하고` object 자체를 key로 사용합시다(정규화 X)

UUID는 시스템 생성이라 다른 환경에서 사용하기 불편함 프로퍼티 조합해서 compound key로 만들죠

https://stackoverflow.com/questions/69197880/using-mongoclient-to-read-uuid-written-to-with-spring-data