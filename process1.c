#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>
int write_all_nbytes(int fd,void* buffer,ssize_t nbytes)
{
    ssize_t bytes_to_be_written=nbytes;
    ssize_t nwrite=0;
    size_t total_written=0;
    while (bytes_to_be_written>0)
    {
        nwrite=write(fd,buffer+total_written,bytes_to_be_written);
        if(nwrite==-1)
        {
            printf("error while writing data\n");
            break;
        }
        total_written+=nwrite;
        bytes_to_be_written-=nwrite;
    }
    return  total_written;;   
}
int main()
{
    FILE* fptr=fopen("dictionary.txt","r");
   mkfifo("send_string",0660);
   char str[100]={'\0'};
    int fd;
    int nwrite;

    if(fd==-1)
    {
         perror("error opening namedpipe\n");
        exit(EXIT_FAILURE);
    }
    size_t len;
    while(fgets(str,100,fptr)!=NULL)
    {
        if(str[0]=='m')
        {
            fd=open("send_string",O_WRONLY);
            printf("sending string %s",str);
            len=strlen(str);
            str[len]='\0';
            write_all_nbytes(fd,(char*)str,len);
            close(fd);
        }
    }
    fclose(fptr);
    close(fd);
    return 0;
}