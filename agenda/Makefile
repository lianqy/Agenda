# Makefile
CC := g++-4.8
FLAGS := -std=c++0x -w

bin/main: build/AgendaService.o build/Date.o build/Meeting.o build/Storage.o build/User.o build/AgendaUI.o build/Agenda.o
	$(CC) $(FLAGS) -I./include build/Agenda.o build/AgendaUI.o build/AgendaService.o build/Date.o build/Meeting.o build/Storage.o build/User.o -o $@

build/AgendaService.o: src/AgendaService.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/AgendaService.cpp

build/Date.o: src/Date.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/Date.cpp

build/Meeting.o: src/Meeting.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/Meeting.cpp

build/Storage.o: src/Storage.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/Storage.cpp

build/User.o: src/User.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/User.cpp

build/AgendaUI.o: src/AgendaUI.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/AgendaUI.cpp

build/Agenda.o: src/Agenda.cpp
	$(CC) $(FLAGS) -I./include -c -g -o $@ src/Agenda.cpp

clean:
	@rm -rf build 
	@rm -rf bin
	@mkdir build
	@mkdir bin