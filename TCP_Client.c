#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main(int argc, char **argv) {
  int sockfd;
  int n, i;
  char sendline[1000], recvline[1000];
  struct sockaddr_in servaddr;
  if (argc != 2) {
    printf("Usage: a.out <IP address>\n");
    exit(1);
  }
  memset(sendline, 0, 1000);
  memset(recvline, 0, 1000);
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror(NULL);
    exit(1);
  }
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(51000);
  if (inet_aton(argv[1], &servaddr.sin_addr) == 0) {
    printf("Invalid IP address\n");
    close(sockfd);
    exit(1);
  }
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror(NULL);
    close(sockfd);
    exit(1);
  }
  for (int i = 0; i < 3; i++) {
    printf("Sending message => ");
    fflush(stdin);
    fgets(sendline, 1000, stdin);
    if ((n = write(sockfd, sendline, strlen(sendline) + 1)) < 0) {
      perror("Can\'t write\n");
      close(sockfd);
      exit(1);
    }
    if ((n = read(sockfd, recvline, 999)) < 0) {
      perror("Can\'t read\n");
      close(sockfd);
      exit(1);
    }
    printf("Recieved message => %s", recvline);
  }
  close(sockfd);
}