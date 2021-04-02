all:
        g++ serverFinal.cpp -o server.exe
        g++ clientFinal.cpp -o client.exe
        
        g++ MergeDump.cpp -o MDcpp.exe -std=c++11
        ./MDcpp.exe EMINI1 Adhikari
        
        g++ newserver.cpp -o newserver.exe
        g++ decode2.cpp -o decode2.exe -lpcap -std=c++11


