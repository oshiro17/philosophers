#include "philosophers.h"

void	*aaa(void *mutex)
{
	pthread_mutex_lock((pthread_mutex_t *)mutex);
	sleep(2);
	printf("thread%d\n",1);
	pthread_mutex_unlock(mutex);
	return(0);
}

void	*bbb(void *mutex)
{
	pthread_mutex_lock((pthread_mutex_t *)mutex);
	sleep(2);
	printf("thread%d\n",2);
	pthread_mutex_unlock(mutex);
	return(0);
}

void	*ccc(void *mutex)
{
	pthread_mutex_lock((pthread_mutex_t *)mutex);
	sleep(1);
	printf("thread%d\n",3);
	return(0);
}

void	make_pthread()
{
	pthread_t	thread;
	pthread_t	thread2;
	pthread_t	thread3;
	void		*retval;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	//mutexを初期化する
	pthread_create(&thread, NULL, aaa, &mutex);
	pthread_create(&thread2, NULL, bbb, &mutex);
	pthread_create(&thread3, NULL, ccc, &mutex);
	pthread_join(thread,&retval);
	pthread_join(thread2,&retval);
	pthread_join(thread3,&retval);
	pthread_mutex_destroy(&mutex);
	//mutexを破棄する
}