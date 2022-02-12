target: test_program

test_program: test_program.c epslib.h proje.c
	      gcc test_program.c proje.c -lm -o test_program
