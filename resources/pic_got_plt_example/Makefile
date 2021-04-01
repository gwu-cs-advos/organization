all:
	gcc -m32 -fpic -pie demo.c -c -o demo.pic.o
	gcc -m32 -fno-pic -no-pie demo.c -c -o demo.nopic.o

dump:
	objdump -Srtl demo.pic.o
	objdump -Srtl demo.nopic.o

clean:
	rm demo.pic.o
	rm demo.nopic.o
