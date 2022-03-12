CC=clang++
EXEC=main
ARG=-W -Wall -pedantic
$(EXEC): cfile.o dirent2.o main.o
	$(CC) obj/cfile.o obj/dirent2.o obj/main.o -o $(EXEC) $(ARG)
cfile.o: src/cfile.cpp
	$(CC) -c src/cfile.cpp -o obj/cfile.o $(ARG)	
dirent2.o: src/dirent2.cpp
	$(CC) -c src/dirent2.cpp -o obj/dirent2.o $(ARG)	
main.o: src/main.cpp 
	$(CC) -c src/main.cpp -o obj/main.o $(ARG)	
clean:
	rm -f obj/*.o
