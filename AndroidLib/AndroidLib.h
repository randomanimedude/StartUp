#pragma once

#include "../NativeLib/NativeLib.cpp"

class AndroidLib
{
public:
	const char * getPlatformABI();
	AndroidLib();
	~AndroidLib();
};

