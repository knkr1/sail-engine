# how to run:

```
mkdir build
cd build
cmake -B .
cmake --build .
./program.exe
```

it's an experimental engine that I work on. it's mostly a learning project, you could see some trash code here and there, but I try to keep it clean.

i'm using msys2's mingw, and installed the glm/glfw packages from there, so you'll probably also need to install them from here.

## some fun facts:
- i dont have an asset loader yet, so instead, cmake copies all assets to the build folder
- i cant think any other fun fact right now