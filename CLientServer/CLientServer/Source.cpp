#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
char** names;
void* mythread1(void* names) {
	pthread_t mythid;
	mythid = pthread_self();
	int fdw = open((char*)names, O_WRONLY);
	while (1) {
		char buf[100];
		memset(buf, 0, 100);
		fgets(buf, 100, stdin);
		write(fdw, buf, 100);
		memset(buf, 0, 100);
	}
	//printf("Thread %lu, Calculation result = %d\n", mythid, a);
	return NULL;
}
void main() {
	names = (char**)calloc(100, sizeof(char*));
	for (int i = 0; i < 100; i++)
	{
		names[i] = (char*)calloc(100, sizeof(char));
	}
	int sockfd, newsockfd; /* ����������� ��� ���������� � ��������������� ������� */
	int clilen; /* ����� ������ ������� */
	int n; /* ���������� �������� �������� */
	char line[1000]; /* ����� ��� ������ ���������� */
	struct sockaddr_in servaddr, cliaddr; /* ��������� ��� ���������� ������ ������� ������� � ������� */
	/* ������� TCP-����� */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror(NULL);
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* ����������� ����� ������ */
	if (bind(sockfd, (struct sockaddr*) & servaddr, sizeof(servaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}/* ��������� ��������� ����� � ��������� (���������)���������. ������� ������� ��� ������������� ���������� ��������� ��������� 5 */
	if (listen(sockfd, 5) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}/* �������� ���� ������� */
	while (1)
	{
		/* � ���������� clilen ������� ����������������� ���������� ������ ������� */
		clilen = sizeof(cliaddr);
		/* ������� ��������� �������������� ������������ ��������� ������. ��� ���������� ����������� ��� � ��������� cliaddr ����� ������ ����������� �������, ������������� ����������, � ����������� clilen � ��� ����������� �����. ������� ������ ���������� ��������������� ������,����� ������� ����� ����������� ������� � ��������.�������, ��� ���������� � ������� ���� � ���������� ����� �� ������������, ������������� ������� � �������� ���������� ����� ������������� �������� NULL. */
		if ((newsockfd = accept(sockfd, (struct sockaddr*) & cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		/* � ����� ��������� ���������� �� ������� ����� ���, ���� �� ���������� ������ (����� read()������ ������������� ��������) ��� ������ �� ������� ���������� (����� read() ������ ��������0). ������������ ����� ����� ������ ������ ��������� ��������� 999 ���������. � ��������������� � ������ ���������� ������������ ��������������� ������, �. �. ���������, ������������� ����� accept().*/
		while ((n = read(newsockfd, line, 999)) > 0)
		{
			/* �������� ������ ���������� ������� */
			if ((n = write(newsockfd, line, strlen(line) + 1)) < 0)
			{
				perror(NULL);
				close(sockfd);
				close(newsockfd);
				exit(1);
			}
		}
		/* ���� ��� ������ �������� ������ � ��������� ������ */
		if (n < 0)
		{
			perror(NULL);
			close(sockfd);
			close(newsockfd);
			exit(1);
		}/* ��������� ���������� ��������������� ������� ������ ������� ������ ���������� */
		close(newsockfd);
	}
}