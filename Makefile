all:
	$(MAKE) -C src

run:
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean
	rm -f os.iso *.o
