all: pi roman

pi: pi.cpp ; g++ -o pi pi.cpp -I.

roman: roman.cpp ; g++ -o roman roman.cpp -I.

run_pi:
	./pi

run_roman:
	./roman

clean:
	rm -f *.o pi roman
