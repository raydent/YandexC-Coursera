
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
int main()
{
	for (int i = 0; i < stringnum; i++) {
		if (frk == 0) {
			kill(getpid(), SIGKILL);
		}
		if (frk != 0) {
			frk = fork();
			if (frk == 0)
			{
				frk = fork();
				if (frk != 0) {
					t = time(NULL);
					for (;;)
					{
						if (abs(time(NULL) - t) > 5)
						{
							kill(frk, SIGKILL);
							printf("PROCESS %d TERMINATED\n", i);
							kill(getpid(), SIGKILL);
						}
					}
				}
				//pid = getpid();
					//printf("forked\n");
				if (frk == 0)
				{
					sleep(container[i].args[0][0] - '0');
					execvp(container[i].args[1], container[i].args + 1);
					//kill(frk, SIGKILL);
					frk = 0;
					kill(getppid(), SIGKILL);
					kill(getpid(), SIGKILL);
				}
			}
		}
	}
}
int getargnum(char* string) {
	char* space = string;
	int n = 0;
	while (space != NULL) {
		space = strstr(space + 1, " ");
		n++;
	}
	char* c = (char*)calloc(20, sizeof(char));
	strcpy(c, "2 ls -all");
	char** shittystring = makeargarr(c);
	for (int i = 0; i < getargnum(string); i++) {
		std::cout << shittystring[i];
	}
	return n;
}
char** makeargarr(char* string) {
	int argnum = getargnum(string);
	char** argarr = (char**)calloc(argnum + 1, sizeof(char*));
	char* p1, * p2;
	p1 = string;
	p2 = string;
	int i = 0;
	while (p2 != NULL) {
		p2 = strstr(p2, " ");
		if (p2 == NULL && p1 != NULL) {
			argarr[i] = (char*)calloc(strlen(string) - (p1 - string), sizeof(char));
			strcpy(argarr[i], p1);
			break;
		}
		argarr[i] = (char*)calloc(p2 - p1, sizeof(char));
		strncpy(argarr[i], p1, p2 - p1);
		p2++;
		if (p2 == NULL)
			break;
		p1 = p2;
		i++;
	}
	argarr[i + 1] = NULL;
	return argarr;
}