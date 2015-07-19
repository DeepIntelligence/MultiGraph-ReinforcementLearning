CC = g++
CFLAGS = -std=c++0x -I/opt/boost/boost_1_57_0 -Wall -g3 -DDEBUG
LFLAGS = 

#all:map_ser

OBJS= main.o MultiGraph_QL.o RLSolver.o model.o

test: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $^

#map_ser.o:map_ser.cpp
#	$(CC) -c $(CFLAGS) map_ser.cpp

#rod_static: $(OBJS)
#	$(CC) -o $@ $(OBJS) -static $(LFLAGS)

clean:
	rm *.o 
