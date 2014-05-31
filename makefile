# Makefile du projet Sudoku.
# auteur : Jude Seide
# -----------------------------

# version construction avec tests unitaires :

#FLAGS=-D TESTS_UNITAIRES

# version construction sans tests unitaires :

#FLAGS=

# version final :

#FLAGS=-D NDEBUG


CC=gcc
BIN=sudoku
DOC_REP=doc
ARCHIVE=sudoku
OBJETS=\
        main.o \
        metrique.o \
        sudoku.o \
        tri.o


all : $(OBJETS)
	$(CC) $(FLAGS) $(OBJETS) -lm -o $(BIN)

.c.o :
	$(CC) $(FLAGS) -c $<
	
main.o : main.c sudoku.h metrique.h tri.h

metrique.o : metrique.c metrique.h sudoku.h

sudoku.o : sudoku.c sudoku.h

tri.o : tri.c tri.h sudoku.h

doc : 
	doxygen main.c metrique.c metrique.h tri.c tri.h sudoku.c sudoku.h

archive : clean
	\rm -f $(ARCHIVE).tar.gz
	tar cvf $(ARCHIVE).tar *
	gzip $(ARCHIVE).tar

clean :
	\rm -f $(BIN)
	\rm -f *.o
	\rm -f *~
	\rm -f core
	\rm -fr html
	\rm -fr latex
