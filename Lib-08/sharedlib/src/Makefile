LIBRARY_STATIC=libmymath.a
LIBRARY_SO=libmymath.so.1.10

all:$(LIBRARY_STATIC) $(LIBRARY_SO)

$(LIBRARY_STATIC):add.o sub.o mul.o dive.o
	ar -rcs $@ $^

$(LIBRARY_SO):add.o sub.o mul.o dive.o
	gcc -shared -Wl,-soname,libmymath.so.1 -o libmymath.so.1.10 $^

%.o:%.c
	gcc -c -fPIC $<

.PHONY:clean
clean:
	rm -rf $(LIBRARY_STATIC)
	rm -rf *.o 

