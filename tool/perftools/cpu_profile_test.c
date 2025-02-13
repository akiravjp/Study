#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <gperftools/profiler.h>

//SIGUSR1: start profiling
////SIGUSR2: stop profiling


static void gprof_callback(int signum)
{
    if (signum == SIGUSR1) 
    {
        printf("Catch the signal ProfilerStart\n");
        ProfilerStart("bs.prof");
    } 
    else if (signum == SIGUSR2) 
    {
        printf("Catch the signal ProfilerStop\n");
        ProfilerStop();
    }
}

static void setup_signal()
{
    struct sigaction profstat;
    profstat.sa_handler = gprof_callback;
    profstat.sa_flags = 0;
    sigemptyset(&profstat.sa_mask);                                        
    sigaddset(&profstat.sa_mask, SIGUSR1);
    sigaddset(&profstat.sa_mask, SIGUSR2);

    if ( sigaction(SIGUSR1, &profstat,NULL) < 0 ) 
    {
        fprintf(stderr, "Fail to connect signal SIGUSR1 with start profiling");
    }
    if ( sigaction(SIGUSR2, &profstat,NULL) < 0 ) 
    {
        fprintf(stderr, "Fail to connect signal SIGUSR2 with stop profiling");
    }
}

int loopop_callee()
{
    int n=0;
    int i, j;
    for(i=0; i<10000; i++)
    {
        for(j=0; j<10000; j++)
        {
             n |= i%100 + j/100;
        }
    }
    return n;
}

int loopop()
{
    int n=0;
    int i, j;
    while(1)
    {
        for(i=0; i<10000; i++)
        {
            for(j=0; j<10000; j++)
            {
                n |= i%100 + j/100;
            }
        }
        printf("result:  %d\n", (loopop_callee)() );
    }
    return n;
}

int main(int argc,char** argv)
{
    char program[1024]={0};
    //snprintf(program,1023,"%s_%d.prof",argv[0],getpid());
    setup_signal();
    printf("result:  %d\n", (loopop)() );
    return 0;
}
