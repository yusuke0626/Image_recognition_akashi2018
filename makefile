cap: Main.cpp
	g++ Main.cpp -o cap `pkg-config --cflags opencv` `pkg-config --libs opencv`

