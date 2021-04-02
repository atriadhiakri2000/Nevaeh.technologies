#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

struct comm_struct
{
        int sequence;
        const char * name;
        char phoneNo[13];
        double salary;
};

struct namestr
{
        char * data;
};

int main(int argc , char *argv[])
{
        if (argc < 3)
        {
                cout << "<--- PORT or IP not Accessible --->" << endl;
                exit(EXIT_FAILURE);
        }
        struct sockaddr_in server_addr,client_addr;
        int PORT, server;
        char* IP;
        struct comm_struct *str = (struct comm_struct*) malloc(sizeof(struct comm_struct));

        PORT = atoi(argv[2]);
        IP = argv[1];

        server = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(server < 0)
        {
                cout << "<--- Connection Failed --->" << endl;
                exit(EXIT_FAILURE);
        }

        memset(&server_addr, 0, sizeof(server_addr));
        memset(&client_addr, 0, sizeof(client_addr));
        int n = sizeof(server_addr);

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(IP);
        server_addr.sin_port = htons(PORT);

        if(bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                cout << "<--- Binding Failed --->" << endl;
                exit(EXIT_FAILURE);
        }

        cout << " <---------------------------> " << endl;
        comm_struct packet = {12, "Atri", {'+', '9', '1', '9', '6', '7', '4', '5', '4', '5', '5', '6', '3'}, 500.89};
        // STRING
        namestr xyz;
        string s = "Atri";
        xyz.data = const_cast<char*>(s.c_str());
        int x = strlen(xyz.data);
        char * send_data;
        send_data = new char[x + 1]();
        cout << "&x " << x << " sizeof(int) " << sizeof(int) << "xyz.data " << xyz.data <<  endl;
        memcpy(send_data, &x, sizeof(int));
        cout << sizeof(send_data) << send_data << endl;
        memcpy(send_data + sizeof(int), xyz.data, x+1);
        cout << sizeof(int) + x << " --- " << sizeof(send_data) << endl;
        //////////////////////////////////////////////////////////////////

        if(sendto(server, &packet, sizeof(packet), 0, (struct sockaddr*)&server_addr, n) < 0)
        {
                cout << "Packet not sent" << endl;
        }

        else
        {
                cout << "Packet sent" << endl;
                cout << "Sequence : " << packet.sequence << " --- Size : " << sizeof(packet.sequence) << endl;
                cout << "Name : " << packet.name << " --- Size : " << sizeof(packet.name) << endl;
                cout << "Phone No : " << packet.phoneNo << " --- Size : " << sizeof(packet.phoneNo) << endl;
                cout.precision(2);
                cout << "Salary : " << fixed << packet.salary << " --- Size : " << sizeof(packet.salary) << endl;
                cout << "Packet size : " << sizeof(packet) << endl;
        }

        if(sendto(server, send_data, sizeof(send_data), 0, (struct sockaddr*)&server_addr, n) < 0)
        {
                cout << "String not sent" << endl;
        }
        else
        {
                cout << "String Sent" << endl;
        }

        cout << endl;
        close(server);
}

