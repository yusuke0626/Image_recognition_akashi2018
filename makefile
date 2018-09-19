Main: Main.cpp
	g++ Main.cpp -o Main `pkg-config --cflags opencv` `pkg-config --libs opencv`

