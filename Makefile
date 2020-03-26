IZLAZ=to-do

ifeq ($(OS),Windows_NT)
	PLATFORMA=windows
else
	PLATFORMA=linux
endif

all: ./*
	gcc main.c lib/${PLATFORMA}.c lib/razno.c  src/*.c -o ./bin/${PLATFORMA}/${IZLAZ} `pkg-config --cflags --libs gtk+-3.0` && ./bin/${PLATFORMA}/${IZLAZ}
	#rm -f ./bin/${IZLAZ}

proba: ./*
	gcc proba.c `pkg-config --cflags --libs gtk+-3.0` && ./a.out
	rm -f a.out