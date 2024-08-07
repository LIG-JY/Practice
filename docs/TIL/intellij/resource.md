# resource directory

## TIL 1) : IntelliJ resource 디렉토리에 대해서

resource 디렉토리는 properties files, xml files, image files, html files, etc.를 포함하는 디렉토리이다.
이 디렉토리는 classpath에 포함되어 있어서, 프로그램이 실행될 때 `ResourceBundle.getBundle()` 또는 `getResourceAsStream()` 을 통해 classpath에 있는 파일들을 읽어올 수 있다.

코드 예시
```java
InputStream inputStream = this.getClass().getResourceAsStream("/config.properties");
Properties properties = new Properties();
properties.load(inputStream);
```

예시처럼 클래스 로더를 사용하게 된다.

https://docs.oracle.com/javase/8/docs/api/java/lang/Class.html#getResourceAsStream-java.lang.String-

빌드하면 IntellJ IDEA에서 resources디렉토리의 파일을 output directory(프로젝트를 빌드할 때 생성되는 컴파일 코드와 리소스 파일이 저장되는 디렉토리)에 복사한다.

보통 out, build 디렉토리가 output directory임 gradle에서 주로 build, maven에서는 out으로 생성됨. 하위에 classes는 컴파일된 바이트 코드(.class 파일)
resources에 있는 파일들이 IntellJ IDEA에서 복사한 파일들이다.

어플리케이션이 실행되면 JVM은 .class 파일을 로드하고, resources 디렉토리에 있는 파일들도 로드한다.

![img.png](img.png)

## application-test.yml 사용하기

Spring Boot를 사용하면 테스트 환경에서 쉽게 test 프로파일을 설정할 수 있다. [@ActiveProfiles](https://docs.spring.io/spring-framework/reference/testing/annotations/integration-spring/annotation-activeprofiles.html) 어노테이션을 사용하면 된다.
이를 통해서 통합 테스트를 수행할 수 있다. 통합 테스트에서는 실제 스프링 application context를 로드하고, 모든 빈을 초기화하며, 종종 실제 데이터베이스나 외부 시스템과의 통합을 포함한 전체 스프링 애플리케이션의 동작을 테스트한다.
@SpringBootTest 어노테이션은 이러한 통합 테스트를 위해 설계된 것이다.

```java
@SpringBootTest
@ActiveProfiles("test")
class AssignmentApplicationTests {

	@Value("${spring.datasource.url}")
	private String datasource;

	@Test
	void contextLoads() {
		System.out.println(datasource);
	}

}
```

@Value로 application-test.yml에 있는 값을 가져올 수 있다.

```yaml
spring:
  datasource:
    url: jdbc:h2:mem:testdb
    driver-class-name: org.h2.Driver
    username: z
    password: z
```

이러면 `jdbc:h2:mem:testdb`가 출력된다.