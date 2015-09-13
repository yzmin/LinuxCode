LIBRARY_STATIC=libmymath.a
all:$(LIBRARY_STATIC)

$(LIBRARY_STATIC):add.o sub.o mul.o dive.o
	ar -rcs $@ $^

%.o:%.c
	gcc -c $<

.PHONY:clean
clean:
	rm -rf $(LIBRARY_STATIC)
	rm -rf *.o 

