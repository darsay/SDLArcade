#pragma once

#include "Animation.h"
#include <vector>
#include <string>

class AnimationPlayer
{
public:
	AnimationPlayer();
	bool Init(const std::string& animationPath);
	bool Play(const std::string& animationName, bool looped);
	void Pause();
	void Stop();
	void Update(uint32_t dt);
	AnimationFrame GetCurrentAnimationFrame() const;

	inline uint32_t GetCurrentFrameNumber() const { return mFrame; }
	inline bool IsFinishedPlaying() const { return mIsFinishedPlaying; }
private:
	uint32_t mTime;
	std::vector<Animation> mAnimations;
	size_t mCurrentAnimation;
	uint32_t mFrame;

	bool mLooped;
	bool mIsPlaying;
	bool mIsFinishedPlaying;
};

