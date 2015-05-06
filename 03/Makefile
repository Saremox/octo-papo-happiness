buildalll: aufgabe31.o aufgabe32.o
	mpicc -o aufgabe31 -std=c11 aufgabe31.o
	mpicc -o aufgabe32 -std=c11 aufgabe32.o
	
aufgabe31.o: aufgabe.3.1.c
	mpicc -o aufgabe31.o -std=c11 -c aufgabe.3.1.c 

aufgabe32.o: aufgabe.3.2.c
	mpicc -o aufgabe32.o -std=c11 -c aufgabe.3.2.c
    
clean:
	rm aufgabe31.o aufgabe32.o aufgabe31 aufgabe32 
