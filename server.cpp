#include <iostream>      
#include <cstring>       
#include <unistd.h>     
#include <sys/socket.h> 
#include <netinet/in.h>  
#include <arpa/inet.h>   
using namespace std;

int main() {
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    int setting_value = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &setting_value, sizeof(setting_value));

    sockaddr_in s{};
    s.sin_family = AF_INET;
    s.sin_port = htons(1234);
    s.sin_addr.s_addr = INADDR_ANY;

    bind(socket_descriptor, (struct sockaddr*)&s, sizeof(s));
    listen(socket_descriptor, 10);
    while(true) {
        int client_descriptor = accept(socket_descriptor, nullptr, nullptr);
        char input[10];
        ssize_t r = read(client_descriptor, input, sizeof(input));
        if (r > 0) 
            cout.write(input, r);
        char output[] = "world";
        write(client_descriptor, output, sizeof(output) - 1);
        close(client_descriptor);
    }
    close(socket_descriptor);
return 0;
}