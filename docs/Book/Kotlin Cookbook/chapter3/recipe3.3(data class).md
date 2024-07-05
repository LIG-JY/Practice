# 데이터 클래스

## 문제: equals, hashCode, toString 등이 포함된 `엔티티`를 나타내는 클래스를 생성하고 싶음

## 해결: data class

- 데이터를 담는 용도로 data class를 사용
- 코틀린 컴파일러가 equals, hashCode, toString, 구조 분해를 위함 component 함수 등을 생성

```kotlin
data class Product(
    val name: String,
    val price: Double
)

fun main() {
    val p1 = Product("gun", 10.0)
    val p2 = Product("gun", 10.0)

    val products = setOf(p1, p2)
    println(products)
    println(p1.toString())
    println(p1.hashCode())
    println(p2.toString())
    println(p2.hashCode())
}

>> 출력
[Product(name=gun, price=10.0)]
Product(name=gun, price=10.0)
1079285440
Product(name=gun, price=10.0)
1079285440
```

- p1, p2 개체가 동등하기 때문에 set에 오직 하나만 추가됨
  - equals를 컴파일러가 자동으로 구현했음을 확인
  - toString()으로 생성된 문자열도 동일함
  - hashCode도 동일함

### [copy 함수]

- copy 함수는 원본과 같은 속성 값으로 시작해서 copy 함수에 매개변수로 제공된 속성 값만 변경해 새로운 개체를 생성함

```kotlin
fun main() {
    val p1 = Product("gun", 10.0)
    val p2 = p1.copy(name = "sun")

    val products = setOf(p1, p2)
    println(products)
}

>> 출력
[Product(name=gun, price=10.0), Product(name=sun, price=10.0)]
```

- copy 함수는 얕은 복사를 수행함
  - 데이터 클래스의 멤버가 참조형인 경우

```kotlin

data class ReferenceData(
    val value: String
)

data class Product(
    val name: String,
    val price: Double,
    val referenceData: ReferenceData
)

fun main() {
    val rd = ReferenceData("reference")
    val p1 = Product(name = "gun", price = 10.0, referenceData = rd)
    val p2 = p1.copy("sun", price = 20.0)
    
    println(p1.referenceData === p2.referenceData)
}
>> 출력
true
```

- p1에서 값을 복사할 때 멤버 변수 rd의 참조를 복사했기 때문에 p1.referenceData === p2.referenceData의 값은 true
- 얉은 복사를 확인할 수 있음

### [component 함수]

- 구조 분해에 사용됨

```kotlin

data class ReferenceData(
    val value: String
)

data class Product(
    val name: String,
    val price: Double,
    val referenceData: ReferenceData
)

fun main() {
    val rd = ReferenceData("reference")
    val p1 = Product(name = "gun", price = 10.0, referenceData = rd)

    val (name, price, ref) = p1
    println(name == p1.component1())
    println(price == p1.component2())
    println(ref == p1.component3())
}
```

### [코틀린이 생성하는 함수가 포함된 속성을 사용하지 않고 싶다면 클래스 바디에 속성을 추가하자]

```kotlin
data class Product(
    val name: String,
    val price: Double,
    val referenceData: ReferenceData
) {
    var custom: Int = 0
        get() {
            return field
        }
        set(value: Int) {
            field = value
        }
}
```

- 멤버 변수 custom의 경우 컴파일러가 자동으로 equals, hashCode, toString, 구조 분해를 위함 component 함수 등을 생성하지 않음