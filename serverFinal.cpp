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
#include <fstream>
//#define PORT 7600
using namespace std;

int main(int argc, char const *argv[])
{
        cout << argc << "    " << argv[1] << endl;
        if (argc < 3)
        {
                cout << "<-- PORT NOT ACCESSIBLE -->" << endl;
                exit(EXIT_FAILURE);
        }
        int PORT = atoi(argv[2]);
        int client, serverSD, read_client_message;
        struct sockaddr_in address;
        int opt = 1;
        int addlen = sizeof(address);
        cout << "Connected" << endl;
        if ((serverSD = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
                cout << "<-- Connection UnStable -->" << endl;
                exit(EXIT_FAILURE);
        }
        cout << "<-- Connection Stable -->" << endl;
        if (setsockopt(serverSD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
                cout << "<-- Setsockopt -->" << endl;
                exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );
        if (bind(serverSD, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
                cout << "<-- Binding Error -->" << endl;
                exit(EXIT_FAILURE);
        }
        cout << "<-- Binnding Successful -->" << endl;
        if (listen(serverSD, 10) < 0)
        {
                cout << "<-- Listening Failed -->" << endl;
                exit(EXIT_FAILURE);
        }
        cout << "<-- Heard -->" << endl;
        if ((client = accept(serverSD, (struct sockaddr *)&address, (socklen_t*)&addlen)) < 0)
        {
                cout << "<-- Not Accepted -->" << endl;
                exit(EXIT_FAILURE);
        }
        for (int i = 0; i<10000; i++){};
        cout << "<-- Client Accepted -->" << endl;
        cout << "<-- START -->" << endl;
        ofstream of("Server_Log.txt");
        char client_message[100];
        char server_message[100] = ">>> Hey There...";
        of << " SERVER ---> " << server_message << endl;
        read_client_message = read( client, client_message, 100);
        cout << ">>> " << client_message << endl;
        struct timespec start, end;
        send(client, server_message, strlen(server_message), 0);
        cout << "Reply --> ";
        cin.getline( server_message, 100);
        of << " SERVER ---> " << server_message << endl;
        send(client, server_message, strlen(server_message), 0);
        while(1)
        {
                clock_gettime(CLOCK_MONOTONIC, &start);
                char client_message[100] = {0};
                read_client_message = read(client, client_message, 100);
                clock_gettime(CLOCK_MONOTONIC, &end);
                cout << ">>> "  << client_message << "          (Time_Taken_for_reply --> " << end.tv_sec - start.tv_sec << "sec)"<< endl;
                if(strcmp(client_message, "QUIT") == 0)
                {
                        break;
                }
                if (end.tv_sec - start.tv_sec > 20)
                {
                        cout << "Time taken to Lose connection -->" << end.tv_sec - start.tv_sec << "sec" << endl;
                        break;
                }
                char server_message[100] = {0};
                cout << "Reply --> " ;
                cin.getline(server_message, 100);
                of << " SERVER ---> " << server_message << endl;
                char PPP[] = "PPP";
                if (strcmp(PPP, server_message) == 0)
                {
                        cout << "<----READY---->" << endl;
                        int size_of_packet;
                        cout << " Packect Size --> " ;
                        cin >> size_of_packet;
                        string packet;
                        int size = size_of_packet;
                        while (size_of_packet > 0)
                        {
                                size_of_packet -= 1;
                                string lines;
                                cout << " Line " << size - size_of_packet << " --> " ;
                                cin >> lines;
                                for(int i=0; i<lines.length(); i++)
                                {
                                        packet.push_back(lines[i]);
                                }

                                //packet.push_back("\n");
                        }
                        char server_message2[packet.length() + 1];
                        strcpy(server_message2, packet.c_str());
                        send(client, server_message2, strlen(server_message2), 0);
                        of2 << " Packect ---> " << "\n" << server_message2 << endl;
                        cout << " Packet Sent..." << endl;
                }
                else
                {
                        send(client, server_message, strlen(server_message), 0);
                        cout << "Message sent..." << endl;
                }
        }
        of.close();
        of2.close();
        cout << "Connection closed...!" << endl;
        close(serverSD);
        close(client);
        return 0;
}
