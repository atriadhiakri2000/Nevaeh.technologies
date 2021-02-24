#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 7600
using namespace std;

int main(int argc, char const *argv[])
{
        int server, serverSD, n;
        struct sockaddr_in address;
        int opt = 1;
        int addlen = sizeof(address);
        char msg[10] = {0};

        cout << "Connected" << endl;

        if ((serverSD = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
                cout << "NO CONNECTION...!" << endl;
                exit(EXIT_FAILURE);
        }

        if (setsockopt(serverSD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
                cout << "Setsockopt" << endl;
                exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );
        if (bind(serverSD, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
                cout << "binding Failed" << endl;
                exit(EXIT_FAILURE);
        }
        if (listen(serverSD, 10) < 0)
        {
                cout << "Listen" << endl;
                exit(EXIT_FAILURE);
        }
        if ((server = accept(serverSD, (struct sockaddr *)&address, (socklen_t*)&addlen)) < 0)
        {
                cout << "Accept" << endl;
                exit(EXIT_FAILURE);
        }
        char cm[10];
        char sm[10] = "HI";
        n = read( server, cm, 10);
        cout << cm << endl;
        struct timespec start, end;
        send(server, sm, strlen(sm), 0);
        cout << "Message sent..." << endl;
        cout << "***************" <<  endl;
        cout << "Stablished Connection" << endl;
        cout << "Send Message" << endl;
        cin.getline( sm, 80);
        send(server, sm, strlen(sm), 0);
        while(1)
        {
                clock_gettime(CLOCK_MONOTONIC, &start);
                n = read(server, cm, 10);
                cout << ">>>"  << cm << endl;
                if(strcmp(cm, "QUIT") == 0)
                {
                        break;
                }
                clock_gettime(CLOCK_MONOTONIC, &end);
                if (end.tv_sec - start.tv_sec > 20)
                {
                        break;
                }
                cout << "reply --> " ;
                cin.getline(sm, 10);
                send(server, sm, strlen(cm), 0);
                cout << "Message sent..." << endl;

        }
        cout << "Connection closed...!" << endl;
        close(serverSD);
        close(server);
        return 0;
}
