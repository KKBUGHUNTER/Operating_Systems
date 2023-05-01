#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
#include <ctype.h>

#define SHMSZ     27

int main()
{
    int shmid,i;
    key_t key;
    char *shm, *s;
    key = 8080; 
   
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget"); 
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

	*shm = '!';
	while(*shm!='*')
	{
		while(*shm!='@'&&*shm!='*')
			sleep(1);
		if(*shm!='*'){
			printf("server:");
			for (s = shm+1; *s != '\0'; s++)
		    	putchar(*s);
			putchar('\n');

			char a[100];
			printf("message to send (* to end):");
			fgets(a, sizeof(a), stdin);
			if(a[0]!='*'){
				s=shm+1;
				for (i=0;i<strlen(a);i++)
					 *s++ = a[i];
				*s = '\0';
				*shm = '#';
			}
			else
				*shm = '*';
		}
		else
			printf("connection closed by server");
	}

    shmid = shmdt(shm);

    exit(0);
    return 0;
}

// KKBUGHUNTER