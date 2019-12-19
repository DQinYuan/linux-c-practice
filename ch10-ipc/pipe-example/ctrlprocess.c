#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int arg, char * argv[])
{
    int	  n;
    char  buf[1024];

    while (1)
    {
        if ((n = read (STDIN_FILENO, buf, 1024)) > 0)
        {
            buf[n] = '\0';
            printf ("ctrlprocess receive: %s\n",buf);

            if (!strcmp (buf,"exit\n"))
                exit(0);

            if (!strcmp (buf, "getpid\n"))
            {
                printf ("My pid:%d\n", getpid());
                sleep (3);
                exit (0);
            }
        }
    }
}
