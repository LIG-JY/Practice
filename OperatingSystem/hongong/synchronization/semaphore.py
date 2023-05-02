from threading import Thread
from threading import Semaphore

num = 0
  
def foo(sem):
    sem.acquire()
    for _ in range(100000):
        global num
        num += 1
    sem.release()
 
if __name__ == '__main__':
    sem = Semaphore(1)
    t1 = Thread(target=foo, args=(sem,))
    t2 = Thread(target=foo, args=(sem,))
 
    t1.start()
    t2.start()
 
print(num)