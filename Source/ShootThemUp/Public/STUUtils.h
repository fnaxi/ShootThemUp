// Shoot Them Up Game. All Rights Reserved.

#pragma once

/**
 * 
 */
class FSTUUtils
{
public:
	/** Get a component */
	template<class TType>
	static TType* GetSTUPlayerComponent(APawn* PlayerPawn)
	{
		if (PlayerPawn)
		{
			return Cast<TType>(PlayerPawn->GetComponentByClass(TType::StaticClass()));
		}
		return nullptr;
	}
};
