#!/bin/bash

function install()
{
	cp -v libsdl* /usr/lib/
	cp -v sdlgraph.h /usr/include/
}




gcc -shared $CFLAGS -fPIC -Wl,-soname,libsdlgraph.so.0 graph.c -o libsdlgraph.so.0.1 -lSDL

ln -s libsdlgraph.so.0.1 libsdlgraph.so
ln -s libsdlgraph.so.0.1 libsdlgraph.so.0

if [ "$1" = "install" ]; then
	install
fi


