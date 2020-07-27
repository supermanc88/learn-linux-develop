#include <iostream>
#include <netdb.h>

// 主要用来判断ip字串是ipv4还是ipv6

int main() {

    struct hostent * hp;
    hp = gethostbyname2("192.168.45.135", AF_INET);

    if (hp == NULL) {
        return -1;
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
