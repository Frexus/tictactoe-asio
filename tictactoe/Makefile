# 517f599f9b20fe5bf9e87d3e7796a52d
CFLAGS=-O$(O) -std=c++11
O=2
LFLAGS=-l boost_serialization -l boost_system -l boost_thread -l ncurses
OBJS=objs/main.o objs/gameclient.o objs/mainmenu.o objs/board.o


.PHONY: all
all: objs tictactoe-client 

./tictactoe-client : $(OBJS)
	@ echo "    LINK ./tictactoe-client "
	@ $(CXX) $(OBJS) -o "./tictactoe-client" $(LFLAGS)

objs/main.o: main.cpp gameclient.cpp gameclient.h
	@ echo "    CXX  ./main.cpp"
	@ $(CXX) $(CFLAGS) -c "./main.cpp" -o $@
objs/gameclient.o: gameclient.cpp board.cpp gameclient.h messages.h board.h
	@ echo "    CXX  ./gameclient.cpp"
	@ $(CXX) $(CFLAGS) -c "./gameclient.cpp" -o $@
objs/mainmenu.o: mainmenu.cpp mainmenu.h messages.h
	@ echo "    CXX  ./mainmenu.cpp"
	@ $(CXX) $(CFLAGS) -c "./mainmenu.cpp" -o $@
objs/board.o: board.cpp board.h messages.h
	@ echo "    CXX  ./board.cpp"
	@ $(CXX) $(CFLAGS) -c "./board.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./tictactoe-client"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././tictactoe-client 

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
