/*
 * main.c
 *
 *  Created on: Jul 3, 2012
 *      Author: lisperl
 */
#include<sys/types.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#include"socket_util.h"
#include"handle_http.h"
#define MAX_EPOLL_SIZE 32

int main(int argc, char* argv[]) {

	int serv_socket;
	int epoll_fd;
	struct epoll_event ev;
	struct epoll_event events[MAX_EPOLL_SIZE];
	int nfds;
	int i;
	int client_socket;
	if ((serv_socket = create_server_socket(8080, 32)) == -1) {
		printf("create server socket failed\n");
		exit(-1);
	} else {
		printf("create server socket succeed\n");
	}
	epoll_fd = epoll_create(MAX_EPOLL_SIZE);
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = serv_socket;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_socket,&ev);
	while (1) {
		nfds = epoll_wait(epoll_fd, events, MAX_EPOLL_SIZE, -1);
		for (i = 0; i < nfds; ++i) {
			if (events[i].data.fd == serv_socket) {
				client_socket = apccet_new_connection(serv_socket);
				if(client_socket<0){
					printf("can't create connection\n");
				}else{
					printf("create a new connection\n");
				}
				ev.data.fd = client_socket;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &ev);
			} else if (events[i].events & EPOLLIN) {
				handle_http(events[i].data.fd);
			}
		}

	}
	return 0;

}

