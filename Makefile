all:
        g++ serverFinal.cpp -o server.exe
        g++ clientFinal.cpp -o client.exe
        
        g++ MergeDump.cpp -o MDcpp.exe -std=c++11
        ./MDcpp.exe EMINI1 Adhikari

