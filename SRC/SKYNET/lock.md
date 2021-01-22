# skynet锁
## 摘要
读写锁，原子操作，自旋锁的实现

## 详情
- atomic.h
- rwlock.h
- spinlock.h

### 原子操作
```c++
//值比较替换：在写入新值之前， 读出旧值， 当且仅当旧值与存储中的当前值一致时，
//才把新值写入存储 ptr:指针 oval:旧值 nval:新值
#define ATOM_CAS(ptr, oval, nval) __sync_bool_compare_and_swap(ptr, oval, nval) 
 
//指针比较替换：在写入新指针之前， 读出旧指针， 当且仅当旧指针与存储中的当前新指针一致时，
//才把新指针写入存储
#define ATOM_CAS_POINTER(ptr, oval, nval) __sync_bool_compare_and_swap(ptr, oval, nval)
 
//先加1再返回 例子:开始ptr = 1; __sync_fetch_and_add(ptr, 1) 返回2，ptr的值为2
#define ATOM_INC(ptr) __sync_add_and_fetch(ptr, 1)
 
//先返回再加1 例子:开始ptr = 1; __sync_fetch_and_add(ptr, 1) 返回1，ptr的值为2
#define ATOM_FINC(ptr) __sync_fetch_and_add(ptr, 1) 
 
//先减1再返回
#define ATOM_DEC(ptr) __sync_sub_and_fetch(ptr, 1) 
 
//先返回再减1
#define ATOM_FDEC(ptr) __sync_fetch_and_sub(ptr, 1)
 
//先加n再返回
#define ATOM_ADD(ptr,n) __sync_add_and_fetch(ptr, n)
 
//先减n再返回
#define ATOM_SUB(ptr,n) __sync_sub_and_fetch(ptr, n)
 
//先做and操作再返回
#define ATOM_AND(ptr,n) __sync_and_and_fetch(ptr, n)
```

### 读写锁
源码中用到了 __sync_synchronize() 内存屏障，主要为了解决gcc的一个乱序执行bug，
（此bug存在于低版本的gcc，高版本已修复）

2种实现锁的方式
1. 使用系统的线程锁
```c++
//使用系统的线程锁
#ifndef USE_PTHREAD_LOCK 
 
//读写锁
struct rwlock {
	int write; //标记写
	int read; //标记读
};
//初始化
static inline void rwlock_init(struct rwlock *lock) {
	lock->write = 0;
	lock->read = 0;
}
//锁住读
static inline void rwlock_rlock(struct rwlock *lock) {
	for (;;) {
		while(lock->write) {
			__sync_synchronize(); //内存屏障，让cpu顺序执行；主要为了解决gcc的一个乱序执行bug
		}
		__sync_add_and_fetch(&lock->read,1); //自加（先加后返回）
		if (lock->write) {
			__sync_sub_and_fetch(&lock->read,1); //自减(先减后返回)
		} else {
			break;
		}
	}
}
//锁住写
static inline void rwlock_wlock(struct rwlock *lock) {
	while (__sync_lock_test_and_set(&lock->write,1)) {} //设置写状态，能不能成功听天由命
	while(lock->read) {
		__sync_synchronize();
	}
}
//解锁写
static inline void rwlock_wunlock(struct rwlock *lock) {
	__sync_lock_release(&lock->write);
}
//解锁读
static inline void rwlock_runlock(struct rwlock *lock) {
	__sync_sub_and_fetch(&lock->read,1);
}
 
#else
```

2. 使用 pthread.h 的锁
```c++
struct rwlock {
    pthread_rwlock_t lock;
};
static inline void rwlock_init(struct rwlock *lock) {
    pthread_rwlock_init(&lock->lock, NULL);
}
static inline void rwlock_rlock(struct rwlock *lock) {
    pthread_rwlock_rdlock(&lock->lock);
}
static inline void rwlock_wlock(struct rwlock *lock) {
    pthread_rwlock_wrlock(&lock->lock);
}
static inline void rwlock_wunlock(struct rwlock *lock) {
    pthread_rwlock_unlock(&lock->lock);
}
 
static inline void rwlock_runlock(struct rwlock *lock) {
    pthread_rwlock_unlock(&lock->lock);
}
```

### 自旋锁:
自旋锁是一种互斥锁的实现方式，相比一般的互斥锁会在等待期间放弃cpu，
自旋锁（spinlock）则是不断循环并测试锁的状态，这样就一直占着cpu。

2种实现方式:
1. 使用系统的线程锁
```c++
#ifndef USE_PTHREAD_LOCK
 
//自旋锁
struct spinlock {
	int lock;
};
//锁初始化
static inline void spinlock_init(struct spinlock *lock) {
	lock->lock = 0;
}
//锁住
static inline void spinlock_lock(struct spinlock *lock) {
	while (__sync_lock_test_and_set(&lock->lock,1)) {}
}
//尝试锁住
static inline int spinlock_trylock(struct spinlock *lock) {
	return __sync_lock_test_and_set(&lock->lock,1) == 0;
}
//解锁
static inline void spinlock_unlock(struct spinlock *lock) {
	__sync_lock_release(&lock->lock);
}
//摧毁锁
static inline void spinlock_destroy(struct spinlock *lock) {
	(void) lock;
}
 
#else
```

2. 使用 pthread.h 的锁
```c++
struct spinlock {
    pthread_mutex_t lock;
};
 
static inline void spinlock_init(struct spinlock *lock) {
    pthread_mutex_init(&lock->lock, NULL);
}
static inline void spinlock_lock(struct spinlock *lock) {
    pthread_mutex_lock(&lock->lock);
}
static inline int spinlock_trylock(struct spinlock *lock) {
    return pthread_mutex_trylock(&lock->lock) == 0;
}
static inline void spinlock_unlock(struct spinlock *lock) {
    pthread_mutex_unlock(&lock->lock);
}
static inline void spinlock_destroy(struct spinlock *lock) {
    pthread_mutex_destroy(&lock->lock);
}
```