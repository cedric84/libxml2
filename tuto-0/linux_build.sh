#! /bin/bash

CC=cc
LIBXML2_PATH=../install/x86_64-linux
${CC} -Wall -Werror -o./app				\
	-I${LIBXML2_PATH}/include/libxml2	\
	-L${LIBXML2_PATH}/lib				\
	-Wl,-rpath,\$ORIGIN/../lib			\
	./main.c							\
	-lxml2								\
	-liconv								\
	-lm
