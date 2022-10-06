# Tic_and_Toe_SDL

### Introduction

A practical simple C++ project to play TIC TAC TOE using SDL.

### How to build:

#### Windows Version: 
- Clone repository.
- Open `.sln` file by Visual Studio.
- Build.

#### Android Version:
- Clone [SDL](https://github.com/libsdl-org/SDL), [SDL_image](https://github.com/libsdl-org/SDL_image), [SDL_ttf](https://github.com/libsdl-org/SDL_ttf).
- Clone repository.
- Copy 3 folders `SDL`, `SDL_image`, `SDL_ttf` to (path to your working copy)\android-project\app\jni\ **or** make link by run CMD as Administrator and run these commands:
    - `mklink /J (path to your working copy)\android-project\app\jni\SDL (path to SDL folder)`.
    - `mklink /J (path to your working copy)\android-project\app\jni\SDL_image (path to SDL_image folder)`.
    - `mklink /J (path to your working copy)\android-project\app\jni\SDL_ttf (path to SDL_ttf folder)`.
- Open `android-project` by Android Studio.
- Build (required NDK ).
