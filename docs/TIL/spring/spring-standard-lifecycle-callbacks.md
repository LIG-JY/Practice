# Lifecycle Callbacks

- Spring Framework는 빈의 특성을 커스터마이징 하는 데 사용할 수 있는 다양한 인터페이스를 제공함
- `InitializingBean`과 `DisposableBean` 인터페이스를 구현하면 컨테이너의 빈 수명 관리를 조작할 수 있음
    - 이 인터페이스들은 `Spring-specific interfaces`에 속함
    - 즉, Spring 프레임워크에서 제공하는 특정 인터페이스들로 이 인터페이스를 사용하면 애플리케이션의 Spring에 종속적이게 됨

## Best Practice

- 현대 Spring 애플리케이션에서 `@PostConstruct` 과 `@PreDestroy` 어노테이션을 사용하는 것이 빈의 생명주기 callback을 다루는 최선의 방법으로 간주됨
- 이 어노테이션들은 `Spring-specific interfaces`에 속하지 않기 때문에, 애플리케이션의 Spring에 대한 종속성을 줄일 수 있음

## Initialization Callbacks

### [InitializingBean](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/InitializingBean.html)

- `InitializingBean` 인터페이스는 BeanFactory에 의해 빈의 모든 속성(property)이 설정된 후 빈의 초기화 작업을 수행하도록 하는 메서드를 제공하는 인터페이스
    - 이 인터페이스를 구현함으로써 빈이 완전히 초기화된 시점에 원하는 추가적인 초기화 작업을 수행하거나 필수 속성들이 모두 설정되었는지 검증할 수 있음
- `InitializingBean` 인터페이스는 `afterPropertiesSet()`라는 콜백 메서드를 제공함
    - 컨테이너는 빈의 모든 프로퍼티가 설정된 후에 `afterPropertiesSet()` 메서드를 호출함
    - 콜백 이라고 부르는 이유는 컨테이너가 특정 상태 변화(빈 초기화 완료)를 감지하여 자동으로 호출하기 때문

### [@PostConstruct](https://docs.spring.io/spring-framework/reference/core/beans/annotation-config/postconstruct-and-predestroy-annotations.html)

- `Spring-specific interfaces`에 속하지 않아 코드를 스프링에 종속적이지 않게(more portable)해준다.
- `@PostConstruct` 이 붙은 함수는 매개변수가 없고, 반환형은 void여야 함
- `InitializingBean`의 `afterPropertiesSet()`에 대응됨

```kotlin
class CachingMovieLister {

	@PostConstruct
	fun populateMovieCache() {
		// populates the movie cache upon initialization...
	}
}
```

- [CommonAnnotationBeanPostProcessor](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/CommonAnnotationBeanPostProcessor.html)
  은 common java annotaion을 처리함
    - Spring에서 제공하는 클래스
- JSR-250 Lifecycle Annotation은 common java annotain에 포함됨
    - `@PostConstruct`
    - `@Predestroy`
- 최신 Spring Configuration에서는 `CommonAnnotationBeanPostProcessor`을 ApplicationContext에 자동으로 등록함
- `CommonAnnotationBeanPostProcessor`이 ApplicationContext에 등록되면, `@PostConstruct`, `@Predestroy`가 붙은 메서드는 각각 대응하는
  lifecycle point에서 호출됨
    - `@PostConstruct`가 붙은 메서드는 빈의 모든 속성을 설정하고 호출됨

- `@PostConstruct`가 붙은 메서드와 다른 초기화 메서드는 컨테이너의 싱글톤 생성 락(singleton creation lock) 내에서 실행됨
    - 싱글톤 생성 락
        - 말 그대로 싱글톤 빈을 생성하는 락
        - 싱글톤 빈을 생성하는 동안 컨테이너는 외부에서 생성 중인 싱글톤 빈에 접근하는 것을 막음
        - 싱글톤 빈이 완전히 초기화 되는 것을 보장하는 방법
        - 싱글톤 빈끼리 의존관계가 있으면, 의존 받는 빈을 먼저 생성함
- 즉 빈은 초기화 콜백 메서드(위의 3가지 방법)이 완료된 후에야 완전히 초기화된 것으로 간주됨
    - 빈이 완전히 초기화 됨 == 다른 빈에 공개(published)될 준비가 됨

