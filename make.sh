#!/bin/bash

g++ $CFLAGS -I/usr/include/python3.8 main.cpp -lpython3.8 -lboost_python3 -lpthread -lm -lutil -ldl
