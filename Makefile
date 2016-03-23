all:
	g++ luDecomp.cpp main.cpp -o exe
cln:
	rm exe
push:
	git push origin master
pull:
	git pull origin master