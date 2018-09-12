tube: main.o tube.o
	g++ -g main.o tube.o -o tube

main.o: main.cpp tube.h
	g++ -g -Wall -c main.cpp

tube.o: tube.cpp tube.h
	g++ -g -Wall -c tube.cpp

clean:
	rm -f *.o mcslab_1_exe
