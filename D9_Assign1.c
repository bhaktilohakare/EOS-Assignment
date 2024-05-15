#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void process_handler(int pid, int signum)
{
	int ret;
	ret = kill(pid,signum);
	printf("process killed\n");
}

int main()
{
	int pid,signum;
	printf("Enter the pid : ");
	scanf("%d", &pid);

	printf("Enter the signum : ");
	scanf("%d", &signum);

	// signal(signum,pid);
	process_handler(pid,signum);
	 
	return 0;
}
