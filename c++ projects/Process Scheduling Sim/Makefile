CWFLAGS=-Wall -Wextra

all: proc_sched

proc_sched.o:	proc_sched.cpp proc_sched.h
	g++ $(CWFLAGS) -O2 -c proc_sched.cpp

ps_sim_main.o:	ps_sim_main.cpp proc_sched.h
	g++ $(CWFLAGS) -O2 -c ps_sim_main.cpp

proc_sched: ps_sim_main.o proc_sched.o
	g++ $(CWFLAGS) -O2 ps_sim_main.o proc_sched.o -o proc_sched

clean:
	rm -f *.o proc_sched.exe proc_sched debug.txt