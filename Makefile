main: main.o commandline.o readinputline.o token.o expr.o parser.o interpreter.o \
	vm_svl.o
	g++ -g -o main.out main.o commandline.o readinputline.o vm_svl.o\
		token.o expr.o parser.o interpreter.o -lreadline

clean: 
	rm *.o

main.o : main.cpp

vm_svl.o: vm_svl.cpp vm_svl.hh
interpreter.o: interpreter.cpp interpreter.hh
commandline.o: commandline.cpp commandline.hh
readinputline.o: readinputline.cpp readinputline.hh
token.o: token.cpp token.hh
expr.o: expr.cpp expr.hh
parser.o: parser.cpp parser.hh
