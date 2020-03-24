IZLAZ=to-do
all: ./*
	gcc main.c lib/*.c -o ${IZLAZ} `pkg-config --cflags --libs gtk+-3.0` && ./${IZLAZ}
	rm -f ${IZLAZ}

proba: ./*
	gcc proba.c lib/*.c && ./a.out
	rm -f a.out