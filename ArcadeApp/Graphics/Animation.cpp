#include "Animation.h"

#include <cassert>

#include "FileCommandLoader.h"

Animation::Animation() :
	size(Vec2D::Zero), spriteSheetName(""), animationName(""), fps(0)
{

}

AnimationFrame Animation::GetAnimationFrame(uint32_t frameNum) const
{
	AnimationFrame frame;

	if(frameNum > frames.size())
	{
		return frame;
	}

	frame.frame = frames[frameNum];

	if(frameNum < frameColors.size())
	{
		frame.frameColor = frameColors[frameNum];
		frame.frameColorSet = 1;
	}

	if(overlay.size() > 0)
	{
		frame.overlay = overlay;
	}

	if(frameNum < overlayColors.size())
	{
		frame.overlayColor = overlayColors[frameNum];
	}

	if(frameNum < frameOffsets.size())
	{
		frame.offset = frameOffsets[frameNum];
	}

	frame.size = size;
}

std::vector<Animation> Animation::LoadAnimations(const std::string& animationFilePath)
{
	std::vector<Animation> animations;

	FileCommandLoader fileLoader;

	Command animationCommand;
	animationCommand.command = "animation";
	animationCommand.parseFunc = [&](ParseFuncParams params)
		{
			Animation newAnimation;
			newAnimation.animationName = FileCommandLoader::ReadString(params);
			animations.push_back(newAnimation);
		};

	fileLoader.AddCommand(animationCommand);

	Command spriteSheetCommand;
	spriteSheetCommand.command = "sprite_sheet";
	spriteSheetCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().spriteSheetName = FileCommandLoader::ReadString(params);
		};

	fileLoader.AddCommand(spriteSheetCommand);


	Command sizeCommand;
	sizeCommand.command = "size";
	sizeCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().size = FileCommandLoader::ReadSize(params);
		};

	fileLoader.AddCommand(sizeCommand);

	Command fpsCommand;
	fpsCommand.command = "fps";
	fpsCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().fps = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(fpsCommand);

	Command framesCommand;
	framesCommand.command = "frame_keys";
	framesCommand.commandType = COMMAND_MULTI_LINE;
	framesCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().AddFrame(params.line);
		};

	fileLoader.AddCommand(framesCommand);

	Command overlayCommand;
	overlayCommand.command = "overlay";
	overlayCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().overlay = FileCommandLoader::ReadString(params);
		};

	fileLoader.AddCommand(overlayCommand);

	Command frameColorsCommand;
	frameColorsCommand.command = "frame_colors";
	frameColorsCommand.commandType = COMMAND_MULTI_LINE;
	frameColorsCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().AddFrameColor(FileCommandLoader::ReadColor(params));
		};

	fileLoader.AddCommand(frameColorsCommand);


	Command overlayFrameColorCommand;
	overlayFrameColorCommand.command = "overlay_colors";
	overlayFrameColorCommand.commandType = COMMAND_MULTI_LINE;
	overlayFrameColorCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().AddOverlayFrameColor(FileCommandLoader::ReadColor(params));
		};

	fileLoader.AddCommand(overlayFrameColorCommand);

	Command frameOffsetsCommand;
	frameOffsetsCommand.command = "frame_offsets";
	frameOffsetsCommand.commandType = COMMAND_MULTI_LINE;
	frameOffsetsCommand.parseFunc = [&](ParseFuncParams params)
		{
			animations.back().AddFrameOffset(FileCommandLoader::ReadSize(params));
		};

	fileLoader.AddCommand(frameOffsetsCommand);

	assert(fileLoader.LoadFile(animationFilePath));

	return animations;
}

