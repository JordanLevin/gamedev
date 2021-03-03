.PHONY: build
build:
	cd build && cmake .. && make VERBOSE=0 && cp ./game ..
