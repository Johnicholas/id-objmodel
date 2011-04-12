CC = cc
CFLAGS = -g -O2

all : prim-c prim-obj info

obj.o : obj.c
	$(CC) $(CFLAGS) -c -o obj.o obj.c

prim-c : prim-c.c
	$(CC) $(CFLAGS) -o prim-c prim-c.c

prim-obj : prim-obj.c
	$(CC) $(CFLAGS) -o prim-obj prim-obj.c

info : obj.o .FORCE
	@echo
	@echo "size of object library:"
	@size obj.o
	@echo
	@echo "you should now run 'time ./prim-c'"
	@echo "and                'time ./prim-obj'"
	@echo
	@echo "have fun!"
	@echo

clean : .FORCE
	rm -f prim-c prim-obj obj.o *~

.FORCE :
