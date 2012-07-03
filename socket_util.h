/*
 * socket_util.h
 *
 *  Created on: Jul 3, 2012
 *      Author: lisperl
 */

#ifndef SOCKET_UTIL_H_
#define SOCKET_UTIL_H_

int set_nonblock(int);
int create_server_socket(short,int);
int apccet_new_connection(int);
int send_data(int,const char*,int);
int recv_data(int,char*,int);

#endif /* SOCKET_UTIL_H_ */
