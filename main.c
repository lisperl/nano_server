/*
 * main.c
 *
 *  Created on: Jul 3, 2012
 *      Author: lisperl
 */

#include<unistd.h>
#include<stdio.h>

#include"socket_util.h"
int main(int argc, char* argv[]) {

	int serv_socket;
	if ((serv_socket = create_server_socket(8080, 32)) == -1) {
		printf("create server socket failed\n");
	} else {
		printf("create server socket succeed\n");
	}
	return 0;

}

