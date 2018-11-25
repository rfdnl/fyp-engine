mkdir.exe:
	mkdir exe
	mkdir exe\fonts
	mkdir exe\audio
	xcopy dll exe
	xcopy fonts exe\fonts
	xcopy audio exe\audio

mkdir.obj:
	mkdir obj

clean:
	rmdir /s /q obj
	rmdir /s /q exe

rebuild: clean all

Audio.o: mkdir.obj Audio.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Audio.cpp -o obj\Audio.o

Engine.o: mkdir.obj Engine.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Engine.cpp -o obj\Engine.o

Fonts.o: mkdir.obj Fonts.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Fonts.cpp -o obj\Fonts.o

Game.o: mkdir.obj Game.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Game.cpp -o obj\Game.o

Graphics.o: mkdir.obj Graphics.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Graphics.cpp -o obj\Graphics.o

ILoggable.o: mkdir.obj ILoggable.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c ILoggable.cpp -o obj\ILoggable.o

lodepng.o: mkdir.obj lodepng.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c lodepng.cpp -o obj\lodepng.o

Logger.o: mkdir.obj Logger.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Logger.cpp -o obj\Logger.o

main.o: mkdir.obj main.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c main.cpp -o obj\main.o

TestGame.o: mkdir.obj TestGame.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c TestGame.cpp -o obj\TestGame.o

all: mkdir.exe main.o Audio.o Logger.o ILoggable.o Graphics.o Game.o Fonts.o Engine.o lodepng.o TestGame.o
	mingw32-g++.exe -LC\:\MinGW\lib obj\Engine.o obj\Audio.o obj\Fonts.o obj\Game.o obj\Graphics.o obj\ILoggable.o obj\lodepng.o obj\Logger.o obj\main.o obj\TestGame.o -o exe\test.exe -lglfw3 -lopengl32 -lglu32 -lfreetype -lgdi32 -lopenal32 -lcommon -lalut

