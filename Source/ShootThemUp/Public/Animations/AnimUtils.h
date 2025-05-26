// Shoot Them Up Game. All Rights Reserved.

#pragma once

/**
 * 
 */
class FAnimUtils
{
public:
	/**
	 * Find first anim notify of specified class in animation montage passed by parameter.
	 * @warning Keep in mind that there should be only one anim notify in animation montage.
	 */
	template<typename TNotifyClass>
	static TNotifyClass* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;
		for (FAnimNotifyEvent NotifyEvent : Animation->Notifies)
		{
			TNotifyClass* AnimNotify = Cast<TNotifyClass>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}	
};
