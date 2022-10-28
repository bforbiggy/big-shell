default:
	gcc bish.c shell.c -o bish -Wall -Wextra

run: default
	./bish

clean:
	rm -r bish *.o