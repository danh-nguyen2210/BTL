all:g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
 
 all after include image : g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

g++ -I src/include -L src/lib -o main main.cpp Dog.cpp Animation.cpp Texture.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

g++ -I src/include -I Headers -L src/lib -o main main.cpp dog.cpp LTexture.cpp Stone.cpp Timer.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

g++ -I src/include -I Headers -L src/lib -o main main.cpp dog.cpp LTexture.cpp Stone.cpp Timer.cpp Variables.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer