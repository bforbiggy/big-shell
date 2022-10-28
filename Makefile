default:
	gcc shell.c -o shell -Wall -Wextra

run:
	gcc shell.c -o shell -Wall -Wextra
	./shell

clean:
	rm -r shell *.0