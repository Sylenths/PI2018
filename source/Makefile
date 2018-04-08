mingw:
	g++ -std=c++14 -Dmain=SDL_main -I/mingw64/include/SDL2 -I/mingw64/include/mesa main.cpp -o cmake-build-debug/PI2018 -L/mingw64/lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

mac:
	g++ -std=c++14 -D_THREAD_SAFE -I/opt/local/include/SDL2 main.cpp -o cmake-build-debug/PI2018 -framework OpenGL -framework SDL2 -framework SDL2_ttf -framework SDL2_image

clean:
	rm ./cmake-build-debug/PI2018*

run:
	./cmake-build-debug/PI2018
