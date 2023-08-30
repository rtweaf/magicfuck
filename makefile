CXXFLAGS := -std=c++20 -Wall -Wextra -I include/

magicfuck: main.o lexer.o parser.o executor.o
	$(CXX) $(CXXFLAGS) $^ -o magicfuck

magicfuck_debug: test.o lexer.o parser.o
	$(CXX) $(CXXFLAGS) $^ -o magicfuck_debug

main.o: main.cpp include/lexer.hpp include/parser.hpp
lexer.o: include/lexer.hpp
parser.o: include/lexer.hpp include/parser.hpp
executor.o: include/executor.hpp include/parser.hpp
test.o: include/lexer.hpp include/parser.hpp

.PHONY: clean
clean:
	rm *.o magicfuck