main.out:  lexer2.l grammar2.y main.cpp  opcode.o assembler.o
	bison -d grammar2.y
	flex lexer2.l
	clang++ -omain.out main.cpp Parser2.cpp Scanner2.cpp opcode.o assembler.o 

opcode.o: opcode.cpp opcode.h
	clang++ -c opcode.cpp

assembler.o: assembler.cpp assembler.h
	clang++ -c assembler.cpp

clean:
	rm -f main.out Parser2.cpp Scanner2.cpp



