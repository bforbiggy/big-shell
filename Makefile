default:
	gcc bish.c shell.c lib/node.c lib/util.c -o bish -Wall -Wextra

run: default
	./bish

clean:
	rm bish *.o lib/*.o