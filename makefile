all: pi bj2

pi: pi.cpp ; g++ -o pi pi.cpp -I.

bj2: bj2.cpp ; g++ -o bj2 bj2.cpp -I.

run_pi:
	./pi

run_bj2:
	./bj2

clean:
	rm -f *.o pi bj2
