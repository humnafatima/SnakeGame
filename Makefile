all:
	@cmake -B build
	@cmake --build build
	@./build/SnakeGame

clean:
	@rm -rf build

.PHONY: all clean
