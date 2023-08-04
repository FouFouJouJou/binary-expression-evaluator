eval: build/main
		@echo "running main"
		@build/main "$(expr)"

build/main: object/binary_expression_tree.o object/postfix.o object/main.o object/lexer.o
		@echo "linking main"
		@gcc object/*.o -o build/main 
		@echo "exit code: $$?"

object/lexer.o: source/lexer.c
		@gcc -c source/lexer.c -o object/lexer.o -D_GNU_SOURCE -Iinclude
		@echo "compiling lexer [100%]"

object/binary_expression_tree.o: source/binary_expression_tree.c
		@gcc -c source/binary_expression_tree.c -o object/binary_expression_tree.o -D_GNU_SOURCE -Iinclude
		@echo "compiling binary expression tree [100%]"

object/postfix.o: source/postfix.c
		@gcc -c source/postfix.c -o object/postfix.o -D_GNU_SOURCE -Iinclude
		@echo "compiling postfix [100%]"

object/main.o: source/main.c
		@gcc -c source/main.c -o object/main.o -D_GNU_SOURCE -Iinclude
		@echo "compiling main.c [100%]"

clean: 
		@rm -r build/* object/* 2> /dev/null
		@echo "cleaning files [100%]"
