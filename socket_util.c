/*
 * socket_util.c
 *
 *  Created on: Jul 3, 2012
 *      Author: lisperl
 */

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>

#include"socket_util.h"

int create_server_socket(short port, int connection_num) {

	int serv_socket;
	struct sockaddr_in serv_addr;
	char buff[4096];
	int n;

	if ((serv_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY );
	serv_addr.sin_port = htons(port);

	if (bind(serv_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr))
			== -1) {
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		return -1;
	}

	if (listen(serv_socket, connection_num) == -1) {
		printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		return -1;
	}
	return serv_socket;
}
