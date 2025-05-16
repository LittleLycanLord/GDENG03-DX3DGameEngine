

#pragma once
#include<Core/MyLogger.h>

namespace DX3D {
#define DX3DGraphicsLogThrowOnFail(hr,message)\
	{\
	auto res = (hr);\
	if (FAILED(res))\
		DX3DLogErrorAndThrow(message);\
	}
}