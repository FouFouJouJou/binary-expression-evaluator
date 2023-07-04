compile_binary_expression_tree: source/binary_expression_tree.c
		@echo "compiling binary expression tree"
		@[ ! -d object ] && mkdir object; gcc -c source/binary_expression_tree.c -o object/binary_expression_tree.o -D_GNU_SOURCE -Iinclude

compile_postfix: source/postfix.c
		@echo "compiling postfix"
		@[ ! -d object ] && mkdir object; gcc -c source/postfix.c -o object/postfix.o -D_GNU_SOURCE -Iinclude

compile_main: source/main.c
		@echo "compiling main.c"
		@[ ! -d object ] && mkdir object; gcc -c source/main.c -o object/main.o -D_GNU_SOURCE -Iinclude

run: compile_postfix compile_binary_expression_tree compile_main 
		@echo "running main"
		@[ ! -d build ] && mkdir build; gcc object/*.o -o build/main && build/main "$(expr)"
		@echo "exit code: $$?"
clean: 
		@rm -r build/ object/
