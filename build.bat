@echo off
set deps=deps/src/glad/glad.c deps/src/stb/stb_image.cpp
set file=src/file.cpp
set shader=src/shader.cpp
set renderer=src/renderer.cpp
set resource_manager=src/resource_manager.cpp
set game=src/game.cpp
set tile=src/tile.cpp
set state=src/state.cpp
set texture=src/texture.cpp
set flag=src/flag.cpp
set number=src/number.cpp
set files=src/main.cpp %deps% %file% %shader% %renderer% %resource_manager% %game% %tile% %state% %texture% %flag% %number%
set lib=-L deps/lib -lglfw3 -lopengl32 -lgdi32
set include=-I deps/include

g++ -std=c++20 %files% %include% %lib% -mwindows -o minesweeper.exe && minesweeper.exe