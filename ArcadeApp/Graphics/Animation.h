#pragma once

#include "Vec2D.h"
#include "Color.h"
#include "Utils.h"
#include <string>
#include <vector>

struct AnimationFrame
{
	std::string frame = "";
	std::string overlay = "";
	Color frameColor = Color::White();
	Color overlayColor;
	Vec2D size;
	Vec2D offset = Vec2D::Zero;
	int frameColorSet = 0;
};

struct Animation
{
public:
	Animation();

	std::string animationName;
	std::string spriteSheetName;
	std::string overlay;
	std::vector<std::string> frames;
	std::vector<Color> frameColors;
	std::vector<Color> overlayColors;
	std::vector<Vec2D> frameOffsets;
	Vec2D size;
	int fps;

	AnimationFrame GetAnimationFrame(uint32_t frameNum) const;

	inline void AddFrame(const std::string& frame) { frames.push_back(frame); }
	inline void AddFrameColor(const Color& color) { frameColors.push_back(color); }
	inline void AddOverlayFrameColor(const Color& color) { overlayColors.push_back(color); }
	inline void AddFrameOffset(const Vec2D& offset) { frameOffsets.push_back(offset); }

	size_t NumFrames() const { return frames.size(); }
	size_t NumFrameColors() const { return frameColors.size(); }
	size_t NumOverlayColors() const { return  overlayColors.size(); }
	size_t NumFrameOffsets() const { return frameOffsets.size(); }

	static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);
};