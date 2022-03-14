#ifndef ANIMATIONCOMPONENT_H_INCLUDED
#define ANIMATIONCOMPONENT_H_INCLUDED

#include <iostream>
#include "SFML\Graphics.hpp"
#include <map>

/** AnimationComponent class */
class AnimationComponent
{
private:
	/** Animation class */
	class Animation
	{
	private:

		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

	public:
		/*constructor for Animation*/
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), height(height)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x *width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		void play(const float& dt)
		{
			this->timer += 35.f * dt;
			if (this->timer >= this->animationTimer)
			{
				this->timer = 0.f;

				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
		}

		void reset()
		{
			this->timer = 0.f;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;

public:

		/*constructor for AnimationComponent*/
		AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);

		/*destructor for AnimationComponent*/
		virtual ~AnimationComponent();

		/** The function creates new animation with a specific key
		@param key animation key
		@param animation_timer timer for an animation
		@param start_frame_x position x of frame from which we start
		@param start_frame_y position y of frame from which we start
		@param frames_x number of frames to pass
		@param frames_y number of frames to pass
		@param width width of an frame
		@param height height of an frame
		*/
		void addAnimation(const std::string key,float animation_timer, int start_frame_x, int start_frame_y,
			int frames_x, int frames_y, int width, int height);

		/** The function plays the animation from the beggining
		@param key animation key
		@param dt reference to the delta time
		*/
		void play(const std::string key, const float & dt);



};

#endif