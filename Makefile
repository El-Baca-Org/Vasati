derle: topla
topla: main.o zaman.o pugi.o
	g++ ./lib/main.o  ./lib/zaman.o ./lib/pugi.o -o Vasati

main.o:
	g++ -I "./include" -c ./src/main.cpp -o ./lib/main.o
zaman.o:
	g++ -I "./include" -c ./src/src-class/Zaman.cpp -o ./lib/zaman.o
pugi.o:
	g++ -I "./include/packages/pugixml-1.9/src" -c ./include/packages/pugixml-1.9/src/pugixml.cpp -o ./lib/pugi.o
test: topla tests/test_zaman.cpp
	g++ -I "./include" ./tests/test_zaman.cpp ./lib/zaman.o ./lib/pugi.o -o run_tests

clean:
	rm -f Vasati run_tests lib/*.o
