#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
int read_all_nbytes(int fd,char* buffer,ssize_t nbytes)
{

    ssize_t nread=0;
    char ch;
    size_t i=0;
    
    while (1)
    {
        nread=read(fd,&ch,nbytes);
        if(nread==0)
        {
            perror("error while reading\n");
            exit(EXIT_FAILURE);
        }
        buffer[i]=ch;
        i++;
        if(ch=='\0')
        {
            break;
        }
    }
    return  i;   
}
int main()
{   
    char str[100]={'\0'};
    int fd;
    int nwrite;
    if(fd==-1)
    {
        perror("error opening namedpipe\n");
        exit(EXIT_FAILURE);
    }
    size_t len;
    size_t nread;
    
    do
    {
        fd=open("dictionary.txt",O_RDONLY);
        nread=read(fd,str,100);
        printf("str is %s and len is %ld\n",str,nread);
        str[0]='\0';
        close(fd);
    } while (nread!=0);
    
}