objects=module.o main.o bfs.o

all: main
main: $(objects)
	gcc -o main main.o module.o bfs.o
bfs.o: bfs.c
	gcc -c bfs.c
module.o: module.c
	gcc -c module.c
main.o: main.c
	gcc -c main.c
clean:
	rm main $(objects)
graph1:
	./main < Graph.txt
graph2:
	./main < Graph2.txt