all: ReqDepGraph
ReqDepGraph: main.o parse.o graph.o report.o
	gcc -std=c11 -Wall main.o parse.o graph.o report.o -o ReqDepGraph
main.o: src/main.c include/parse.h include/graph.h include/report.h 
	gcc -std=c11 -Wall -c src/main.c -o main.o
parse.o: src/parse.c include/parse.h include/graph.h include/report.h 
	gcc -std=c11 -Wall -c src/parse.c -o parse.o
graph.o: src/graph.c include/parse.h include/graph.h include/report.h 
	gcc -std=c11 -Wall -c src/graph.c -o graph.o
report.o: src/report.c include/parse.h include/graph.h include/report.h
	gcc -std=c11 -Wall -c src/report.c -o report.o
clean:
	rm -f *.o ReqDepGraph