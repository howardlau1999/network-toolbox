#include "socket_helper.h"

void print_hex(const char *data, size_t size) {
    int i;
    printf("0x");
    for (i = 0; i < size; ++i)
        printf("%x%x", ((unsigned char)data[i]) / 16,
               ((unsigned char)data[i]) % 16);
}

int get_in_port(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return (((struct sockaddr_in *)sa)->sin_port);
    }

    return (((struct sockaddr_in6 *)sa)->sin6_port);
}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void set_non_blocking(int fd) {
    int opts;
    if ((opts = fcntl(fd, F_GETFL)) < 0) {
        fprintf(stderr, "GETFL failed");
        exit(1);
    }
    opts |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, opts) < 0) {
        fprintf(stderr, "SETFL failed");
        exit(1);
    }
}

void set_blocking(int fd) {
    int opts;
    if ((opts = fcntl(fd, F_GETFL)) < 0) {
        fprintf(stderr, "GETFL failed");
        exit(1);
    }
    opts &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, opts) < 0) {
        fprintf(stderr, "SETFL failed");
        exit(1);
    }
}

void recv_n(int fd, char *buf, const int size) {
    int received = 0;
    while (received < size) {
        int chunk = recv(fd, buf, size - received, 0);
        if (chunk == -1) {
            perror("recv");
            return;
        }
        received += chunk;
        buf += chunk;
    }
}

void send_n(int fd, const char *buf, const int size) {
    int sent = 0;
    while (sent < size) {
        int chunk = send(fd, buf, size - sent, 0);
        if (chunk == -1) {
            perror("send");
            return;
        }
        sent += chunk;
        buf += chunk;
    }
}