Main: Main.cpp
	g++ Main.cpp -o Main -std=c++11 `pkg-config --cflags opencv` `pkg-config --libs opencv`
test: test.cpp
	g++ test.cpp -o test -std=c++11 `pkg-config --cflags opencv` `pkg-config --libs opencv`
clean:
	rm test
