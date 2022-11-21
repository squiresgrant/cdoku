alias b:= build
alias d:= dev
dev:
	nodemon --exec "gcc -o cdoku main.c && ./cdoku" ./main.c
	
build:
	gcc -o cdoku main.c && ./cdoku
