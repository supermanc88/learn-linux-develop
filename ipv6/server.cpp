#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <iostream>

int main()
{

    struct sockaddr_in6 server_sock;
    bzero(&server_sock, sizeof(struct sockaddr_in6));

    int ret = 0;

    int lfd = socket(PF_INET6, SOCK_STREAM, 0);

    server_sock.sin6_family = AF_INET6;
    server_sock.sin6_port = htons(12345);

//    ret = inet_pton(AF_INET6, "fe80::20c:29ff:fede:af8b%eth0", &server_sock.sin6_addr);

    server_sock.sin6_addr = in6addr_any;

    ret = bind(lfd, (struct sockaddr *) &server_sock, sizeof(struct sockaddr_in6));

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
