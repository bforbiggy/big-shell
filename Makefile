default:
	gcc bish.c util.c shell.c -o bish -Wall -Wextra

run:
	gcc bish.c util.c -o bish -Wall -Wextra
	./bish

clean:
	rm -r bish *.o