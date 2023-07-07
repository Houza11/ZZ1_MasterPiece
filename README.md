# zz1_masterpiece

This project use SDL2 and SDL_image only.

In order to compile it, add a `bin` folder at the root with the `.dll` files (`SDL2.dll`, `SDL2_image.dll`)
Also add the `.a`, `.la` and `.dll` to `lib`

SDL : https://github.com/libsdl-org/SDL/releases/tag/release-2.28.0
SDL image : https://github.com/libsdl-org/SDL_image/releases

Make sure you choose the `devel` version

![image](https://github.com/Thomas-Mewily/zz1_sprite/assets/40406187/f46707bf-7fe6-4a50-ae56-72fa59ff2792)
![image](https://github.com/Thomas-Mewily/zz1_sprite/assets/40406187/e623163d-3302-4a66-927c-426f0a45040f)

Gcc compilation command :

Linux
```bash
gcc -O4 -fdiagnostics-color=always -g ./src/*.c ./src/betterC/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/ordi/*.c ./src/game/*.c -Wall -Wextra -Iinclude -Llib -lSDL2main -lSDL2 -lSDL2_image -lm -o ./bin/main.exe
```

Windows
```bash
gcc -O4 -fdiagnostics-color=always -g ./src/*.c ./src/betterC/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/ordi/*.c ./src/game/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
```

Launch the game from the `zz1_masterpiece` folder (otherwise the game will not be able to load the asset), or copy the folders `asset` (and `save`) inside the `bin` folder
```bash
./bin/main.exe
```

![eviter pattern compliquer_2](https://github.com/Thomas-Mewily/zz1_masterpiece/assets/40406187/6564b68b-eaf5-4580-8e07-01308de9a971)
