# Force Of Nature

### Pre-Reqs

This package requires the use of SDL3, SDL3_Image, and SDL3_TTF which can be found here:

SDL3 -> https://github.com/libsdl-org/SDL

SDL3_TTF -> https://github.com/libsdl-org/SDL_ttf

SDL3_Image -> https://github.com/libsdl-org/SDL_image

### Building the Project

First we need to clone the project:

```bash
cd <destination directory>
git clone --recursive git@github.com:AndreMellis/forceOfNature.git
cd forceOfNature

```

Now that we have cloned the project we can build it. Please note that CMake will handle all copying of assets, so do not manually copy anything
```bash
mkdir build
cmake ..
make
```

Now we can run the game's executable directory
```bash
./forceOfNature.out
```