eval: build/main
		@echo "running main"
		@build/main "$(expr)"

build/main: object/binary_expression_tree.o object/postfix.o object/main.o object/lexer.o
		@echo "linking main"
		@gcc object/*.o -o build/main 
		@echo "exit code: $$?"

object/lexer.o: source/lexer.c
		@echo "compiling lexer"
		@gcc -c source/lexer.c -o object/lexer.o -D_GNU_SOURCE -Iinclude

object/binary_expression_tree.o: source/binary_expression_tree.c
		@echo "compiling binary expression tree"
		@gcc -c source/binary_expression_tree.c -o object/binary_expression_tree.o -D_GNU_SOURCE -Iinclude

object/postfix.o: source/postfix.c
		@echo "compiling postfix"
		@gcc -c source/postfix.c -o object/postfix.o -D_GNU_SOURCE -Iinclude

object/main.o: source/main.c
		@echo "compiling main.c"
		@gcc -c source/main.c -o object/main.o -D_GNU_SOURCE -Iinclude

clean: 
		@rm -r build/* object/* 2> /dev/null
