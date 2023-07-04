run: object/binary_expression_tree.o object/postfix.o object/main.o
		@echo "linking and running"
		[ ! -d build ] && mkdir build; gcc object/*.o -o build/main && build/main "$(expr)"
		@echo "exit code: $$?"

object/binary_expression_tree.o: source/binary_expression_tree.c
		@echo "compiling binary expression tree"
		[ ! -d object ] && mkdir object; gcc -c source/binary_expression_tree.c -o object/binary_expression_tree.o -D_GNU_SOURCE -Iinclude

object/postfix.o: source/postfix.c
		@echo "compiling postfix"
		[ ! -d object ] && mkdir object; gcc -c source/postfix.c -o object/postfix.o -D_GNU_SOURCE -Iinclude

object/main.o: source/main.c
		@echo "compiling main.c"
		[ ! -d object ] && mkdir object; gcc -c source/main.c -o object/main.o -D_GNU_SOURCE -Iinclude

clean: 
		@rm -r build/ object/
