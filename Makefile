default:
	gcc bish.c shell.c lib/node.c lib/util.c lib/program.c -o bish -Wall -Wextra

run: default
	./bish

clean:
	rm bish *.o lib/*.o