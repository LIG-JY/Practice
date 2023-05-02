import java.util.*;

public class BoundBuffer<E> {
    private static final int BUFFER_SIZE = 5;
    private List<E> buffer;
    int count;
    int in;
    int out;

    public BoundBuffer() {
        this.count = 0;
        this.in = 0;
        this.out = 0;
        this.buffer = new ArrayList<>(Arrays.asList((E[]) new Object[BUFFER_SIZE])); // Object 타입의 배열 생성 후 E 타입으로 형 변환
    }

    public synchronized void insert(E item) {
        while (this.count == BUFFER_SIZE) {
            try {
                wait();
            } catch (InterruptedException ignored) {
            }
        }
        buffer.set(this.in, item);
        this.in = (this.in + 1) % BUFFER_SIZE;
        this.count++;

        notify(); // buffer(공유자원)을 기다리는 스레드(remove 수행)를 실행 대기(모니터 안 으로)로 만든다.
    }

    public synchronized E remove() {
        E item;

        while (this.count == 0) {
            try {
                wait();
            } catch (InterruptedException ignored) {
            }
        }

        item = buffer.get(this.out);
        this.out = (this.out + 1) % BUFFER_SIZE;
        this.count--;
        notify(); // buffer(공유자원)을 기다리는 스레드(insert 수행)를 실행 대기(모니터 안 으로)로 만든다.

        return item;
    }
}
