#!/bin/bash

watch 'g++ -O2 -S /tmp/test.cc -o - | c++filt'
