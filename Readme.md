# Krnnt text utils

Small `Python 3` package created for [krnnt project](https://github.com/kwrobel-nlp/krnnt) written in c++.

# Installation 

To install maca_analyse you should have [ICU](http://site.icu-project.org) installed.

This will install packages to your /usr/local/lib/pythonx.x/dist-packages/

``` bash
$ sudo apt-get install pkg-config
$ git clone https://github.com/Zhylkaaa/krnnt_text_utils
$ cd krnnt_text_utils
$ ./build_text_utils_wrapper.sh
```
Now you can remove `krnnt_text_utils/` folder.

**Note:**
`sudo` is important, because build script copy generated with [SWIG](http://www.swig.org) python package to /usr/local/lib/pythonx.x/dist-packages/, if you don’t want to do so, you can comment 2 last lines in build script, or change instalation path.

## Supported systems:

Currently this tool builds only for Linux.

## Tested build configurations:

- Ubuntu 18.04 and Python 3.6.8 


