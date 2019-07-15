#!/usr/bin/env bash

swig -python -c++ shape.i 
g++ -fPIC -c $(pkg-config --cflags --libs python3) shape.cpp shape_wrap.cxx 
g++ -shared -o _text_utils.so shape.o shape_wrap.o $(pkg-config --libs --cflags icu-uc icu-io)

Python_Path=$(python3 -c "import sys; print('/usr/local/lib/python' + sys.version[:3] + '/dist-packages/')")

cp _text_utils.so ${Python_Path}
cp text_utils.py ${Python_Path}