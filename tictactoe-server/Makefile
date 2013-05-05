# 2fa54cdb5c8b4c3ef442d21b8b7605f6
CFLAGS=-O$(O) -std=c++0x -std=c++11
O=2
LFLAGS=-l boost_system -l boost_thread -l boost_serialization -l ncurses
OBJS=objs/boardcontainer.o objs/main.o objs/board.o


.PHONY: all
all: objs tictactoe-server

./tictactoe-server: $(OBJS)
	@ echo "    LINK ./tictactoe-server"
	@ $(CXX) $(OBJS) -o "./tictactoe-server" $(LFLAGS)

objs/boardcontainer.o: boardcontainer.cpp boardcontainer.h messages.h board.h
	@ echo "    CXX  ./boardcontainer.cpp"
	@ $(CXX) $(CFLAGS) -c "./boardcontainer.cpp" -o $@
objs/main.o: main.cpp messages.h board.h boardcontainer.h
	@ echo "    CXX  ./main.cpp"
	@ $(CXX) $(CFLAGS) -c "./main.cpp" -o $@
objs/board.o: board.cpp board.h messages.h
	@ echo "    CXX  ./board.cpp"
	@ $(CXX) $(CFLAGS) -c "./board.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./tictactoe-server"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././tictactoe-server

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
