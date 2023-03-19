PROGRAM=gajdijan

CC=g++ -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb

run: compile
	./$(PROGRAM) ./examples/inline_ProgTest.html ./examples/out-file.html -c ./examples/gajdijan.conf

all: compile doc

compile: $(PROGRAM)

doc: src/main.cpp src/main.hpp src/configuration.cpp src/configuration.hpp src/page.cpp \
 src/page.hpp src/fileError.hpp src/token.hpp src/token.cpp src/syntaxError.hpp \
 src/tokens/tag.hpp src/tokens/tag.cpp src/tokens/cdata.hpp src/tokens/text.hpp \
 src/tokens/comment.hpp src/tokens/endTag.hpp src/tokens/startTag.hpp \
 src/tokens/tag.hpp src/tokens/text.hpp src/tokens/unknown.hpp src/tokens/voidTag.hpp
	doxygen Doxyfile

clean:
	rm -rf $(PROGRAM) *.o doc/ examples/out-file.html

$(PROGRAM): main.o configuration.o page.o token.o text.o comment.o \
 cdata.o tag.o unknown.o endTag.o voidTag.o startTag.o
	$(CC) $^ -o $@

main.o: src/main.cpp src/main.hpp src/configuration.hpp src/fileError.hpp \
 src/page.hpp src/syntaxError.hpp
	$(CC) -c $< -o $@

configuration.o: src/configuration.cpp src/configuration.hpp src/fileError.hpp
	$(CC) -c $< -o $@

page.o: src/page.cpp src/page.hpp src/configuration.hpp src/fileError.hpp \
 src/syntaxError.hpp src/token.hpp
	$(CC) -c $< -o $@
	
token.o: src/token.cpp src/token.hpp src/tokens/text.hpp \
 src/tokens/comment.hpp src/tokens/tag.hpp src/tokens/cdata.hpp \
 src/tokens/unknown.hpp src/syntaxError.hpp src/tokens/endTag.hpp \
 src/tokens/voidTag.hpp src/tokens/startTag.hpp
	$(CC) -c $< -o $@

text.o: src/tokens/text.cpp src/tokens/text.hpp src/token.hpp
	$(CC) -c $< -o $@

comment.o: src/tokens/comment.cpp src/tokens/comment.hpp src/token.hpp
	$(CC) -c $< -o $@

cdata.o: src/tokens/cdata.cpp src/tokens/cdata.hpp src/token.hpp
	$(CC) -c $< -o $@
	
unknown.o: src/tokens/unknown.cpp src/tokens/unknown.hpp src/token.hpp
	$(CC) -c $< -o $@
	
tag.o: src/tokens/tag.cpp src/tokens/tag.hpp src/token.hpp
	$(CC) -c $< -o $@

endTag.o: src/tokens/endTag.cpp src/tokens/endTag.hpp src/token.hpp
	$(CC) -c $< -o $@

voidTag.o: src/tokens/voidTag.cpp src/tokens/voidTag.hpp src/tokens/tag.hpp
	$(CC) -c $< -o $@

startTag.o: src/tokens/startTag.cpp src/tokens/startTag.hpp src/tokens/tag.hpp
	$(CC) -c $< -o $@

