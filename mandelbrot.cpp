#include<iostream>
#include"mpreal.h"

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
  * Computing the steps is where things get interesting. It places four
  * strips of pixels, 1/3 into the x-axis, 2/3 into the x-axis, 1/3 into
  * the y-axis, and 2/3 into the y-axis. It computes the pixels along this
  * line and gets the variation (standard deviation squared) of the line.
  * If it's above three, there is something on the screen, and we have not zoomed
  * into a blank screen, or off the set. Once at least one strip has a variation
  * of three, the computation is aborted, the zoom is increased, and the process
  * starts again. This goes until all four strips have a variation under three,
  * in which how many times it was zoomed in was recorded, in this it's called
  * steps. 
  *
  * The goal of this program is to beat the world record for the deepest Mandelbrot
  * zoom by using a program to find a sweet point that allows us to continue
  * to zoom for an unholy amount of time without zooming off the set.
*/


// This function scales a number in one range to another range. It's used to scale a pixel
// on the screen to the Mandelbrot's range
mpfr::mpreal scale(mpfr::mpreal num, mpfr::mpreal old_min, mpfr::mpreal old_max, mpfr::mpreal new_min, mpfr::mpreal new_max) {
	mpfr::mpreal numerator = (new_max-new_min)*(num-old_min);
	mpfr::mpreal denominator = old_max - old_min;
	return (numerator/denominator)+new_min;
}

// This function finds the total variation of a set of numbers.
// It's used to see if computing the Mandelbrot of that area
// has more than one color. If not, we have hit a dead end.
mpfr::mpreal variation(unsigned int data[], unsigned short start, unsigned short stop) {
  mpfr::mpreal initial_mean = 0.0;
  unsigned short size = (stop-start);
  for (unsigned short x = start; x < stop; x++) {
    initial_mean += data[x];
  }

  initial_mean /= size;

  mpfr::mpreal final_mean = 0.0;

  for (unsigned short x = start; x < stop; x++) {
    final_mean += pow((data[x]-initial_mean), 2);
  }

  return final_mean/size;
}

unsigned int mandelbrot_steps(mpfr::mpreal x_center, mpfr::mpreal y_center, unsigned int starting_zoom) {
  unsigned int steps = 0;
  unsigned int zoom = starting_zoom;

  while(true) {
    unsigned int MAX_ITERATIONS = 255;
    int values[1000][2];
    unsigned int results[1000];
    mpfr::mpreal y_scaled = scale(y_center, 0, 360, -1, 1);
    for (unsigned short i = 0; i < 640; i++) {
      mpfr::mpreal x_scaled = scale((((i-320))>>zoom) + x_center, 0, 640, -2.5, 1);
      mpfr::mpreal x;
      mpfr::mpreal y;
      
      x = 0;
      y = 0;

      unsigned int iteration = 0;
      
      while((x*x + y*y) < 4 && iteration < MAX_ITERATIONS) {
        mpfr::mpreal xtemp = x*x - y*y + x_scaled;
        y = 2*x*y + y_scaled;
        x = xtemp;
        iteration++;
      }

      results[i] = iteration;

    }

    if (variation(results, 0, 640) > 3) {
      steps++;
      std::cout << "Continuing after first iteration, steps is " << steps << " and zoom is " << zoom << std::endl;
      zoom++;
      continue;   
    }
    
    mpfr::mpreal x_scaled = scale(x_center, 0, 640, -2.5, 1);
    for (unsigned short i = 640; i < 1000; i++) {
      mpfr::mpreal y_scaled = scale((((i-820)) >> zoom) + y_center, 0, 360, -1, 1);

      mpfr::mpreal x = 0.0;
      mpfr::mpreal y = 0.0;
      
      unsigned int iteration = 0;
      
      while((x*x + y*y) < 4 && iteration < MAX_ITERATIONS) {
        mpfr::mpreal xtemp = x*x - y*y + x_scaled;
        y = 2*x*y + y_scaled;
        x = xtemp;
        iteration++;
      }

      results[i] = iteration;
    }

    if (variation(results, 640, 1000) > 3) {
      steps++;
      std::cout << "Continuing after second iteration, steps is " << steps  << " and zoom is " << zoom << std::endl;
      zoom++;
      continue;  
    }

    break;
  
  }
  return steps;
}

unsigned int mandelbrot_grid(int xi, int yi, mpfr::mpreal x_offset, mpfr::mpreal y_offset, unsigned int zoom) {
  unsigned int MAX_ITERATIONS = 255;

  mpfr::mpreal x = 0;
  mpfr::mpreal y = 0;

  unsigned int iteration = 0;

  mpfr::mpreal x_scaled = scale((((xi+x_offset)-320)) >> zoom, 0, 640, -2.5, 1);
  mpfr::mpreal y_scaled = scale((((yi+y_offset)-180)) >> zoom, 0, 360, -1, 1);

  while((x*x + y*y) < 4 && iteration < MAX_ITERATIONS) {
    mpfr::mpreal xtemp = x*x - y*y + x_scaled;
    y = 2*x*y + y_scaled;
    x = xtemp;
    iteration++;
  }

  return iteration;
}

int main(void) {
  std::cout << mandelbrot_steps(320, 180, 0) << std::endl;
  return 0;
}
