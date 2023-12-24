# BillHub

This is the BillHub project.

## Building and installing

### Linux
You need to install some stuff
```
sudo apt-get install git clang libglfw3-dev libglew-dev
```
You will also need to install [libharu](http://libharu.org/) to generate PDFs, follow instructions [here](https://github.com/libharu/libharu/wiki/Installation).

You might also need to run `sudo ldconfig` to update the cache to find shared libraries.

Finally, run `make` and BillHub executable gets generated in bin directory.

### Windows
This is a one time setup so do it carefully to avoid any errors.
#### Install mingw-w64 
Watch how to install [video](https://www.youtube.com/watch?v=Zcy981HhGw0).
#### Set up glew
1. Download and extract [glew](https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip) release files
2. Open cmd in source directory as administrator and then run the following (ignore any warnings in this step):
	```
	gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude -DGLEW_BUILD -o src/glew.o -c src/glew.c
	gcc -nostdlib -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
	ar cr lib/libglew32.a src/glew.o

	gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
	gcc -nostdlib -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o lib/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
	ar cr lib/libglew32mx.a src/glew.mx.o
	```
	Some files are now generated in lib folder. Copy `.dll` files to `C:\Windows\System32\` folder. Copy `.a` and `.dll.a` files to `C:\mingw64\lib\` folder.
3. Copy `.\include\GL\` directory's all files to `C:\mingw64\x86_64-w64-mingw32\include\GL`

#### Set up glfw
1. Download these files [libglfw3.a](https://github.com/McNopper/OpenGL/blob/master/External/x86/Windows/MinGW/lib/libglfw3.a), [glfw3.h](https://github.com/glfw/glfw/blob/master/include/GLFW/glfw3.h) and [glfw3native.h](https://github.com/glfw/glfw/blob/master/include/GLFW/glfw3native.h). Then copy `libglfw3.a` to `C:\mingw64\lib`. Copy `glfw3.h` and `glfw3native.h` to `C:\mingw64\x86_64-w64-mingw32\include\GLFW` (create `GLFW` directory if it does not exists). Or, alternatively you can compile these files on your own watching this [video](https://www.youtube.com/watch?v=1s8C9dXRXmM) and then copying them to these directories.

#### Set up libharu
Download [libharu](http://libharu.org/) to generate PDFs, follow steps given in glfw video but instead using libharu's source code to install it. Then, copy `.dll` file to `C:\Windows\System32\` folder. Copy `.dll.a` file to `C:\mingw64\lib\` folder and files in `include` folder to `C:\mingw64\x86_64-w64-mingw32\include\`.

Finally, run `mingw32-make` (use powershell or cmd) in BillHub directory and BillHub.exe gets generated in bin directory.

## Licensing

<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
GNU AGPLv3.
-->