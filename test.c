#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

 // To run the code enter the following commands into the linux terminal
//   gcc -o test -lpthread test.c 
//  ./test

int length = 100;
int n_thread = 10;
int max[10];
int arr[100];
typedef struct str
{
    int lower_bound;
    int upper_bound;
    int thread_id;
}str;

void *runner(void *param)
{
    struct str *b;
    b = (struct str *) param;
    int l_max = arr[b->lower_bound];
    int i;
    for (i = b->lower_bound + 1; i < b->upper_bound; i++)
        if (arr[i] > l_max) l_max = arr[i];
    max[b->thread_id] = l_max;
    printf("Max of Thread[%d]: %d\n",b->thread_id,l_max);
    pthread_exit(0);
    return NULL;
}

int main()
{
   srand(time(0));
    int i;
    for (i = 0; i < length; i++)
        {
         arr[i] = (int) rand();
         printf("%d, ",arr[i]);
        }
    printf("\n\n");
    pthread_t threads[n_thread];
    str st[n_thread];
    int in = 0;
    int incr = length / n_thread;
    for (i = 0;i < n_thread; i++)
    {
        st[i].thread_id = i;
        st[i].lower_bound = in;
        st[i].upper_bound = in + incr;
        in += incr;
        pthread_create(&threads[i],NULL,runner,&st[i]);
        pthread_join(threads[i],NULL);
    }
    int m = max[0];
    for(i = 1;i < n_thread; i++)
        if (max[i] > m)
          m = max[i];
    printf("\nMax of array: %d\n",m);
    return 0;
}
