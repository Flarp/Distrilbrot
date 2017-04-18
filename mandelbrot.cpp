#ifdef DEBUG
#include<ostream>
#endif

#include"mpreal.h"
#include<string>
#include<emscripten.h>
#include"constants.h"
/*
  * Distrilbrot - Distributed Mandelbrot set computing program
  * (If you don't know what the Mandelbrot set is, look it up, or 
  * this won't really make sense)
  *
  * Written in C++, compiled to asm.js and wasm using Emscripten and Binaryen.
  * It has two modes, computing steps and computing sets.
  * Computing Mandelbrot sets works the way you expect it, it
  * zooms into the set, computing every pixel. This is obviously
  * CPU intensive so it is heavily distributed across the current
  * users online to make sure no one gets too much work.
  *
  * The program works by zooming into areas and finding patches with the
  * the greatest standard deviation. The higher the standard deviation,
  * the more colorful everything is, and that's what makes the Mandelbrot
  * so cool. 
  *
  * A problem with the set is that the higher the max iteration count is, does
  * not get a more colorful picture. A low one doesn't get one either. There is
  * a sweet spot for every zoom, so this program also includes a regression function
  * that helps find that sweet spot.
  *
  *
  * The goal of this program is to beat the world record for the deepest Mandelbrot
  * zoom by using a program to find a sweet point that allows us to continue
  * to zoom for an unholy amount of time without zooming off the set.
*/


unsigned int mandelbrot(mpfr::mpreal x_init, mpfr::mpreal y_init, unsigned int max_iterations) {
  mpfr::mpreal x = 0.0;
  mpfr::mpreal y = 0.0;

  unsigned int iterations = 0;
  
  while((x*x + y*y) < 4 && iterations < max_iterations) {
    mpfr::mpreal xtemp = x*x - y*y + x_init;
    y = 2*x*y + y_init;
    x = xtemp;
    iterations++;
  }

  return iterations;

}

unsigned int max_iterations(unsigned int zoom) {
  return 255;
}

unsigned int* mandelbrot_array(mpfr::mpreal x_center, mpfr::mpreal y_center, unsigned int zoom, unsigned int MAX_ITERATIONS) {
  mpfr::mpreal one = 1; 
  one = one >> zoom; // mpfr::mpreal overloads the operator >> to be x / 2^y (in the form of x >> y)

  unsigned int *results = new unsigned int[SIZE];
  for (short x = -(FRAME_WIDTH/2); x < (FRAME_WIDTH/2); x++) {
    std::cout << y_center << x_center+((one/HALF_WIDTH)*x) << std::endl;
    results[x+(FRAME_WIDTH/2)] = mandelbrot(y_center, x_center+((one/HALF_WIDTH)*x), MAX_ITERATIONS);
  }
  for (short y = -(FRAME_HEIGHT/2); y < (FRAME_HEIGHT/2); y++) {
    std::cout << y_center+((one/HALF_HEIGHT)*y) << x_center << std::endl;
    results[y+((FRAME_WIDTH+(FRAME_HEIGHT/2))-1)] = mandelbrot(y_center+((one/HALF_HEIGHT)*y), x_center, MAX_ITERATIONS);
  }
  return results;
}

mpfr::mpreal mandelbrot_variation(unsigned int values[]) {
  mpfr::mpreal initial_mean_y, initial_mean_x;

  for (short x = 0; x < FRAME_WIDTH; x++) {
    initial_mean_x += values[x];
  }

  for (short y = FRAME_WIDTH; y < SIZE; y++) {
    initial_mean_y += values[y];
  }

  initial_mean_y /= FRAME_HEIGHT;
  initial_mean_x /= FRAME_WIDTH;

  mpfr::mpreal final_mean_x, final_mean_y;

  for (short x = 0; x < FRAME_WIDTH; x++) {
    final_mean_x += pow(values[x] - initial_mean_x, 2);
  }

  for (short y = FRAME_WIDTH; y < SIZE; y++) {
    final_mean_y += pow(values[y]- initial_mean_y, 2);
  }
  
  final_mean_x /= FRAME_WIDTH;
  final_mean_y /= FRAME_HEIGHT;

  return (final_mean_x+final_mean_y)/2;
}

int main() {
  unsigned int *gronk = mandelbrot_array(-0.25, 0.1, 0, 255);
  for (unsigned int x = 0; x < SIZE; x++) {
    std::cout << gronk[x] << std::endl;
  }
  return 0;

}



