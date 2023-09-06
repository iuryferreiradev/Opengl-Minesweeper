@echo off
set deps=deps/src/glad/glad.c
set files=src/main.cpp %deps%
set lib=-L deps/lib -lglfw3 -lopengl32 -lgdi32
set include=-I deps/include

g++ -std=c++20 %files% %include% %lib% -o minesweeper.exe && minesweeper.exe