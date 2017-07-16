all:
	cd src && make

run:
	cd src && make run

clean:
	cd src && make clean
	rm -f os.iso *.o
