TARGET  := emLisp
SRCS    := src/test_runner.c src/lexer_test.c src/lexer.c src/cunit.c src/parser_test.c src/parser.c
OBJS    := ${SRCS:.c=.o}
DEPS    := ${SRCS:.c=.dep}
XDEPS   := $(wildcard ${DEPS})

CCFLAGS = -std=gnu99 -O2 -Wall -Werror -ggdb 
LDFLAGS = 
LIBS    = 

.PHONY: all clean distclean 
all:: ${TARGET} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 

${OBJS}: %.o: %.c %.dep 
	${CC} ${CCFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.c Makefile 
	${CC} ${CCFLAGS} -MM $< > $@ 

clean:: 
	-rm -f *~ src/*.o src/*.dep ${TARGET} 

distclean:: clean
