#include<iostream>
#include<mpreal.h>
#include<cmath>

using namespace mpfr;


mpreal scale(mpreal num, mpreal old_min, mpreal old_max, mpreal new_min, mpreal new_max) {
	mpreal numerator = (new_max-new_min)*(num-old_min);
	mpreal denominator = old_max - old_min;
	return (numerator/denominator)+new_min;
}

mpreal standard_deviation(mpreal data[], mpreal size) {
	mpreal initial_mean;
	for (short x = 0; x < size; x++) {
		initial_mean += data[x];
	}

	initial_mean = initial_mean/size;


	mpreal final_mean = 0.0;

	for (short x = 0; x < size; x++) {
		final_mean += pow(data[x]-initial_mean, 2);
	}



	return final_mean/size;
	
}

mpreal mandelbrot_steps(mpreal x_center, mpreal y_center, mpreal starting_zoom) {
	int steps = 0;
	
	mpreal zoom = starting_zoom;
	
	
	while(true) {
		mpreal standard_deviations[1280];

		bool exit = true;

		for(short xi = 0; xi < 1280; xi++) {
			mpreal results[720];
			for (short yi = 0; yi < 720; yi++) {
				mpreal x, y, x_scaled, y_scaled;

				x_scaled = scale(((xi-640)+(x_center*zoom))/zoom, 0, 1280, -2.5, 1);
				y_scaled = scale(((yi-360)+(y_center*zoom))/zoom, 0, 720, -1, 1);

				x = 0.0;
				y = 0.0;
				
				int iteration = 0;
				
				while((x*x) + (y*y) < 4 && iteration < 255) {
					mpreal xtemp = (x*x) + (y*y) - x_scaled;
					y = 2*x*y + y_scaled;
					x = xtemp;
					iteration++;
				}
				results[yi] = iteration;
			}
			standard_deviations[xi] = standard_deviation(results, 720);

			std::cout << "Just finished row " << xi << " that had a standard deviation of " << standard_deviations[xi] << std::endl;
			if (standard_deviations[xi] > 3) {
				exit = false;
				break;
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

int main(void) {
	std::cout << mandelbrot_steps(640,360,1) << std::endl;
	return 0;
}
