//Jacob Pledger
//001136676

/*
Programming Assignment  (50 marks)

1. Use "fork" to create a child process. 
In the parent process, print out the letters from "A" to "Z".
In the child process, print out the letters from "a" to "z". 

2. Use "fork" to create a child process. 
In the child process, print out the current process ID, and 
the parent process ID. 
In the parent process, print out the current process ID, and 
the parent process ID.
*/

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main()
{
	cout << "In the parent process" << endl;
	cout << "The current process ID is: " << getpid() << endl;
	cout << "The parent process ID is: " << getppid() << endl;
		for (char A = 'A'; A <= 'Z'; ++A)
			cout << A << ' ';
	cout << endl;

	pid_t pid; //holds return value of fork()
	if ((pid = fork()) < 0)
		cout << "fork error" << endl;

	else if(pid == 0)
	{
		cout << "In child process" << endl;
		cout << "The current process ID is: " << getpid() << endl;
		cout << "The parent process ID is: " << getppid() << endl;
		for (char a = 'a'; a <= 'z'; ++a)
			cout << a << ' ';
	}

	else
	{
		cout << "Back in parent process" << endl;
		cout << "Current process ID is: " << getpid() << endl;
		cout << "Parent process ID is: " << getppid() << endl;
		for (char A = 'A'; A <= 'Z'; ++A)
			cout << A << ' ';
	}
	cout << endl;
	return 0;
}
