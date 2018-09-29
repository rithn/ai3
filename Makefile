SRC=  src/getClauses.cpp 

all: $(SRC)
	  g++ -O3 -o getClauses.out $(SRC)

debug: $(SRC)
	  g++ -g -o getClauses.out $(SRC)

debug_out: $(SRC)
	  g++ -DUSEDEBUG -g -o getClauses.out $(SRC)

warnings: $(SRC)
	  g++ -g -Wall -Wextra -o getClauses.out $(SRC)

clean:
	rm -rf build
	rm -rf main
