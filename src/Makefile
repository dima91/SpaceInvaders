## COMPILER
CC= g++
## COMPILER OPTIONS
CFLAGS= -Wall -pedantic -O3 -g
## LINKING OPTIONS
LINKING= -lncurses -l$(LIBNAME) -L $(LIBDIR)
## MAIN
MAINFILE= main.cpp
## OBJECT FILES
OBJECT FILES= cannon.o bullet.o bullist.o enelist.o enemy.o game.o
## LIBRARY'S NAME
LIBNAME= SpaceInvaders
## LIBRARY'S DIRECTORY 
LIBDIR= ../lib/
## HEADERS FILE
HEADERNAME= $(LIBNAME).h Components.h
## LIBRARY FILE (*.a)
LIBFILE= lib$(LIBNAME).a
## EXECUTABLE'S NAME
EXENAME= SpaceInvaders
## EXECUTABLE'S DIRECTORY
EXEDIR= ../bin/


.PHONY:	clean docu run lib

##----------##
##----------##

## Clean enviroinment from files *.o, remove old library and old executable
clean:
	-rm -fr *.o $(LIBDIR)$(LIBFILE) ./$(EXEDIR)/$(EXENAME) ../doc/* ../bin/* ./$(LIBFILE)

## Creates doxygen documentation
docu:	Doxyfile
	-rm -fr html/
	doxygen

## Compiled object files
cannon.o: cannon.cpp $(HEADERNAME)
	@echo "**** Creo cannon.o ****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

spacecraft.o: spacecraft.cpp $(HEADERNAME)
	@echo "**** Creo spacecraft.o ****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

bullet.o: bullet.cpp $(HEADERNAME)
	@echo "**** Creo bullet.o ****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

bullist.o: bullist.cpp $(HEADERNAME)
	@echo "**** Creo bullist.o ****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

enelist.o: enelist.cpp $(HEADERNAME)
	@echo "**** Creo enelist.o ****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

game.o: game.cpp $(HEADERNAME)
	@echo "***** Creo game.o *****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

enemy.o: enemy.cpp $(HEADERNAME)
	@echo "***** Creo enemy.o *****"
	$(CC) $(CFLAGS) -c $<
	cp $@ $(EXEDIR)

## Building libray
lib:
	make $(LIBDIR)/$(LIBFILE)

$(LIBDIR)/$(LIBFILE): $(OBJECT FILES)
	@echo "\n**** Creo la libreria ****"
	ar -r $(LIBFILE) $^
	cp $(LIBFILE) $(HEADERNAME) $(LIBDIR)
	@echo "\n@@**** Libreria creata!! ****@@\n"

## Building executable
build: $(MAINFILE) $(LIBDIR)/$(LIBFILE) $(HEADERNAME)
	@echo "**** Creo l'eseguibile ****"
	$(CC) $(CFLAGS) -o $(EXENAME) $(MAINFILE) $(LINKING)
	@echo "\n@@**** Eseguibile creato!! ****@@\n"
	@mv $(EXENAME) $(EXEDIR)

## Run's targets
run:
	@make build
	@echo "\n\n"
	@echo "**************************"
	@echo "**************************"
	@echo "*** Ready to play!!!!! ***"
	@echo "**************************"
	@echo "**************************"
	@sleep 2
	$(EXEDIR)/$(EXENAME)
