Main: Main.cpp
	g++ Main.cpp -o Main `pkg-config --cflags opencv` `pkg-config --libs opencv`
test: test.cpp
	g++ test.cpp -o test `pkg-config --cflags opencv` `pkg-config --libs opencv`
clean:
	rm test
