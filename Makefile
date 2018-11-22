mkdir.exe:
	mkdir exe
	mkdir exe\fonts
	xcopy fonts exe\fonts

mkdir.obj:
	mkdir obj

Engine.o: mkdir.obj Engine.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Engine.cpp -o obj\Engine.o

Fonts.o: mkdir.obj Fonts.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Fonts.cpp -o obj\Fonts.o

Game.o: mkdir.obj Game.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Game.cpp -o obj\Game.o

Graphics.o: mkdir.obj Graphics.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Graphics.cpp -o obj\Graphics.o

Audio.o: mkdir.obj Audio.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Audio.cpp -o obj\Audio.o

ILoggable.o: mkdir.obj ILoggable.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c ILoggable.cpp -o obj\ILoggable.o

Logger.o: mkdir.obj Logger.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c Logger.cpp -o obj\Logger.o

main.o: mkdir.obj main.cpp
	mingw32-g++.exe -Wall -g -IC\:\MinGW\include -c main.cpp -o obj\main.o

all: mkdir.exe main.o Logger.o ILoggable.o Graphics.o Game.o Audio.o Fonts.o Engine.o
	mingw32-g++.exe -LC\:\MinGW\lib obj\Engine.o obj\Fonts.o obj\Game.o obj\Graphics.o obj\ILoggable.o obj\Logger.o obj\main.o -o exe\test.exe -lglfw3 -lOpenGL32 -lglu32 -lfreetype -lgdi32
