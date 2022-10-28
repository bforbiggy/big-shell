default:
	gcc bish.c -o bish -Wall -Wextra

run: default
	./bish

clean:
	rm -r bish *.o