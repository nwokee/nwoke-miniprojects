CWFLAGS=-Wall -Wextra

all: mem_mgr

mem_mgr.o:	mem_mgr.cpp mem_mgr.h
	g++ $(CWFLAGS) -O2 -c mem_mgr.cpp

mm_sim_main.o:	mm_sim_main.cpp mem_mgr.h
	g++ $(CWFLAGS) -O2 -c mm_sim_main.cpp

mem_mgr: mm_sim_main.o mem_mgr.o
	g++ $(CWFLAGS) -O2 mm_sim_main.o mem_mgr.o -o mem_mgr

clean:
	rm -f *.o mem_mgr.exe mem_mgr