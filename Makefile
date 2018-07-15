.PHONY: viewer

viewer:
	g++ -std=c++11 window.cpp -lGL -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -fpermissive
	./a.out

server:
	g++ -std=c++11 server.cpp -o iotui -fpermissive
	./iotui
server.a:
	g++ -std=c++11 server.cpp -o iotui
	./iotui -p 540 -device /dev/fb1

server.ad:
	g++ -std=c++11 server.cpp -o iotui -D_DEBUG_ -fpermissive
	./iotui -p 540 -device /dev/fb1

drawer:
	g++ -std=c++11 iotui_test.cpp -o drawer
	./drawer