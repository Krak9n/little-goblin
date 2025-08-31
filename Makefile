CC=as
LI=ld
B_FILES=src
SRC=$(B_FILES:%=%.s)
O=$(SRC:%.s=%.o)

out: 
	$(B_FILES)
	
%: %.s 
	$(CC) -o $@.o $<
	$(LI) -o $@ $@.o

.PHONY: clean

clean:
	rm -f $(O) 
