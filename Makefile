all:
	gcc -Wall -g TCP_Client.c -o TCP_Client -lm
	gcc -Wall -g TCP_Server.c -o TCP_Server -lm
