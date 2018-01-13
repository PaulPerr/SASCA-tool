g++ -c -pipe -O2 -std=gnu++11 -Wall -W  -o main.o main.cpp

g++ -c -pipe -O2 -std=gnu++11 -Wall -W -o construction.o construction.cpp

g++ -O1 -W -o Construction main.o construction.o   /usr/local/lib/libhdf5.so 
