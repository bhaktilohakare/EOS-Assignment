//Q 2. The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process
//print the result and exit. The parent process wait for completion of the child and then exit.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
	int ret, err,s, fd;
	printf("parent started!\n");
	ret = fork();
	if(ret == 0) {
		// input  redirection
		fd = open("in.txt", O_RDONLY);
		close(0); // stdint
		dup(fd); // copy fd on stdout
		close(fd);
		
		err = execlp("wc","wc", NULL);
		if(err < 0) {
			perror("exec() failed");
			_exit(1);
		}
	}
	else
		waitpid(-1, &s, 0);
	printf("parent completed!\n");
	return 0;
}

