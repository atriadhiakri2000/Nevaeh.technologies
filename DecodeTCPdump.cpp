#include <string>
#include <bitset>
#include <iostream>
#include <pcap.h>
#include <fstream>
#include <cstring>

using namespace std;

string change( const bitset<8>&val)
{
        string s = val.to_string();
        return s;
}

double convert(const char* p)
{
    unsigned long long x = 0;
    for (; *p; ++p)
    {
        x = (x << 1) + (*p - '0');
    }
    double d;
    memcpy(&d, &x, 8);
    return d;
}


int main(int argc, char *argv[])
{

        string file = "first.pcap";
        ofstream in("Server_Log.txt");
        char errbuff[PCAP_ERRBUF_SIZE];
        string x, w;

        pcap_t * pcap = pcap_open_offline(file.c_str(), errbuff);

        struct pcap_pkthdr *header;

        const u_char *data;

        u_int packetCount = 0;
        while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
        {
                if(packetCount != 2)
                {
                        printf(" Packet # %i\n", packetCount);
                        packetCount += 1;

                        in << " Packet " << ++packetCount << endl;

                        printf(" Packet size: %d bytes\n", header->len);
                        int pacsize = header->len;
                        if (header->len != header->caplen)
                                printf(" Warning! Capture size different than packet size: %ld bytes\n", header->len);

                        printf("Epoch Time: %d:%d seconds\n", header->ts.tv_sec, header->ts.tv_usec);
                        int h = 0;
                        for (u_int i=0; (i < header->caplen ) ; i++)
                        {
                                //if ( (i % 16) == 0) printf("\n");

                                //cout << h << " "  << bitset<8>(data[i]) << endl;

                                if(h == 42)
                                {
                                        string s = change(bitset<8>(data[i]));
                                        //cout << stoi(s, 0, 2) << " ---------> Sequence " << endl;
                                        cout << " Sequence --- > : " << stoi(s, 0, 2) << endl;
                                        in << " Sequence --- > : " << stoi(s,0,2) << endl;
                                }
                                else if( h == 56 )
                                {
                                        int c = 0;
                                        string ch;
                                        in << " Phone Number --- > : " ;
                                        cout << " Phone Number --- > : " ;
                                        for(int j = h; j < h+14; j++)
                                        {

                                                in << data[j];
                                                c = j;
                                        }
                                        cout << endl;
                                        in << endl;
                                }
                                else if(h == 81)
                                {
                                        int z = pacsize - sizeof(double);

                                        string s1 = change(bitset<8>(data[z]));
                                        string s2 = change(bitset<8>(data[z+1]));
                                        string s3 = change(bitset<8>(data[z+2]));
                                        string s4 = change(bitset<8>(data[z+3]));
                                        string s5 = change(bitset<8>(data[z+4]));
                                        string s6 = change(bitset<8>(data[z+5]));
                                        string s7 = change(bitset<8>(data[z+6]));
                                        string s8 = change(bitset<8>(data[z+7]));
                                        string dou = s8 + s7 + s6 + s5 + s4 + s3 + s2 + s1;
                                        in << " Salary --- > : " << convert(dou.c_str()) << endl;

                                }


                                h = h + 1;
                        }


                        printf("\n\n");
                }
                else
                {
                        ++packetCount;

                        int pacsize = header->len;
                        if (header->len != header->caplen)
                                printf("Warning! Capture size different than packet size: %ld bytes\n", header->len);

                        int h = 0;
                        for (u_int i=0; (i < header->caplen ) ; i++)
                        {
                                if( h == 46)
                                {

                                        for (int j=46; j < header->caplen; j++)
                                        {
                                                x += data[j];
                                        }
                                        cout << x << endl;
                                        in << " Name --- > : " << x << endl;
                                }
                                h += 1;
                        }

                        for(int j == header->caplen; j > 45; j--)
                        {
                                w = data[j] + w;
                        }
                        cout << w << endl;
                }
        }
        in.close();
        in << "\n" << endl;
        in.close();
}
