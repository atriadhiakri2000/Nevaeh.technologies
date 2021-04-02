#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <string>
#include <stdio.h>
#include <vector>
#include <sys/stat.h>
using namespace std;

ofstream f, f2;
float bid, ask, ltp;
string bidq , askq , lrt, t_lrt, lastprint, prevstr, newsymbol, prevstr2;
int ttq, pbid, pask, seq, prevseq;
vector<string> trade_seq, processed_seq;

void print(vector<string> g1)
{
        for (auto it = g1.begin(); it != g1.end(); it++)
                cout << *it << " ";
}

bool IsPathExist(const string &s)
{
        struct stat buffer;
        return (stat (s.c_str(), &buffer) == 0);
}

vector<string> split (string s, string delimiter)
{
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;
        while ((pos_end = s.find (delimiter, pos_start)) != string::npos)
        {

                token = s.substr (pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back (token);
        }
        res.push_back (s.substr (pos_start));
        return res;
}

string gettlrt()
{
        return lastprint;
}

void writeline()
{

        if(ttq > 0)
        {
                if(prevseq != 0)
                {
                        f << prevstr << endl;
                        f2 << prevstr2 << endl;
                }
                prevseq = seq;
                if (bidq.length() < 2)
                {
                        if (askq.length() < 2)
                        {
                                 prevstr = gettlrt() + "," + " " + newsymbol + "," + "  " + bidq + "," + "  " +  to_string(bid) + "," + "  " + askq + "," + " " + to_string(ask) + "," +" " +  to_string(ltp) + "," + " " + to_string(ttq);
                        }
                        else
                        {
                                 prevstr = gettlrt() + "," + " " + newsymbol + "," + "  " + bidq + "," + "  " +  to_string(bid) + "," + " " + askq + "," + " " + to_string(ask) + "," +" " +  to_string(ltp) + "," + " " + to_string(ttq);

                        }
                }
                else
                {
                        if (askq.length() < 2)
                        {
                                 prevstr = gettlrt() + "," + " " + newsymbol + "," + " " + bidq + "," + "  " +  to_string(bid) + "," + "  " + askq + "," + " " + to_string(ask) + "," +" " +  to_string(ltp) + "," + " " + to_string(ttq);

                        }
                        else
                        {
                                 prevstr = gettlrt() + "," + " " + newsymbol + "," + " " + bidq + "," + "  " +  to_string(bid) + "," + " " + askq + "," + " " + to_string(ask) + "," +" " +  to_string(ltp) + "," + " " + to_string(ttq);

                        }
                }
                prevstr2 = gettlrt() + "," + newsymbol + "," +  bidq + "," +  to_string(bid) + "," + askq + "," +  to_string(ask) + "," +  to_string(ltp) + "," + to_string(ttq);

                cout << prevstr << endl;

        }
}

int main(int argc, char *argv[])
{
        //ARGUMENTS
        string symbol = argv[1];
        string subsymbol = argv[2];
        string folder = "/home/cpptest/Atri/";
        newsymbol = subsymbol + "1cmerevnew2Comdty";
        cout << "Symbol -> " << symbol << endl;;
        cout << "SUBSymbol -> " << subsymbol << endl;
        cout << "newSymbol -> " << newsymbol<< endl;

        //DATE YESTERDAY
        time_t now;
        struct tm * timeinfo;
        char buffer[80];
        char buffer2[80];
        time (&now);
        timeinfo = localtime(&now);
        strftime(buffer,sizeof(buffer),"%Y%m%d",timeinfo);
        string cds(buffer);
        cout << cds << endl;

        //DATE YESTERDAY
        timeinfo-> tm_mday--;
        mktime(timeinfo);
        strftime(buffer2,sizeof(buffer2),"%Y%m%d",timeinfo);
        string pds(buffer2);
        cout << pds << endl;

        string fn = folder + cds + "/" + subsymbol + "Pricelog2.txt";
        cout << fn << endl;

        ifstream test(fn.c_str());
        if (!test)
        {
                cout << "Not Found !!" << endl;

        }
        else
        {
                cout << "Found !!" << endl;

                string ofn = folder + cds + "/" + "FINAL" + ".csv";
                string ofn2 = folder + cds + "/" + "FINAL2" + ".csv";

                bid = 0.0, ask = 0.0, ltp = 0.0;
                ttq = 0, pbid = 0, pask = 0, seq = 0, prevseq = 0;
                bidq = "0", askq = "0", lrt = "", t_lrt="", lastprint = "", prevstr = "";

                f.open(ofn.c_str());
                f2.open(ofn2.c_str());
                string line;

                f << "      DATE-TIME,            " << "NEWSYMBOL,        " << "BIDQ,    " << "BID,     " << "ASKQ,  " << "ASK,       " << "   LTP,      " << "TTQ" << endl;
                getline(test, line);
                vector <string> larr = split(line , ",");

                pds = "20210328";
                if(larr[0] == pds)
                {
                        int x = 0;
                        while(!test.eof())
                        {
                                vector<string> lr = split(line,",");
                                cout << x << endl;
                                x += 1;

                                if(lr.size() > 5 && lr[6] == symbol)
                                {
                                        if(lr[9] != "A" && lr[9] != "B")
                                        {

                                                ttq += atoi(lr[10].c_str());
                                                seq = atoi(lr[4].c_str());
                                                ltp = atof(lr[9].c_str()) * atof(lr[13].c_str());
                                                t_lrt = lr[2] + lr[3];
                                                trade_seq.push_back(lr[4]);
                                                if(bid < ask)
                                                {

                                                        lastprint = t_lrt.substr(8);

                                                        if (std::find(processed_seq.begin(), processed_seq.end(),to_string(seq)) != processed_seq.end())
                                                        {

                                                                processed_seq.push_back(to_string(seq));
                                                        }

                                                        writeline();
                                                        pbid = bid;
                                                        pask = ask;
                                                }
                                        }
                                        if(lr[9] == "A" || lr[9] == "B")
                                        {

                                                seq = atoi(lr[4].c_str());
                                                lrt = lr[2] + lr[3];
                                                string lpair;
                                                getline(test, lpair);
                                                vector <string> lrpair = split(lpair , ",");
                                                if (lrpair.size() > 5 && lrpair[6] == symbol && lrpair[2] + lrpair[3] == lrt)
                                                {

                                                        if( lr[9] == "A" && lrpair[9] == "B")
                                                        {


                                                                bid = atoi(lrpair[10].c_str()) * atof(lrpair[12].c_str());
                                                                bidq = lrpair[11];
                                                                ask = atoi(lr[10].c_str()) * atof(lr[12].c_str());
                                                                askq = lr[11];
                                                        }
                                                        else if( lr[9] == "B" && lrpair[9] == "A")
                                                        {


                                                                ask = atoi(lrpair[10].c_str()) * atof(lrpair[12].c_str());
                                                                askq = lrpair[11];
                                                                bid = atoi(lr[10].c_str()) * atof(lr[12].c_str());
                                                                bidq = lr[11];
                                                        }
                                                        if((pbid!= bid or pask != ask) && bid < ask)
                                                        {

                                                                lastprint = lrt.substr(8);
                                                                if(count(processed_seq.begin(), processed_seq.end(), to_string(seq)) == 0)
                                                                {

                                                                        processed_seq.push_back(to_string(seq));
                                                                }
                                                                writeline();
                                                                pbid = bid;
                                                                pask = ask;
                                                        }
                                                }
                                        }
                                }
                                getline(test, line);
                        }
                        //f << prevstr << endl;
                }
        }

        return 0;
}
