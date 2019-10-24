build:
	g++ -w -std=c++17 -Wfatal-errors -static-libgcc -static-libstdc++ \
	./src/*.cpp \
	./src/Components/*.cpp \
	-o game.exe \
	-I"C:\libsdl\SDL2\include" \
	-I"C:\libsdl\SDL2\lib" \
	-I".\lib\lua" \
	-L".\lib\lua" \
	-llua53 \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer

clean:
	del game.exe;

run:
	game.exe;
