buildalll: aufgabe31.o aufgabe32.o aufgabe33.o
	mpicc -o aufgabe31 -std=c11 aufgabe31.o
	mpicc -o aufgabe32 -std=c11 aufgabe32.o
	mpicc -o aufgabe33 -std=c11 aufgabe33.o
	
aufgabe31.o: aufgabe.3.1.c
	mpicc -o aufgabe31.o -std=c11 -c aufgabe.3.1.c 

aufgabe32.o: aufgabe.3.2.c
	mpicc -o aufgabe32.o -std=c11 -c aufgabe.3.2.c

aufgabe33.o: aufgabe.3.3.c
	mpicc -o aufgabe33.o -std=c11 -c aufgabe.3.3.c
    
clean:
	rm aufgabe31.o aufgabe32.o aufgabe33.0 aufgabe31 aufgabe32 aufgabe33
