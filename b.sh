make && gcc test.c -O0 -g -fsanitize=address -L. -lftprintf && ./a.out
