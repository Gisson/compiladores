#!/bin/bash
editor=geany

for i in $(find */*.h *.h )  ;do $editor $i ;done
for i in $(find */*.cpp *.cpp )  ;do $editor $i ;done
for i in $(find */*.l *.l )  ;do $editor $i ;done
for i in $(find */*.y *.y )  ;do $editor $i ;done
