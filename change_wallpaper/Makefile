all:
	x86_64-w64-mingw32-gcc -c change_wallpaper.c -masm=intel -Wall -DBOF -o change_wallpaper.o
	x86_64-w64-mingw32-strip --strip-unneeded change_wallpaper.o
clean:
	rm change_wallpaper.o
