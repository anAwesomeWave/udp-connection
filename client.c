#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == -1) {
        perror("cannot create socket.");
        return -2;
    }
    struct sockaddr_in server_addr;
    inet_aton("127.0.0.1", &server_addr.sin_addr);
    server_addr.sin_port = htons(12345);
    server_addr.sin_family = AF_INET;

    char msg[] = "hy server.\n";
    ssize_t d = sendto(s, msg, sizeof(msg), 0, (struct sockaddr *) &server_addr, (socklen_t) sizeof(server_addr));
    if(d == -1) {
        perror("cannot reach server.");
        return -1;
    }
    char buf[256];
    socklen_t len = sizeof(server_addr);
    int r = recvfrom(s, buf, 256, MSG_WAITALL, NULL, NULL);
    if(r == -1) {
        perror("recv on the client side");
        return -3;
    }
    printf("%s", buf);
    close(s);
}