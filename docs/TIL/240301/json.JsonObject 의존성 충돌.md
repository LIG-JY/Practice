# Found multiple occurrences of org.json.JSONObject on the class path

```shell
2024-03-02 00:55:06.802[1709308506802] | WARN  | Test worker | o.s.b.t.j.DuplicateJsonObjectContextCustomizerFactory$DuplicateJsonObjectContextCustomizer - 

Found multiple occurrences of org.json.JSONObject on the class path:

	jar:file:/Users/gyo/.gradle/caches/modules-2/files-2.1/org.json/json/20231013/e22e0c040fe16f04ffdb85d851d77b07fc05ea52/json-20231013.jar!/org/json/JSONObject.class
	jar:file:/Users/gyo/.gradle/caches/modules-2/files-2.1/com.vaadin.external.google/android-json/0.0.20131108.vaadin1/fa26d351fe62a6a17f5cda1287c1c6110dec413f/android-json-0.0.20131108.vaadin1.jar!/org/json/JSONObject.class

You may wish to exclude one of them to ensure predictable runtime behavior
```

spring-boot-starter-test 의존성에 포함된 android-json를  제외하면 된다.

```build.gradle.kts
"testImplementation"("org.springframework.boot:spring-boot-starter-test") {
            exclude(group = "com.vaadin.external.google", module = "android-json")
        }
```

gradle을 사용하는 경우 의존성을 찾기 위한 명령어는 다음과 같다. 의존성 트리를 확인할 수 있다.

```shell
./gradlew dependencies
```

멀티 모듈 프로젝트에서 의존성 트리를 확인하기 위해서는 아래와 같은 명령어를 사용하면 된다.

 infra 모듈의 의존성 트리를 확인하는 예시

```shell
./gradlew :infra:dependencies
```

[참고](https://stackoverflow.com/questions/52980064/maven-spring-boot-found-multiple-occurrences-of-org-json-jsonobject-on-the-cl)

[의존성 트리](https://stackoverflow.com/questions/21645071/using-gradle-to-find-dependency-tree)