#ifndef _SOCKET_HELPER_H_
#define _SOCKET_HELPER_H_

#define _GNU_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <memory.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_LEN 4096
#define MAX_WINDOW 4096
#define MAX_EVENTS 32
#define MAX_CONNS 32

/**
 * Print buffer data in hex
 */
void print_hex(const char *data, size_t size);

/**
 * Get inet port in sockaddr struct
 */
int get_in_port(struct sockaddr *sa);

/**
 * Get inet addr in sockaddr struct
 * Returns struct sockaddr_in6 * if sa->sa_family == AF_INET6
 * Else returns struct sockaddr_in *
 */
void *get_in_addr(struct sockaddr *sa);

/**
 * Set a fd to non blocking mode
 */
void set_non_blocking(int fd);

/**
 * Set a fd to blocking mode
 */
void set_blocking(int fd);

/**
 * Block until received n bytes
 */
void recv_n(int fd, char *buf, const int size);

/**
 * Block until sent n bytes
 */
void send_n(int fd, const char *buf, const int size);

/**
 * Quickly listen to a TCP port
 * Returns the listening socket fd
 */
int listen_port(const char *port);

/**
 * Quickly connect to a TCP addr & port
 * Returns the conn socket fd
 */
int connect_to(const char *host, const char *port);

#endif
