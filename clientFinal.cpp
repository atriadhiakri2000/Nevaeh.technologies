#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <fstream>

//#define PORT 7600
using namespace std;

int main(int argc, char const *argv[])
{
        if (argc < 3)
        {
                cout << "<-- PORT NOT ACCESSIBLE -->" << endl;
                exit(EXIT_FAILURE);
        }
        int PORT = atoi(argv[2]);
        int server = 0, read_server_message;
        struct sockaddr_in server_add;
        cout << "Connected" << endl;
        if (( server = socket(AF_INET, SOCK_STREAM,0)) < 0)
        {
                cout << "<-- Connection UnStable -->" << endl;
                exit(1);
        }
        cout << "<-- Connection Stable -->" << endl;
        server_add.sin_family = AF_INET;
        server_add.sin_port = htons( PORT );
        if (inet_pton(AF_INET, "127.0.0.1", &server_add.sin_addr) <= 0)
        {
                cout << "<-- Invalid Address -->" << endl;
                exit(1);
        }
        cout << "<-- Valid Address -->" << endl;
        if (connect(server, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
        {
                cout << "<-- Connection failed -->" << endl ;
                exit(1);
        }
        for (int i = 0; i<1000000000000000; i++){};
        cout << "<-- Connection Secured -->" << endl ;
        cout << "<-- START -->" << endl;
        ofstream of("Client_Log.txt");
        char server_message[100] ;
        char client_message[100] = " Hello There...";
        send(server, client_message , strlen(client_message), 0);
        of << " CLIENT ---> " << client_message << endl;
        cout << "Message sent..." << endl ;
        struct timespec start, end;
        read_server_message = read(server, server_message, 100);
        cout << server_message << endl;
        while(1)
        {
                clock_gettime(CLOCK_MONOTONIC, &start);
                char server_message[100] = {0};
                read_server_message = read(server, server_message, 100);
                clock_gettime(CLOCK_MONOTONIC, &end);
                if(strcmp(server_message, "QUIT") == 0)
                {
                        break;
                }
                if (end.tv_sec - start.tv_sec > 20)
                {
                        cout << "Time taken to Lose connection -->" << end.tv_sec - start.tv_sec << "sec" << endl;
                        break;
                }
                cout << ">>> " << server_message << "          (Time_Taken_for_reply --> " << end.tv_sec - start.tv_sec << "sec)"<< endl;
                char client_message[100] = {0};
                cout << "Reply --> ";
                cin.getline(client_message, 100);
                send(server, client_message, strlen(client_message), 0);
                of << " CLIENT ---> " << client_message << endl;
                cout << "Message Sent..." << endl;
        }
        of.close()
        cout << "Connection closed...!" << endl;
        return 1;
}


