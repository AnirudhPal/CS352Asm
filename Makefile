mjavac: y.tab.c lex.yy.c
	g++ -g y.tab.c lex.yy.c interpretor.cpp -o mjavac
y.tab.c: mjavac.y
	bison -y -d -g --verbose mjavac.y
lex.yy.c: mjavac.l
	flex mjavac.l
clean:
	rm -r lex.yy.c y.tab.c mjavac y.dot y.output y.tab.h *.s\
