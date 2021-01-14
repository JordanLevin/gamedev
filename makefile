.PHONY: build
build:
	cd build && cmake .. && make && cp ./game ..
