selfparse:
	g++ -g -Wall -o gsim net.cpp gsim.cpp gates.cpp design.cpp vlg_parser_man.cpp 

autoparse:
	flex verilog.lex
	bison -v -d verilog.y
	g++ -g -Wall -DAUTOPARSE -o gsim verilog.tab.c lex.yy.c vlg_parser_auto.cpp net.cpp  gates.cpp design.cpp  gsim.cpp 


install_flex:
	sudo apt-get install flex
	sudo apt-get install bison
