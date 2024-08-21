#!/bin/bash
clear
echo "------------ Make File ------------"
make all
echo "-----------------------------------"
./a.out < inputs/$1.txt