main: app.o sched.o task.o mm.o

	gcc -o main app.o sched.o task.o mm.o

app.o: app.c
	gcc -c app.c

sched.o: sched.c sched.h
	gcc -c sched.c

task.o: task.c task.h
	gcc -c task.c

mm.o: mm.c mm.h
	gcc -c mm.c

clean:
	rm -f *.o
	rm -f main
