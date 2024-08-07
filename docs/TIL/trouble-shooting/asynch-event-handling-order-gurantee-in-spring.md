# Asynchronous Event Handling and Order Guarantee in Spring

## 문제 상황 정리(PositionUseCase 예시)

1. connection에서 데이터는 순서대로 오기 때문에 StreamExchange에서는 순서대로 이벤트 발행할 수 있음

2. PositionUsecase에서 들을 때 비동기가 되서 StreamExchange에서 순서대로 발행한 이벤트를 순서대로 처리하지 못할 수 있음

3. 따라서 순서대로 이벤트를 처리할 때 콜백함수로 순서대로 PostionUseCase가 position을 Refresh하게 조작(이벤트 발행 X) 따라서 PositionUseCase에서 이벤트 리스너는 사라짐

4. position refresh할 때 position이 refreshed됬다고 이벤트를 publish하기 위해 정합성을 체크

## 문제 이유

### What is the effect of setting the core pool size to 3?

A : The "core pool size" in a ThreadPoolTaskExecutor refers to the `minimum number of threads` that are kept alive in the thread pool.

Setting this to 3 means that there will always be at least 3 threads ready to handle tasks. In the context of handling events with SimpleApplicationEventMulticaster, this ensures that there are always three threads available to process event notifications concurrently.
> 최소 3개 스레드는 각각 다른 이벤트를 등록된 리스너에게 notificiation 할 수 있다.
> publishing과 notificaiton을 구분할 것, publishing은 이벤트를 생성하고 multicaster에게 전달하는 행위, notification은 multicater가 각 이벤트(여기서 최소 3개 보장)를 각 이벤트를 listen하는 등록된 listener에게 알리는 거임
If more than three events are published simultaneously, and all three core threads are busy, new tasks will wait in the queue until a thread becomes available.
> 3개보다 많은 이벤트를 동시에 notify할 수 있지만 그건 시스템 자원에 따라 불가능할 수 있다. 아무튼 3개는 최소 보장하는게 CorePoolSize의 개념

### applicationEventMulticaster의 publishEvent는 왜 순서를 보장하지 못하는가?

결론은 비동기로 실행되게 config 코드에서 설정했음

```kotlin
@Configuration
class AsynchronousSpringEventConfig {
    @Bean(name = ["applicationEventMulticaster"])
    fun simpleApplicationEventMulticaster(): ApplicationEventMulticaster {
        val eventMulticaster = SimpleApplicationEventMulticaster()
        eventMulticaster.setTaskExecutor(taskExecutor())
        return eventMulticaster
    }

    @Bean
    fun taskExecutor(): ThreadPoolTaskExecutor {
        val taskExecutor = ThreadPoolTaskExecutor().apply {
            corePoolSize = 3
            setPrestartAllCoreThreads(true)
        }

        return taskExecutor
    }
}
```

SimpleApplicationEventMulticaster에 taskExecutor을 지정한다.

taskExecutor의 역할은 각 리스너를 호출하는 것이다.

SimpleApplicationEventMulticaster의 기본 TaskExecutor은  `org.springframework.core.task.SyncTaskExecutor` 로 동기적으로 리스너를 호출한다.

커스터마이징한 taskExecutor을 설정해 비동기적으로 리스너를 호출하게 설정했다.

[참고 1](https://blog.naver.com/gngh0101/222020512119)

[참고 2](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/event/SimpleApplicationEventMulticaster.html)