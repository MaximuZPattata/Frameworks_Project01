#include "pch.h"
#include "cFrameRates.h"

void cFrameRates::UpdateFrameRates(std::vector < sAnimationFrames* >& animationFrames)
{
	for (int frameIndex = 0; frameIndex < animationFrames.size(); frameIndex++)
	{
		if (animationFrames[frameIndex]->isActivated)
			animationFrames[frameIndex]->FrameRateValue++;
	}
}
