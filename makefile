compile: ajex.o identity.o meta.o numerical.o stack.o string.o validity.o  
	  gcc -o ajex ajex.o identity.o meta.o numerical.o stack.o string.o validity.o
	  rm  ./bin/*.o
	  mv ./*.o ./bin
	  clear
	  
ajex.o: ./source/header.h
	  gcc -c ./source/ajex.c
identity.o:./source/header.h
	  gcc -c ./source/identity.c
meta.o: ./source/header.h
	  gcc -c ./source/meta.c
numerical.o: ./source/header.h
	  gcc -c ./source/numerical.c
stack.o: ./source/header.h 	
	  gcc -c ./source/stack.c
string.o: ./source/header.h	
	  gcc -c ./source/string.c
validity.o:	./source/header.h
	  gcc -c ./source/validity.c
clear:
	  rm *.o 

	

