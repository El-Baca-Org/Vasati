derle: init topla
init:
	mkdir -p lib
topla: main.o zaman.o pugi.o
	g++ ./lib/main.o  ./lib/zaman.o ./lib/pugi.o -o Vasati

main.o: init
	g++ -I "./include" -c ./src/main.cpp -o ./lib/main.o
zaman.o: init
	g++ -I "./include" -I "./include/packages/pugixml-1.9/src" -c ./src/src-class/Zaman.cpp -o ./lib/zaman.o
pugi.o: init
	g++ -I "./include/packages/pugixml-1.9/src" -c ./include/packages/pugixml-1.9/src/pugixml.cpp -o ./lib/pugi.o

test: init zaman.o pugi.o
	g++ -I "./include" -I "./include/packages/pugixml-1.9/src" ./tests/test_zaman.cpp ./lib/zaman.o ./lib/pugi.o -o RunTests
	./RunTests

clean:
	rm -rf lib/ Vasati RunTests
