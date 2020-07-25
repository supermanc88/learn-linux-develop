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

int main()
{
    struct addrinfo hints, *res;
    bzero(&hints, sizeof(hints));
    res = NULL;






    std::cout << "Hello, World!" << std::endl;
    return 0;
}
