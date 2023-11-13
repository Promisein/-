head = pctl.h
srcs = pctl.cpp
objs = pctl.o
opts = -g -c
all: pctl
pctl: $(objs)
	gcc $(objs) -o pctl 
pctl.o: $(srcs) $(head)
	gcc $(opts) $(srcs) 
clean:
	rm pctl *.o