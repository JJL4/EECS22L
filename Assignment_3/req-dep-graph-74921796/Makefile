ifeq ($(OS),Windows_NT)
	RM = del /Q
	TARGET = rdgg-74921796.exe
	CLEANEXT = 2>nul || exit 0
else
	RM = rm -f
	TARGET = rdgg-74921796
	CLEANEXT =
endif

all: $(TARGET)

$(TARGET): main.o parse.o graph.o report.o
	gcc -std=c11 -Wall main.o parse.o graph.o report.o -o $(TARGET)

main.o: src/main.c include/parse.h include/graph.h include/report.h
	gcc -std=c11 -Wall -Iinclude -c src/main.c -o main.o

parse.o: src/parse.c include/parse.h include/graph.h
	gcc -std=c11 -Wall -Iinclude -c src/parse.c -o parse.o

graph.o: src/graph.c include/graph.h
	gcc -std=c11 -Wall -Iinclude -c src/graph.c -o graph.o

report.o: src/report.c include/report.h include/graph.h
	gcc -std=c11 -Wall -Iinclude -c src/report.c -o report.o

clean:
	$(RM) *.o $(TARGET) rdgg-report-74921796.md $(CLEANEXT)