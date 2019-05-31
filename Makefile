all:
	gcc daemon.c -o daemon
	gcc cli.c -o cli

clean:
	rm cli
	rm daemon
