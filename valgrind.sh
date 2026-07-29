#!/usr/bin/env bash

valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=valgrind_out.txt \
	./build/av ./sample/in.phylip
