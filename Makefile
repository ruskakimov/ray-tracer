main.out: ./src/main.c ./src/utils/*.c ./src/utils/*.h
	gcc ./src/main.c ./src/utils/*.c -o main.out
