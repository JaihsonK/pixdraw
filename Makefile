src := src/main.c

all:
	rm -rf ./pixdraw
	cc ${src} -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o ./pixdraw
install: all
	sudo rm -rf /usr/bin/pixdraw
	sudo cp ./pixdraw /usr/bin/