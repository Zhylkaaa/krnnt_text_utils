#!/usr/bin/env bash

swig -python -c++ krnnt_utils.i 
g++ -fPIC -c $(pkg-config --cflags --libs python3) shape.cpp flatten.cpp uniq.cpp create_tags5_without_guesser.cpp create_tags4_without_guesser.cpp krnnt_utils_wrap.cxx
g++ -shared -o _krnnt_utils.so shape.o flatten.o uniq.o create_tags5_without_guesser.o create_tags4_without_guesser.o krnnt_utils_wrap.o $(pkg-config --libs --cflags icu-uc icu-io)

Python_Path=$(python3 -c "import sys; print('/usr/local/lib/python' + sys.version[:3] + '/dist-packages/')")

cp _krnnt_utils.so ${Python_Path}
cp krnnt_utils.py ${Python_Path}