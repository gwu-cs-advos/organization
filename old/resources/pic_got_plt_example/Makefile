all: compile32

compile32:
	gcc -m32 -shared -fpic demo.c -c -o demo.pic.o
	gcc -m32 -shared -fno-pic demo.c -c -o demo.nopic.o

compile64:
	gcc -shared -fpic demo.c -c -o demo.pic.o
	gcc -shared -fno-pic demo.c -c -o demo.nopic.o

dump:
	objdump -Srtl demo.pic.o
	objdump -Srtl demo.nopic.o

clean:
	rm demo*.o
