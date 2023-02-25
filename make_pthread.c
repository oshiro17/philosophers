#include "philosophers.h"

void	*aaa()
{
	// sleep()
	printf("thread%d\n",1);
	return(0);
}

void	*bbb()
{
	sleep(1);
	printf("thread%d\n",2);
	return(0);
}

void	*ccc()
{
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

	pthread_create(&thread, NULL, aaa, NULL);
	pthread_create(&thread2, NULL, bbb, NULL);
	pthread_create(&thread3, NULL, ccc, NULL);
	// pthread_join(thread,&retval);
	// pthread_join(thread2,&retval);
	// pthread_join(thread3,&retval);
	// pthread_detach(thread);
	sleep(2);
}