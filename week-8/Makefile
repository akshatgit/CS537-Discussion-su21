CC=gcc
CFLAGS=-Wall -Werror -O2
CLIBS=-lpthread -lrt

TARGETS=multi-threading shared-memory-wr shared-memory-rd signal-handler


.PHONY: all
all: ${TARGETS}

multi-threading: multi-threading.c
	${CC} ${CFLAGS} $< -o $@ ${CLIBS}

shared-memory-wr: shared-memory-wr.c
	${CC} ${CFLAGS} $< -o $@ ${CLIBS}

shared-memory-rd: shared-memory-rd.c
	${CC} ${CFLAGS} $< -o $@ ${CLIBS}

signal-handler: signal-handler.c
	${CC} ${CFLAGS} $< -o $@


.PHONY: clean
clean:
	rm -f ${TARGETS}
