#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

extern int h_errno;
int main(int argc, char *argv[])
{
    struct hostent *host;
    char str[128];
    struct in_addr addr;
    inet_pton(AF_INET, argv[1], &addr.s_addr);
    host = gethostbyaddr((char *)&addr.s_addr, 4, AF_INET);
    printf("%s\n", host->h_name);
    while (*(host->h_aliases) != NULL)
        printf("%s\n", *host->h_aliases++);
    switch (host->h_addrtype) {
        case AF_INET:
            while (*(host->h_addr_list) != NULL)
                printf("%s\n", inet_ntop(AF_INET, (*host->h_addr_list++), str, sizeof(str)));
            break;
        default:
            printf("unknown address type\n");
            break;
    }
    return 0;
}
