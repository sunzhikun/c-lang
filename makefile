CC=gcc
SRC=./src/enroll.c ./src/get_time.c ./src/main.c ./src/menu.c ./src/msginfo.c ./src/purchar.c ./src/slist_buyer.c ./src/slist_enroll.c ./src/slist_goods.c ./src/slist_purchar.c
OBJS=$(SRC:.c=.o)
TARGET=./bin/a.out
INC=-I./inc
$(TARGET):$(OBJS)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) $(INC) -o $@ -c $<

.PHONY:clean
clean:
	rm ./src/*.o

.PHONY:init
init:
	rm ./file/totol.dat