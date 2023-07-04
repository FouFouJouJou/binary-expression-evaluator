compile_main: source/main.c
		@echo "compiling main"
		@[ ! -d object ] && mkdir object; gcc -c source/main.c -o object/main.o -D_GNU_SOURCE -Iinclude

run: compile_main
		@echo "running main"
		@[ ! -d build ] && mkdir build; gcc object/*.o -o build/main && build/main "$(expr)"
		@echo "exit code: $$?"
clean: 
		@rm -r build/ object/
