IZLAZ=to-do
all: ./*
	gcc test.c -o to-do `pkg-config --cflags --libs gtk+-3.0` && ./to-do
	rm -f to-do