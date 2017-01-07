#include<iostream>
#include<mpreal.h>
#include<cmath>
#include<string>

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

using namespace mpfr;

mpreal scale(mpreal num, mpreal old_min, mpreal old_max, mpreal new_min, mpreal new_max) {
	mpreal numerator = (new_max-new_min)*(num-old_min);
	mpreal denominator = old_max - old_min;
	return (numerator/denominator)+new_min;
}

mpreal variation(mpreal data[], short size) {
	mpreal initial_mean = 0.0;
	for (short x = 0; x < size; x++) {
		initial_mean += data[x];
	}

	initial_mean /= size;


	mpreal final_mean = 0.0;

	for (short x = 0; x < size; x++) {
		final_mean += pow((data[x]-initial_mean), 2);
	}
  



	return final_mean/size;
	
} 

mpreal variation(int data[], short size) {
  mpreal initial_mean = 0.0;
  for (short x = 0; x < size; x++) {
    initial_mean += data[x];
    values[i]
  }

  initial_mean /= size;

  mpreal final_mean = 0.0;

  for (short x = 0; x < size; x++) {
    final_mean += pow((data[x]-initial_mean), 2);
  }

  return final_mean/size;
}

int mandelbrot_steps(mpreal x_center, mpreal y_center, mpreal starting_zoom) {
  int steps = 0;
  mpreal zoom = starting_zoom;

  int values[2000][2];

  for (int i = 0; i < 640; i++) {
    values[i][0] = i;
    values[i][1] = 120;
  }

  for (int i = 640; i < 1280; i++) {
    values[i][0] = i-640;
    values[i][1] = 240;
  }


}

/*

mpreal mandelbrot_steps(mpreal x_center, mpreal y_center, mpreal starting_zoom) {
	int steps = 0;
	
	mpreal zoom = starting_zoom;
	
	
	while(true) {

		bool exit = true;
    for (char itr = 0; itr < 4; itr++) {
    short x_itr, y_itr;
    
      mpreal x, y, x_scaled, y_scaled;    

      x_scaled = scale(((xi-320)+(x_center*zoom))/zoom, 0, 640, -2.5, 1);
      y_scaled = scale(((yi-180)+(y_center*zoom))/zoom, 0, 360, -1, 1);

      x = 0.0;
      y = 0.0;
      
      int iteration = 0;
      
      while((x*x + y*y) < 4 && iteration < 255) {
        mpreal xtemp = x*x - y*y + x_scaled;
        y = 2*x*y + y_scaled;
        x = xtemp;
        iteration++;
      }

      if (variation(results, 360) > 3) {
        exit = false;
        break;
      }
    } 

			

			
		}
		steps++;
		zoom = pow(2, steps);
		if (exit == true) {
			break;
		}

		
	}
	return steps;
}

*/

int main(void) {
  std::cout << mandelbrot_steps(320, 180, 1) << std::endl;
  return 0;
}
