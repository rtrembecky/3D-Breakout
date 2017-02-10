#include "Colors.h"

const float* randColor() {
	 switch (rand() % 20) {
	 case 0:
		 return black;
	 case 1:
		 return red;
	 case 2:
		 return red2;
	 case 3:
		 return red3;
	 case 4:
		 return green;
	 case 5:
		 return green2;
	 case 6:
		 return green3;
	 case 7:
		 return blue;
	 case 8:
		 return blue2;
	 case 9:
		 return blue3;
	 case 10:
		 return yellow;
	 case 11:
		 return yellow2;
	 case 12:
		 return yellow3;
	 case 13:
		 return orange;
	 case 14:
		 return white;
	 case 15:
		 return brown;
	 case 16:
		 return gray;
	 case 17:
		 return gray2;
	 case 18:
		 return gray3;
	 case 19:
		 return maroon5;
	 default:
		 return black;
	 }
}

const float* colorScheme(const int color_scheme, const bool even) {
	switch (color_scheme) {
	case 1:
		return even ? green2 : blue2;
	case 2:
		return even ? maroon5 : yellow2;
	}
	return white;
}