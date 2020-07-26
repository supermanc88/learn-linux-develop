#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>

// gethostbyname 和 gethostbyaddr 只支持ipv4

//根据著名教程beej's guide，getaddrinfo() + addrinfo是一对更现代、方便的组合，用于取代gethostbyname() + sockaddr_in。
//
//不仅可以做DNS lookups，也可以做services name lookups。二合一。
//
//思路为，传入服务器的地址和端口，外加一个addrinfo（用于描述服务器），就可以得到 一个更具体的addrinfo。这个结果可以在创建socket时使用。

//int getaddrinfo(const char *node, const char *service,
//                const struct addrinfo *hints,
//                struct addrinfo **res);

void get_sockaddr1() {
    struct addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(hints));
    res = NULL;

    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_IP;

    int ret = getaddrinfo("fe80::20c:29ff:fe97:f022", NULL, &hints, &res);

    ressave = res;

    while (res != NULL) {

        if (res->ai_family == AF_INET6) {
            char buf[BUFSIZ] {0};
            struct sockaddr_in6 * v6 = (struct sockaddr_in6 *)res->ai_addr;
            inet_ntop(AF_INET6, &(v6->sin6_addr), buf, INET6_ADDRSTRLEN);
            printf("%s\n", buf);
        }

        // 获取的数据可以直接用来创建socket
        int lfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        if (lfd == -1) {
            res = res->ai_next;
            continue;
        }

        ret = bind(lfd, res->ai_addr, res->ai_addrlen);

        if (ret == -1) {
            res = res->ai_next;
            continue;
        }

        ret = listen(lfd, 128);

        if (ret == -1) {
            res = res->ai_next;
            continue;
        }

        break;
        res = res->ai_next;
    }

    freeaddrinfo(ressave);

}

void get_sockaddr2() {
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(hints));
    res = NULL;
    ressave = NULL;

    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = AF_INET;

    int ret = getaddrinfo("google.com", NULL, &hints, &res);

    ressave = res;
    while(res != NULL) {
        printf("%s\n", res->ai_canonname);
        char buf[BUFSIZ] {0};
        struct sockaddr_in * v4 = (struct sockaddr_in *)res->ai_addr;
        inet_ntop(AF_INET, &(v4->sin_addr), buf, BUFSIZ);
        printf("%s\n", buf);
        res = res->ai_next;
    }

    freeaddrinfo(ressave);
}


int main()
{

    get_sockaddr1();

    get_sockaddr2();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
