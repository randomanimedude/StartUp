#include "CommonLib.h"

float lerp(float a, float b, float t)
{
	return a+t*(b-a);
}

Color lerp(Color a, Color b, float t)
{
	return Color(lerp(a.r,b.r,t),lerp(a.g,b.g,t),lerp(a.b,b.b,t),lerp(a.a,b.a,t));
}
