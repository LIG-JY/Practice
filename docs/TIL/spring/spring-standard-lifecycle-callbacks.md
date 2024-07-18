# Lifecycle Callbacks

- `Spring Framework`는 빈의 특성을 커스터마이징 하는 데 사용할 수 있는 다양한 인터페이스를 제공함
- `InitializingBean`과 `DisposableBean` 인터페이스를 구현하면 컨테이너의 빈 수명 관리를 조작할 수 있음

## [InitializingBean](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/InitializingBean.html)

- `InitializingBean` 인터페이스는 `BeanFactory`에 의해 빈의 모든 속성(property)이 설정된 후 빈의 초기화 작업을 수행하도록 하는 메서드를 제동하는 인터페이스다. 
  - 이 인터페이스를 구현함으로써 빈이 완전히 초기화된 시점에 원하는 추가적인 초기화 작업을 수행하거나 필수 속성들이 모두 설정되었는지 검증할 수 있음
- afterPropertiesSet()라는 콜백 메서드를 제공