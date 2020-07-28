#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>

int main()
{

    struct hostent * hp;
    hp = gethostbyname2("netsign", AF_INET6);

    if (hp == NULL) {
        printf("%s\n", gai_strerror(h_errno));
        return -1;
    }
    char buf[BUFSIZ] = {0};
    inet_ntop(AF_INET6, ((struct in6_addr *)(hp->h_addr_list[0]))->s6_addr, buf, BUFSIZ);

    printf("%s\n", buf);


    hp = gethostbyname2("netsign", AF_INET);

    if (hp == NULL) {
        printf("%s\n", gai_strerror(h_errno));
        return -1;
    }
    bzero(buf, BUFSIZ);
    inet_ntop(AF_INET, ((struct in_addr *)(hp->h_addr_list[0])), buf, BUFSIZ);

    printf("%s\n", buf);


    struct addrinfo hints, *res, *ressave;

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_IP;


    int ret = getaddrinfo("fe80::20c:29ff:fede:af8b", NULL, &hints, &res);

    if (ret != 0 ) {
        return -1;
    }
    ressave = res;

    struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *)res->ai_addr;


    bzero(buf, BUFSIZ);
    inet_ntop(AF_INET6, ipv6->sin6_addr.s6_addr, buf, BUFSIZ);

    printf("%s\n", buf);

    freeaddrinfo(ressave);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
