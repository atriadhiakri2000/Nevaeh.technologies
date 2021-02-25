#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5200
using namespace std;

int main(int argc, char const *argv[])
{
        int server = 0, read_server_message;
        struct sockaddr_in server_add;
        cout << "Connected" << endl;
        if (( server = socket(AF_INET, SOCK_STREAM,0)) < 0)
        {
                cout << "<-- Connection UnStable -->" << endl;
                exit(1);
        }
        server_add.sin_family = AF_INET;
        server_add.sin_port = htons( PORT );
        if (inet_pton(AF_INET, "127.0.0.1", &server_add.sin_addr) <= 0)
        {
                cout << "<-- Invalid Address -->" << endl;
                exit(1);
        }
        if (connect(server, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
        {
                cout << "<-- Connection failed -->" << endl ;
                exit(1);
        }
        cout << "<-- START -->" << endl;
        char server_message[100] ;
        char client_message[100] = "Hello There...";
        send(server, client_message , strlen(client_message), 0);
        cout << "Message sent..." << endl ;
        read_server_message = read(server, server_message, 100);
        cout << server_message << endl;
        while(1)
        {
                if(strcmp(client_message, "QUIT") == 0)
                {
                        break;
                }
                read_server_message = read(server, server_message, 100);
                cout << ">>>" << server_message << endl;
                cout << "Reply --> ";
                cin.getline(client_message, 100);
                send(server, client_message, strlen(client_message), 0);
                cout << "Message Sent..." << endl;

        }
        return 1;
}

