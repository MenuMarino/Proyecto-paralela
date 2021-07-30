output: secuential iterative parallel

secuential:
	g++ -std=c++17 Secuential\ w_fuel\ for\ BAB.cpp -o secuential_f.exe
	g++ -std=c++17 Secuential\ for\ BAB.cpp -o secuential.exe

iterative:
	g++ -std=c++17 Iterative\ w_fuel\ for\ BAB.cpp -o iterative_f.exe
	g++ -std=c++17 Iterative\ for\ BAB.cpp -o iterative.exe

parallel:
	g++ -std=c++17 -fopenmp Parallel\ w_fuel\ for\ BAB.cpp -o parallel_f.exe
	g++ -std=c++17 -fopenmp Parallel\ for\ BAB.cpp -o parallel.exe

run:
	./secuential.exe && ./iterative.exe && ./parallel.exe

runfuel:
	./secuential_f.exe && ./iterative_f.exe && ./parallel_f.exe

clean:
	rm *.exe