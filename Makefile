CPPSRC=TP1Infographie/
CC=g++

all:
	$(CC) -std=c++11 -lglew $(CPPSRC)*.cpp -o TP1InfoExec
