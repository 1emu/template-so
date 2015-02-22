C++ = g++
DFLAGS = -Wall -g
#OFLAGS = -O3
#LFLAGS = -lpthread
CFLAGS = $(DFLAGS) $(OFLAGS) $(LFLAGS)

PROGS = Main Terminator
OBJS = Configuration.o Utils.o Colors.o Process.o Queue.o SemaphoreArray.o SharedMemory.o Semaphore.o 

all: $(PROGS) clean

$(OBJS): %.o: %.cpp
	$(C++) -o $@ $(CFLAGS) -c $<

$(PROGS): %: %.cpp  $(OBJS)
	$(C++) -o $@ $< $(OBJS) $(CFLAGS)

clean:
	rm -f *.o

