main:
	gcc -std=c++17 *.cpp -o game -lSDL2 -lSDL2main -lstdc++

clear:
	rm main
