#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <net/if.h>


int main()
{
    int ret = 0;
    struct sockaddr_in6 server_sock = {0};
    bzero(&server_sock, sizeof(struct sockaddr_in6));

    server_sock.sin6_family = AF_INET6;
    server_sock.sin6_port = htons(12345);

    struct in6_addr ip;

    ret = inet_pton(AF_INET6, "::1", &ip);
//    server_sock.sin6_addr = in6addr_loopback;

    for (int i=0; i<16; i++) {
        printf("%d\n", ((char *)&ip)[i]);
    }

//    in6_addr

    server_sock.sin6_addr = ip;

    if (ret == 0) {
        printf("not a valid network address\n");
        return -1;
    } else if (ret == -1) {
        perror("inet_pton error");
        return -1;
    }


//    server_sock.sin6_addr = in6addr_any;

    int cfd = socket(PF_INET6, SOCK_STREAM, 0);
//  如果目的地址是::1时，不需要指定出口网卡，如果目的地址是其它地址时，要指定一个可以路由的网卡
//    struct ifreq interface;
//    strncpy(interface.ifr_ifrn.ifrn_name, "eth0", sizeof("eth0"));
//
//    if(setsockopt(cfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(interface)) == -1) {
//        perror("setsockopt error");
//        return  -1;
//    }

    ret = connect(cfd, (struct sockaddr *)&server_sock, sizeof(server_sock));

    if (ret < 0) {
        perror("connect error");
        return -1;
    }


    while(true) {
        char buf[BUFSIZ] = "aaaaaaaa";

        int writebytes = write(cfd, buf, strlen(buf));

        int readbytes = read(cfd, buf, BUFSIZ);

        fprintf(stdout, "%s", buf);


    }

    return 0;
}