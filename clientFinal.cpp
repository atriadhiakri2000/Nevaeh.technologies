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
        int client = 0, n;
        struct sockaddr_in server_add;
        cout << "Connected" << endl;
        char msg[10] = {0};
        if (( client = socket(AF_INET, SOCK_STREAM,0)) < 0)
        {
                cout << "\n Socket Created \n" << endl;
                exit(1);
        }
        server_add.sin_family = AF_INET;
        server_add.sin_port = htons( PORT );
        if (inet_pton(AF_INET, "127.0.0.1", &server_add.sin_addr) <= 0)
        {
                cout << "\nInvalid address\n" << endl;
                exit(1);
        }
        if (connect(client, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
        {
                cout << "Connection failed" << endl ;
                exit(1);
        }
        char sm[10] ;
        char cm[10] = "HI";
        send(client, cm , strlen(cm), 0);
        cout << "Message sent." << endl ;
        n = read(client, sm, 10);
        cout << sm << endl;
        cout << "Message Sent" << endl;
        while(1)
        {
               // cin.getline(cm, 10);
               // send(client, cm, strlen(cm), 0);
                if(strcmp(cm, "QUIT") == 0)
                {
                        break;
                }
                n = read(client, sm, 10);
                cout << sm << endl;
                cout << "Message Sent..." << endl;
                cin.getline(cm, 10);
                send(client, cm, strlen(cm), 0);

        }
        return 1;
}

