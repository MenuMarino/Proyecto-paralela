output: secuential iterative parallel

secuential:
	g++ -std=c++17 Secuential\ for\ BAB.cpp -o secuential.exe

iterative:
	g++ -std=c++17 Iterative\ for\ BAB.cpp -o iterative.exe

parallel:
	g++ -std=c++17 -lomp Parallel\ for\ BAB.cpp -o parallel.exe

run:
	./secuential.exe && ./iterative.exe && ./parallel.exe

clean:
	rm iterative.exe parallel.exe secuential.exe a.out