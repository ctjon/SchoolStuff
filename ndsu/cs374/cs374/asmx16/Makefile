#
# Makefile for ASMX16
#
all:
	cc -O asmx16.c -o asmx16

clean:
	rm -f core *.o *.xlt *.xob asmx16 *.BAK

run:
	#script asmx16.output
	make clean
	@echo "********* STANDARD.H *********"
	cat standard.h
	@echo "********* ERROR.H *********"
	cat error.h
	@echo "********* TABLE.H *********"
	cat tables.h
	@echo "********* ASMX16.C *********"
	cat asmx16.c
	@echo "********* COMPILE *********"
	make all
	@echo "************** TEST OUTPUT **************"
	@echo " "
	@echo "********* TEST1 *********"
	@echo "***** xas file *****"
	cat test1.xas
	@echo "***** assembly *****"
	asmx16 test1.xas
	@echo "***** xlt file *****"
	cat test1.xlt
	@echo "***** xob file *****"
	cat test1.xob
	@echo " "
	@echo "********* TEST2 *********"
	@echo "***** xas file *****"
	cat test2.xas
	@echo "***** assembly *****"
	asmx16 test2.xas
	@echo "***** xlt file *****"
	cat test2.xlt
	@echo "***** xob file *****"
	cat test2.xob
	@echo " "
	@echo "********* TEST3 *********"
	@echo "***** xas file *****"
	cat test3.xas
	@echo "***** assembly *****"
	asmx16 test3.xas
	@echo "***** xlt file *****"
	cat test3.xlt
	@echo "***** xob file *****"
	cat test3.xob
	@echo " "
	@echo "********* TEST4 *********"
	@echo "***** xas file *****"
	cat test4.xas
	@echo "***** assembly *****"
	asmx16 test4.xas
	@echo "***** xlt file *****"
	cat test4.xlt
	@echo "***** xob file *****"
	cat test4.xob
	@echo " "
	@echo "********* TEST5 *********"
	@echo "***** xas file *****"
	cat test5.xas
	@echo "***** assembly *****"
	asmx16 test5.xas
	@echo "***** xlt file *****"
	cat test5.xlt
	@echo "***** xob file *****"
	cat test5.xob
	@echo " "
	@echo "********* TEST6 *********"
	@echo "***** xas file *****"
	cat test6.xas
	@echo "***** assembly *****"
	asmx16 test6.xas
	@echo "***** xlt file *****"
	cat test6.xlt
	@echo "***** xob file *****"
	cat test6.xob
	@echo " "
	@echo "********* TEST7 *********"
	@echo "***** xas file *****"
	cat test7.xas
	@echo "***** assembly *****"
	asmx16 test7.xas
	@echo "***** xlt file *****"
	cat test7.xlt
	@echo "***** xob file *****"
	cat test7.xob
	@echo " "
	@echo "********* TEST8 *********"
	@echo "***** xas file *****"
	cat test8.xas
	@echo "***** assembly *****"
	asmx16 test8.xas
	@echo "***** xlt file *****"
	cat test8.xlt
	@echo "***** xob file *****"
	cat test8.xob
	@echo " "
	@echo "********* TEST9 *********"
	@echo "***** xas file *****"
	cat test9.xas
	@echo "***** assembly *****"
	asmx16 test9.xas
	@echo "***** xlt file *****"
	cat test9.xlt
	@echo "***** xob file *****"
	cat test9.xob
	@echo " "
	@echo "********* TEST10 *********"
	@echo "***** xas file *****"
	cat test10.xas
	@echo "***** assembly *****"
	asmx16 test10.xas
	@echo "***** xlt file *****"
	cat test10.xlt
	@echo "***** xob file *****"
	cat test10.xob
	@echo " "
	#exit
