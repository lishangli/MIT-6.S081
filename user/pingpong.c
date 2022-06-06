#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[])
{
    int p[2];
    
    pipe(p);
    char buf[2];
    char *recmsg="a";
    char *sedmsg="b";
    if(fork()==0)
    {
        //child
        if(read(p[0],buf,1)!=1)
        {
            fprintf(2,"can't read from parent!\n");
            exit(1);
        }
        printf("child receive :%c\n",buf[0]);
        close(p[0]);
        printf("%d: received ping\n",getpid());
        if(write(p[1],sedmsg,1)!=1)
        {
            fprintf(2,"can't write to parent!");

        }
        close(p[1]);
        exit(0);
    }
    else{
        if(write(p[1],recmsg,1)!=1)
        {
            fprintf(2,"Can't write to child!\n");
            exit(1);
        }
        close(p[1]);
        wait(0);

        if(read(p[0],buf,1)!=1)
        {
            fprintf(2,"Can't read from child!");
            exit(1);
        }
        printf("parent receive: %c\n",buf[0]);
        close(p[0]);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}