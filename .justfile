build-test:
    gcc -Wall -pedantic src/test/test.c src/utils.c src/ruuvitag_decoder_core.c -o test

test: build-test
    ./test