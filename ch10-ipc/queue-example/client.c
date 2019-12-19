#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>


#define BUF_SIZE	256
#define PROJ_ID		32
#define PATH_NAME	"/tmp"
#define SERVER_MSG	1
#define CLIENT_MSG	2

int main(void)
{
    /*用户自定义消息缓冲区*/
    struct mymsgbuf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int	qid; 	/*消息队列标识符*/
    int	msglen;
    key_t	msgkey;

    /*获取键值*/
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1)
    {
        perror("ftok error!\n");
        exit(1);
    }

    if ((qid = msgget(msgkey, IPC_CREAT|0660)) == -1)
    {
        perror("msgget error!\n");
        exit(1);
    }

    while (1)
    {
        if (msgrcv(qid,&msgbuffer,BUF_SIZE,SERVER_MSG,0) == -1)
        {
            perror ("Server msgrcv error!\n");
            exit (1);
        }

        printf ("server: %s\n", msgbuffer.ctrlstring);
        printf ("client: ");
        fgets ( msgbuffer.ctrlstring, BUF_SIZE, stdin);
        if (strncmp ("exit", msgbuffer.ctrlstring, 4) == 0)
        {
            break;
        }
        msgbuffer.ctrlstring[strlen(msgbuffer. ctrlstring)-1] = '\0';
        msgbuffer.msgtype = CLIENT_MSG;
        if(msgsnd(qid,&msgbuffer,strlen(msgbuffer.ctrlstring) + 1,0) == -1)
        {
            perror("client msgsnd error!\n");
            exit(1);
        }
    }
    exit(0);
}
