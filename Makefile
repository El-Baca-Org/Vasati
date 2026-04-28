derle: init topla
init:
	mkdir -p lib
topla: main.o zaman.o pugi.o
	g++ ./lib/main.o  ./lib/zaman.o ./lib/pugi.o -o Vasati

main.o:
	g++ -I "./include" -c ./src/main.cpp -o ./lib/main.o
zaman.o:
	g++ -I "./include" -c ./src/src-class/Zaman.cpp -o ./lib/zaman.o
pugi.o:
	g++ -I "./include/packages/pugixml-1.9/src" -c ./include/packages/pugixml-1.9/src/pugixml.cpp -o ./lib/pugi.o

test: init test_zaman.o zaman.o pugi.o
	g++ ./lib/test_zaman.o ./lib/zaman.o ./lib/pugi.o -o RunTests
	./RunTests

test_zaman.o:
	g++ -I "./include" -c ./src/tests/test_zaman.cpp -o ./lib/test_zaman.o