## Destruction Callbacks

### [DisposableBean](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/DisposableBean.html)

- `DisposableBean`은 빈이 소멸하기 전 호출할 수 있는 콜백 메서드를 제공하는 인터페이스
- `destroy()`라는 콜백 메서드를 제공함
    - `ApplicationContext`을 통해 애플리케이션을 실행한다면, 애플리케이션이 종료되면 컨테이너는 관리하고 있는 모든 빈을 소멸시킴
    - 빈이 `DisposableBean`을 구현한다, 컨테이너는 `destroy()` 메서드를 호출함

### @PreDestroy

- `Spring-specific interfaces`에 속하지 않아 코드를 스프링에 종속적이지 않게(more portable)해준다.
- `@PostConstruct` 이 붙은 함수는 매개변수가 없고, 반환형은 void여야 함
- `DisposableBean`의 'destroy()'에 대응됨

### [참고]

- Spring 프레임워크에는 빈의 소멸 메서드를 자동으로 추론하는 기능이 있음
    - public 접근 제어자로 선언된 close 또는 shutdown 이름을 가진 메서드를 탐지해 소멸 메서드로 간주
    - Java configuration class에 @Bean 어노테이션이 붙은 메서드가 있다면, Spring은 이 메서드가 반환하는 객체의 소멸 메서드를 탐지함
    - `java.lang.AutoCloseable` 인터페이스 또는 `java.io.Closeable` 인터페이스를 구현한 객체의 소멸 메서드 탐지
        - 인터페이스에는 `close()`라는 추상메서드가 정의됨

## Default Initialization and Destroy Methods

- `Spring-specific interfaces`를 사용하지 않는다면 일반적으로 초기화 및 소멸 콜백을 작성할 때 init(), initialize(), dispose()와 같은 이름으로 작성함
    - 컨밴션
- 개발자는 Spring 컨테이너를 구성할 수 있음
- `모든 빈`에 대해 초기화 및 소멸 콜백 메서드 이름을 지정할 수 있음
- 예를 들어 아래와 같음

```xml

<beans default-init-method="init">

    <bean id="blogService" class="com.something.DefaultBlogService">
        <property name="blogDao" ref="blogDao"/>
    </bean>

</beans>
```

```kotlin
class DefaultBlogService : BlogService {

	private var blogDao: BlogDao? = null

	// this is (unsurprisingly) the initialization callback method
	fun init() {
		if (blogDao == null) {
			throw IllegalStateException("The [blogDao] property must be set.")
		}
	}
}
```

- 최상위 <beans> element에 `default-init-method` attribute가 있으면, 컨테이너는 모든 Bean의 init()이라는 메서드를 초기화 콜백으로 인식함
    - 알아서 적절한 시점(초기화 시점)에 호출됨
    - 비슷하게 `default-destroy-method` attribute로 모든 Bean의 소멸 콜백으로 등록 가능
- 기존 Bean이 컨밴션과 다른 이름의 콜백 메서드를 이미 가지고 있는 경우, XML에서 <bean> 자체의 `init-method` 및 `destroy-method` attribute를 사용하여 메서드 이름을
  지정함으로써 콜백 메서드 기본값을 오버라이드할 수 있음

### [AOP Proxy의 적용]

- 컨테이너는 빈의 모든 의존성이 제공된 후 즉시 설정된 초기화 콜백이 호출되는 것을 보장함
  - 따라서 초기화 콜백은 raw bean 참조에 대해서 호출됨
  - 초기화 콜백이 호출되는 시점에 bean에 AOP interceptors 등이 적용되지 않았음을 의미함
- 즉, 만약 빈이 먼저 생성되고, 프록시가 나중에 따로 적용되는 경우 작성한 코드가 프록시가 적용되지 않은 raw bean과 상호작용 할 수 있음
  - bypass the proxy
- 중요한 것은 프록시 인터셉터를 초기화 콜백에 적용하면 안 됨
  - Bean의 라이프 사이클이 프록시 인터셉터와 결합되어 복잡해질 수 있음
    - 각각을 독립적으로 분리하는 것이 좋음
  - 특히 raw bean과 직접 상호작용 하는 코드에서 문제가 생길 수 있음
  - 결론은 일관성있게 초기화 콜백은 raw bean reference에서 호출하기!
