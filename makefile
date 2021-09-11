all: bj bj2

bj: bj.cpp ; g++ -o bj bj.cpp -I.

bj2: bj2.cpp ; g++ -o bj2 bj2.cpp -I.

run_bj:
	./bj

run_bj2:
	./bj2

clean:
	rm -f *.o bj bj2
