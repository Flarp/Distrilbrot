# Distri-Mandelbrot

(DISCLAIMER: This probably will not compile on a 64 bit system)

This repo contains the code for the proof of concept program for Distri, compiled with Emscripten. It computes how many steps a point (x,y) can zoom in to the Mandelbrot set before it zooms into nothingness. It gets the standard deviation of each row and sees if it is over a certain point. If all rows are below a certain number, the set has reached the farthest it can zoom into that point.

For help on how to configure everything, run `./configure --help`

Once configured, you can just run `make`.
