main: main.o commandline.o readinputline.o token.o expr.o parser.o
	g++ -g -o main.out main.o commandline.o readinputline.o\
		token.o expr.o parser.o -lreadline

main.o : main.cpp

commandline.o: commandline.cpp commandline.hh
readinputline.o: readinputline.cpp readinputline.hh
token.o: token.cpp token.hh
expr.o: expr.cpp expr.hh
parser.o: parser.cpp parser.hh


