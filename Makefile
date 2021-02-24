CC=g++ -g -Wall

QUESTION_SOURCES =Q2.cpp

# Generate the names of the disk scheduler's object files
QUESTION_OBJS=${QUESTION_SOURCES:.cpp=.o}

all: thing

# Compile the disk scheduler and tag this compilation
thing: ${QUESTION_OBJS}
	${CC} -o $@ $^ -ldl -pthread

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${QUESTION_OBJS} thing
