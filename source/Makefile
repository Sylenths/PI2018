mingw:
	g++ -std=c++14 -Dmain=SDL_main -I/mingw64/include/SDL2 -I/mingw64/include/mesa main.cpp -o PI2018 -L/mingw64/lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

mac:
	g++ -std=c++14 -Dmain=SDL_main main.cpp -o PI2018

clean:
	rm PI2018.exe

run:
	./PI2018.exe
