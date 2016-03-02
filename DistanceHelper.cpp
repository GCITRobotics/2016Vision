#include "stdafx.hpp"
#include "magic.hpp"

static double approxUDistance(double pixelWidth) {
	double previous = (CAMERA_FOCAL * U_WIDTH) / pixelWidth;
	return previous * 1.07;
}
