#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == -1) {
        perror("error with creating socket.");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);
    int b = bind(s, (struct sockaddr*)&addr, sizeof(addr));
    if(b == -1) {
        perror("error with binding");
        return -2;
    }
    struct sockaddr_in src;
    char buf[256];
    socklen_t len = sizeof(src);
    socklen_t r = recvfrom(s, buf, 256, MSG_WAITALL, (struct sockaddr *) &src, &len);

    printf("%s\n", buf);

    if(r == -1){
        perror("error with 'recvfrom'");
        return -3;
    }
    char msg[256];
    if(buf[0] == 'h' && buf[1] == 'y') {
        strcpy(msg, "hello, you have reached the server.\n");
    }else {
        strcpy(msg,"i don't know this command.\n");
    }
    ssize_t d = sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&src, sizeof(src));
    if(d == -1) {
        perror("cannot answer.");
        return -1;
    }
    close(s);
    return 0;
}
