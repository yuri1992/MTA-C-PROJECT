MTA-C-PROJECT:main.o add-apt.o buy-apt.o apartment.o delete-apt.o find-apt.o history.o lineinteperter.o utils.o
	gcc -o MTA-C-PROJECT main.o add-apt.o buy-apt.o apartment.o 				delete-apt.o find-apt.o history.o lineinteperter.o utils.o

add-apt.o: add-apt.c add-apt.h
	gcc -c add-apt.c

 apartment.o:  apartment.c  apartment.h utils.h
	gcc -c apartment.c

 buy-apt.o:  buy-apt.c buy-apt.h lineinteperter.h
	gcc -c  buy-apt.c

delete-apt.o: delete-apt.c delete-apt.h  lineinteperter.h apartment.h
	gcc -c  delete-apt.c

find-apt.o: find-apt.c find-apt.h  lineinteperter.h delete-apt.h  apartment.h
	gcc -c  find-apt.c

history.o: history.c history.h
	gcc -c  history.c

lineinteperter.o: lineinteperter.c lineinteperter.h find-apt.h buy-apt.h add-apt.h history.h utils.h apartment.h
	gcc -c  lineinteperter.c

main.o: main.c history.h lineinteperter.h
	gcc -c  main.c

utils.o: utils.c utils.h
	gcc -c  utils.c


