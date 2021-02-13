.PHONY: build
build:
	cd build && cmake .. && make VERBOSE=1 && cp ./game ..
