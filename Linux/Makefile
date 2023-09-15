integer_polynomial_system_debug: polynomial.h main.cpp
	mkdir -p bin/IntegerDebug
	mkdir -p obj/IntegerDebug
	g++-12 -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=c++17 -fPIC -Og -g -c main.cpp -o obj/IntegerDebug/main.o
	g++-12 -o bin/IntegerDebug/integer_polynomial_system obj/IntegerDebug/main.o -static-libstdc++ -static

integer_polynomial_system_release: polynomial.h main.cpp
	mkdir -p bin/IntegerRelease
	mkdir -p obj/IntegerRelease
	g++-12 -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=c++17 -fPIC -fomit-frame-pointer -fexpensive-optimizations -O3 -c main.cpp -o obj/IntegerRelease/main.o
	g++-12 -o bin/IntegerRelease/integer_polynomial_system obj/IntegerRelease/main.o -static-libstdc++ -static -s

decimal_polynomial_system_debug: polynomial.h main.cpp
	mkdir -p bin/DecimalDebug
	mkdir -p obj/DecimalDebug
	g++-12 -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=c++17 -fPIC -Og -g -DDECIMAL_VERSION -c main.cpp -o obj/DecimalDebug/main.o
	g++-12 -o bin/DecimalDebug/decimal_polynomial_system obj/DecimalDebug/main.o -static-libstdc++ -static

decimal_polynomial_system_release: polynomial.h main.cpp
	mkdir -p bin/DecimalRelease
	mkdir -p obj/DecimalRelease
	g++-12 -pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=c++17 -fPIC -fomit-frame-pointer -fexpensive-optimizations -O3 -DDECIMAL_VERSION -c main.cpp -o obj/DecimalRelease/main.o
	g++-12 -o bin/DecimalRelease/decimal_polynomial_system obj/DecimalRelease/main.o -static-libstdc++ -static -s

polynomial_system_debug: polynomial.h main.cpp
	make integer_polynomial_system_debug
	make decimal_polynomial_system_debug

polynomial_system_release: polynomial.h main.cpp
	make integer_polynomial_system_release
	make decimal_polynomial_system_release

polynomial_system: polynomial.h main.cpp
	make polynomial_system_debug 
	make polynomial_system_release 
