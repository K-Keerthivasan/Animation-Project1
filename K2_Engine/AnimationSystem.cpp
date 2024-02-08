#include "AnimationSystem.h"
#include <glm/gtx/easing.hpp>
AnimationSystem::AnimationSystem()
{
}

AnimationSystem::~AnimationSystem()
{
}


//Function to update the animation
void AnimationSystem::Update(float dt)
{
	for (Animation* anim : m_animations)
	{
		if (m_isPaused)
		{
			continue;
		}

		// Update the animation
		anim->time = dt;
		double time = anim->time * animationSpeed;
		//time += dt;

		cMesh* affectedMesh = anim->mesh;

#pragma region POSITION
		// Position
		if (anim->positionKeyFrames.size() == 1)
		{
			affectedMesh->drawPosition = anim->positionKeyFrames[0].position;
		}
		else
		{
			// Find our position keyframes (Start and End)
			int KeyFrameEndIndex = 0;
			for (; KeyFrameEndIndex < anim->positionKeyFrames.size(); KeyFrameEndIndex++)
			{
				if (anim->positionKeyFrames[KeyFrameEndIndex].time > time)
				{
					break;
				}
			}

			if (KeyFrameEndIndex >= anim->positionKeyFrames.size())
			{
				// we are at or past the last key frame use the last keyframe only
				affectedMesh->drawPosition = anim->positionKeyFrames[KeyFrameEndIndex - 1].position;
				return;
			}
			int KeyFrameStartIndex = KeyFrameEndIndex - 1;


			PositionKeyFrame startKeyFrame = anim->positionKeyFrames[KeyFrameStartIndex];
			PositionKeyFrame endKeyFrame = anim->positionKeyFrames[KeyFrameEndIndex];

			float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
			float result = 0.f;

			if (percent >= 0.99f)
			{
				//percent = 1.0f;
				bool breakpoint = true;
			}

			switch (endKeyFrame.easingType)
			{
				case EasingType::Linear:
					result = percent;
					break;

				case EasingType::SineEaseIn:
					result = glm::sineEaseIn(percent);
					break;

				case EasingType::SineEaseOut:
					result = glm::sineEaseOut(percent);
					break;

				case EasingType::SineEaseInOut:
					result = glm::sineEaseInOut(percent);
					break;
			}

			glm::vec3 delta = endKeyFrame.position - startKeyFrame.position;
			affectedMesh->drawPosition = startKeyFrame.position + delta * result;
		}
#pragma endregion

#pragma region ROTATION
		// Rotation
		if (anim->rotationKeyFrames.size() == 1)
		{
			affectedMesh->setRotationFromEuler(anim->rotationKeyFrames[0].rotation);
		}
		else
		{
			// Find our position keyframes (Start and End)
			int KeyFrameEndIndex = 0;
			for (; KeyFrameEndIndex < anim->rotationKeyFrames.size(); KeyFrameEndIndex++)
			{
				if (anim->rotationKeyFrames[KeyFrameEndIndex].time > time)
				{
					break;
				}
			}

			if (KeyFrameEndIndex >= anim->rotationKeyFrames.size())
			{
				// we are at or past the last key frame use the last keyframe only
				affectedMesh->setRotationFromEuler(anim->rotationKeyFrames[KeyFrameEndIndex - 1].rotation);
				return;
			}
			int KeyFrameStartIndex = KeyFrameEndIndex - 1;

			RotationKeyFrame startKeyFrame = anim->rotationKeyFrames[KeyFrameStartIndex];
			RotationKeyFrame endKeyFrame = anim->rotationKeyFrames[KeyFrameEndIndex];

			float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
			float result = 0.f;

			switch (endKeyFrame.easingType)
			{
				case EasingType::Linear:
					result = percent;
					anim->mesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);
					break;
				case EasingType::SineEaseIn:
					result = glm::sineEaseIn(percent);
					anim->mesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case EasingType::SineEaseOut:
					result = glm::sineEaseOut(percent);
					//yellow
					anim->mesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
					break;
				case EasingType::SineEaseInOut:
					result = glm::sineEaseInOut(percent);
					//green
					anim->mesh->wholeObjectDebugColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
					break;
			}

			glm::vec3 delta = endKeyFrame.rotation - startKeyFrame.rotation;
			glm::quat startQuat = glm::quat(startKeyFrame.rotation);
			glm::quat endQuat = glm::quat(endKeyFrame.rotation);
			glm::quat offset = glm::slerp(startQuat, endQuat, result);
			glm::vec3 euler = glm::eulerAngles(offset);
			affectedMesh->setRotationFromEuler(euler);
		}
		#pragma endregion

#pragma region SCALE
		if (anim->scaleKeyFrames.size() == 1)
		{
			affectedMesh->setUniformDrawScale(anim->scaleKeyFrames[0].scale.x);
		}
		else
		{
			// Find our position keyframes (Start and End)
			int KeyFrameEndIndex = 0;
			for (; KeyFrameEndIndex < anim->scaleKeyFrames.size(); KeyFrameEndIndex++)
			{
				if (anim->scaleKeyFrames[KeyFrameEndIndex].time > time)
				{
					break;
				}
			}

			if (KeyFrameEndIndex >= anim->scaleKeyFrames.size())
			{
				// we are at or past the last key frame use the last keyframe only
				affectedMesh->setUniformDrawScale(anim->scaleKeyFrames[KeyFrameEndIndex - 1].scale.x);
				return;
			}
			int KeyFrameStartIndex = KeyFrameEndIndex - 1;

			ScaleKeyFrame startKeyFrame = anim->scaleKeyFrames[KeyFrameStartIndex];
			ScaleKeyFrame endKeyFrame = anim->scaleKeyFrames[KeyFrameEndIndex];

			float percent = (time - startKeyFrame.time) / (endKeyFrame.time - startKeyFrame.time);
			float result = 0.f;

			switch (endKeyFrame.easingType)
			{
				case EasingType::Linear:
					result = percent;
					break;
				case EasingType::SineEaseIn:
					result = glm::sineEaseIn(percent);
					break;
				case EasingType::SineEaseOut:
					result = glm::sineEaseOut(percent);
					break;
				case EasingType::SineEaseInOut:
					result = glm::sineEaseInOut(percent);
					break;
			}

			glm::vec3 delta = endKeyFrame.scale - startKeyFrame.scale;
			affectedMesh->setUniformDrawScale(startKeyFrame.scale.x + delta.x * result);
		}
		#pragma endregion

	}
}

void AnimationSystem::AddAnimation(Animation* anim)
{
	m_animations.push_back(anim);
}

void AnimationSystem::Pause()
{
	m_isPaused = true;
}

void AnimationSystem::Resume()
{
	m_isPaused = false;
}
