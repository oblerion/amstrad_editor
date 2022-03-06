CC=clang++
EXEC=main
ARG=-W -Wall -pedantic
$(EXEC): main.o
	$(CC) obj/main.o -o $(EXEC) $(ARG) 
main.o: src/main.cpp 
	$(CC) -c src/main.cpp -o obj/main.o $(ARG)	
clean:
	rm -f obj/*.o
