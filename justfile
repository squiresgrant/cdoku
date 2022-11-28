alias b:= build
alias d:= dev
alias wd:= windows-dev
set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]
dev:
	nodemon --exec "gcc -o cdoku main.c && ./cdoku" ./main.c

windows-dev:
	nodemon --exec "gcc -o cdoku main.c && cdoku" main.c
	
build:
	gcc -o cdoku main.c
