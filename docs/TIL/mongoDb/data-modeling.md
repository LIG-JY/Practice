# flexible schema model

## 데이터 모델링(flexible schema model을 고려)

MongoDB는 flexible schema model을 가진다. 즉 아래 조건을 만족한다.

- 하나의 collection(table에 대응)에 포함되는 document(row에 대응)들이 반드시 동일한 필드들을 가질필요는 없다.

- 하나의 collection에 포함되는 document들의 필드가 동일한 데이터 타입을 가질 필요는 없다.

MongoDB는 document database다. 따라서 document에는 관련된 개체를 포함(embed)할 수 있다. 개체의 배열 형태도 마찬가지로 포함할 수 있다.

스키마를 디자인할 때 document database과 realtional database의 차이점을 고려해야한다. documnet database이 스키마는 이미 데이터가 들어가있는 상태에서도 변할 수 있다. 이런 유연성 때문에 join을 줄여 반정규화할 수 있다. 이를 통해 애플리케이션의 성능을 향상시키고, 개발의 복잡성을 줄일 수 있다.

https://www.mongodb.com/docs/manual/data-modeling/

## MongoDB 네임 스페이스

MongoDB에서는 데이터베이스 이름과 컬렉션 이름 조합을 네임스페이스라고 한다. 데이터베이스 이름과 컬렉션 이름 사이에는 반드시 `.`으로 구분한다.

EX) dbname.collectionname

인덱스도 네임스페이스를 가진다.

EX) dbname.collectionname.$index

DB 엔진에 따라서 네임스페이스에 관한 제약이 있다. MMAPv1 스토리지 엔진은 네임스페이스 목록을 저장하는 파일(*.ns)을 생성하기 때문에 하나의 데이터베이스에서 네임스페이스의 개수가 제한이 된다. 즉 모든 컬렉션과 인덱스를 합친 개수의 최대는 정해져있다. 반면 WiredTiger에는 제약이 없다.