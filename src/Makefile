
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c11
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
COVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS = -lcheck
FILES = function/*.c function/arithmetics/*.c function/comparer/*.c function/converters/*.c function/other/*.c

all: s21_decimal.a gcov_report

s21_decimal.a: s21_decimal.o
	ar rc libs21_decimal.a *.o
	ranlib libs21_decimal.a
	cp libs21_decimal.a s21_decimal.a

s21_decimal.o: function/*.c function/arithmetics/*.c function/comparer/*.c function/converters/*.c function/other/*.c s21_decimal.h
	$(CC) $(CFLAGS) -c $(FILES)

test.o: test.c s21_decimal.h
	$(CC) $(CFLAGS) -c test.c

test: test.o s21_decimal.a
	$(CC) $(CFLAGS)  *.o $(TESTFLAGS) -o test_decimal

leaks: s21_decimal.a
	clear
	$(CC) $(CFLAGS) test.c s21_decimal.a -o v
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./v
	leaks -atExit -- ./v
	$(CC) $(LFLAGS) test.c s21_decimal.a -o 1
	./1

gcov_report: test
	$(CC) $(CFLAGS) test.c libs21_decimal.a $(TESTFLAGS) $(COVFLAGS) function/*.c function/arithmetics/*.c function/comparer/*.c function/converters/*.c function/other/*.c -o test_decimal
	./test_decimal
	lcov -t test_decimal -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	# rm -rf *.gcda *.gcno *.info
	
style:
	clang-format -n --style=Google *.c function/*.c function/arithmetics/*.c function/comparer/*.c function/converters/*.c function/other/*.c
	clang-format -n --style=Google *.c *.h

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info 
	rm test_decimal
	rm -r report

.PHONY: all, test, gcov_report, style, clean, s21_decimal.a
