build:
	gcc main.c -o riscy

clean:
	rm -rf riscy

rebuild: clean build