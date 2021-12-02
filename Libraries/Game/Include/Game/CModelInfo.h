/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "Base.h"

class CModelInfo
{
public:
	static bool IsBoatModel(int index);
	static bool IsCarModel(int index);
	static bool IsTrainModel(int index);
	static bool IsHeliModel(int index);
	static bool IsPlaneModel(int index);
	static bool IsBikeModel(int index);
	static bool IsFakePlaneModel(int index);
	static bool IsMonsterTruckModel(int index);
	static bool IsQuadBikeModel(int index);
	static bool IsBmxModel(int index);
	static bool IsTrailerModel(int index);
	// return -1 if model is not a vehicle model otherwise returns vehicle model type
	static int IsVehicleModelType(int index);
};