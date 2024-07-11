CC = gcc
CFLAGS = -Wall -g

all: speed_test

atomic_matix_mul.o: atomic_matrix_mul.c _atomic_matrix_mul.h
	$(CC) $(CFLAGS) -c atomic_matrix_mul.c

Serial_Matrix_Mul.o: Serial_Matrix_Multiplication.c Serial_Matrix_Mul.h
	$(CC) $(CFLAGS) -c Serial_Matrix_Multiplication.c

speed_test: atomic_matrix_mul.o Serial_Matrix_Mul.o speed_test.c
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f *.o main