default:
	gcc shell.c util.c -o shell -Wall -Wextra

run:
	gcc shell.c util.c -o shell -Wall -Wextra
	./shell

clean:
	rm -r shell *.o