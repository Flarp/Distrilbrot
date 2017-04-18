#include<ostream>
#include"mpreal.h"
#include"constants.h"

struct mandelbrot_intermediate {
  mpfr::mpreal x, y, initial_x, initial_y;
  unsigned char skip;
  unsigned int iteration_counts;
};

mandelbrot_intermediate single_mandelbrot(mandelbrot_intermediate init) {
  if (((init.x*init.x) + (init.y*init.y)) > 4) {
    init.skip = 1;
    return init;
  }


  mpfr::mpreal xtemp = init.x*init.x - init.y*init.y + init.initial_x;

  init.y = 2*init.x*init.y + init.initial_y;

  init.x = xtemp;
  init.iteration_counts++;
  return init;

}

mpfr::mpreal coef(mandelbrot_intermediate screen[SIZE]) {
  unsigned int initial_total = 0;
  for (unsigned short x = 0; x < SIZE; x++) {
    initial_total += screen[x].iteration_counts;
  }

  mpfr::mpreal initial_mean = initial_total / SIZE;
  mpfr::mpreal final_mean = 0;

  for (unsigned short x = 0; x < SIZE; x++) {
    final_mean += pow(screen[x].iteration_counts - initial_mean, 2);
  }

  return sqrt(final_mean/SIZE)/initial_mean;
  
}

void mandelbrot_iteration_getter(mpfr::mpreal x_center, mpfr::mpreal y_center) {
  unsigned int zoom = 0;
  unsigned int iteration_count = 0;
  while (true) {
    mandelbrot_intermediate grid[SIZE];
    for (short x_itr = -HALF_WIDTH; x_itr < HALF_WIDTH; x_itr++) {
      short x = x_itr + HALF_WIDTH;

      grid[x].initial_x = x_center + (((mpfr::mpreal(x_itr)/HALF_WIDTH)*1.75)>>zoom);
      grid[x].initial_y = y_center;
      grid[x].y = 0;
      grid[x].x = 0;
      grid[x].skip = 0;
      grid[x].iteration_counts = 0;

    }

    for (short y = -HALF_HEIGHT; y < HALF_HEIGHT; y++) {
      short y_wd = y+FRAME_WIDTH+HALF_HEIGHT;
      
      grid[y_wd].initial_x = x_center;
      grid[y_wd].initial_y = y_center + ((mpfr::mpreal(y)/HALF_HEIGHT)>>zoom);
      grid[y_wd].y = 0;
      grid[y_wd].x = 0;
      grid[y_wd].skip = 0;
      grid[y_wd].iteration_counts = 0;
    }
    mpfr::mpreal current_variation = 0;
    mpfr::mpreal initial_variation = -1;
    do {
      initial_variation = current_variation;
      
      unsigned int total_skipped = 0; 
      for (unsigned short x = 0; x < SIZE; x++) {
        if (grid[x].skip == 1) {
          total_skipped++;
          continue;
        }
        grid[x] = single_mandelbrot(grid[x]);
      }

      if (total_skipped == SIZE) {
        break;
      }

      current_variation = coef(grid);
      std::cout << current_variation << std::endl;
      iteration_count++;
    } while (iteration_count % 255 != 0);
    zoom++;
    std::cout << "Iteration Count: " << iteration_count << " | Final Variation: " << initial_variation << " | Zoom:  " << zoom;
    std::cout << " | Failing Variation: " << current_variation << std::endl;
  }

  
}

int main() {
  mandelbrot_iteration_getter(-0.25, 0.1);
  return 0;
}


