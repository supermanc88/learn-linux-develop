#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <net/if.h>

int main()
{

    struct sockaddr_in6 server_sock;
    bzero(&server_sock, sizeof(struct sockaddr_in6));

    int ret = 0;

    int lfd = socket(PF_INET6, SOCK_STREAM, 0);

    server_sock.sin6_family = AF_INET6;
    server_sock.sin6_port = htons(12345);


    struct in6_addr ip;

    ret = inet_pton(AF_INET6, "::1", &ip);

    if (ret == 0) {
        printf("inet_pton not a valid src\n");
        return -1;
    } else if (ret == -1) {
        perror("inet_pton error");
        return -1;
    }

    server_sock.sin6_addr = in6addr_any;

//    struct ifreq interface;
//    strncpy(interface.ifr_ifrn.ifrn_name, "eth0", sizeof("eth0"));
//
//    if(setsockopt(lfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface, sizeof(interface)) == -1) {
//        perror("setsockopt error");
//        return  -1;
//    }

    ret = bind(lfd, (struct sockaddr *) &server_sock, sizeof(server_sock));

    if (ret == -1) {
        perror("bind error");
        return -1;
    }

    ret = listen(lfd, 128);

    struct sockaddr_in6 client_sock;
    bzero(&client_sock, sizeof(client_sock));
    socklen_t len = 0;

    int sfd = accept(lfd, (struct sockaddr *) &client_sock, &len);


    while(true) {
        char buf[BUFSIZ] = {0};
        int readbytes = read(sfd, buf, BUFSIZ);

        for (int i = 0; i < readbytes; i++) {
            buf[i] = toupper(buf[i]);
        }

        int writebytes = write(sfd, buf, readbytes);

    }




    std::cout << "Hello, World!" << std::endl;
    return 0;
}
