main:  listinfo.o linkedlist.o main.o
	gcc main.o listinfo.o linkedlist.o -o main
    
main.o: main.c main.h
	gcc -c main.c main.h
    
linkedlist.o: linkedlist.c main.h
	gcc -c linkedlist.c main.h
    
listinfo.o: listinfo.c main.h
	gcc -c listinfo.c main.h