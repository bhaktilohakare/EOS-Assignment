//  1. Execute"wc" command from your program (using fork() + exec()). 
//  The command should read data from the ﬁle "in.txt" (instead of terminal) and output
//     should be displayed on terminal

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>

int main() {
	int ret, ret1, ret2, err,s, s1,fd;
	int arr[2], err1;
	printf("parent started!\n");

	// create pipe
	ret = pipe(arr);
	if(ret < 0) {
		perror("pipe() failed");
		_exit(1);
	}

	// run "who" command
	ret1 = fork();
	if(ret1 == 0) {
		// dup pipe write fd to stdout
		close(arr[0]);
		dup2(arr[1], 1); 
		close(arr[1]);

		err1 = execlp("in.txt", "/eos assignment", NULL);
		if(err1 < 0) {
			perror("exec() failed ");
			_exit(1);
		}
	}

	// run "wc" command
	ret2 = fork();
	if(ret2 == 0) {
		// dup pipe read fd to stdin
		close(arr[1]);
		dup2(arr[0], 0);
		close(arr[0]);

		err = execlp("wc", "wc", NULL);
		if(err < 0) {
			perror("exec() failed to execute wc cmd");
			_exit(2);
		}
	}

	// close pipe both ends in parent (no write no read)
	close(arr[1]);
	close(arr[0]);
	waitpid(ret1, &s, 0);
	waitpid(ret2, &s1, 0);
	printf("parent completed!\n");
	return 0;
}

