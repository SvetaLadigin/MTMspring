OBJS = \
 eurovision.o \
 state.o \
 judge.o \
 new_map.o \
 utilities.o

CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG -Ilibmtm -Itests -Ieuro_tests/tests
LFLAGS = -std=c99 -Llibmtm/csl3 -lmtm

all: eurovisionTests mapTests eurovisionFacebookTests

eurovisionTests: $(OBJS) tests/eurovisionTests.o tests/eurovisionTestsMain.o
	 gcc -o $@ $^ $(LFLAGS)

mapTests: mtm_map/map.o tests/map_example_test.o
	 gcc -o $@ $^ $(LFLAGS)

eurovisionFacebookTests: $(OBJS) euro_tests/tests/main.c
	 gcc -o $@ $^ $(LFLAGS)

%.o: %.c
	 gcc -o $@ $(CFLAGS) -c $<

%.o: %.c %.h

clean:
	 rm -rf  *.o tests/*.o eurovisionTests eurovisionFacebookTests