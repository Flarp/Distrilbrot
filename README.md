# Distri-Mandelbrot

(DISCLAIMER: This probably will not compile on a 64 bit system)

This repo contains the code for the proof of concept program for Distri, compiled with Emscripten. It computes how many steps a point (x,y) can zoom in to the Mandelbrot set before it zooms into nothingness. It gets the standard deviation of each row and sees if it is over a certain point. If all rows are below a certain number, the set has reached the farthest it can zoom into that point.

To install all the needed libraries for this program, run

`./mandelbrot-make --install`

(This takes a while, I think somewhere around 10-15 minutes)

After that, you will have all the libraries needed installed, in which you can run

`./mandelbrot-make --compile`

To compile the LLVM bitcode and get a `mandelbrot.js`.
