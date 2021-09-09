CC=clang++
main: main.o
	$(CC) -o main main.o

main.o: main.cpp 
	$(CC) -c main.cpp -W -Wall -ansi -pedantic
	
clean:
	rm main main.o
