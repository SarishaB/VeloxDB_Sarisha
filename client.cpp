#include <iostream>    
#include <cstring>     
#include <unistd.h>     
#include <sys/socket.h> 
#include <netinet/in.h>  
#include <arpa/inet.h>   
using namespace std;

int main() {
    int client_s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in destination{};
    destination.sin_family = AF_INET;
    destination.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &destination.sin_addr);
    connect(client_s, (struct sockaddr*)&destination, sizeof(destination)); 
    char send[] = "hello";
    write(client_s, send, sizeof(send) - 1);
    char receive[10];
    ssize_t R = read(client_s, receive, sizeof(receive));
    if (R > 0) 
        cout.write(receive, R);
    close(client_s);
    return 0;
}