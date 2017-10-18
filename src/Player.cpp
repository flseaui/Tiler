#include "Player.h"

extern double deltaTime;

Player::Player(Window * window, Camera* camera) : TexRect(camera, "res/textures/clatab.png", 32, 32, 0, 16, 16)
{
	this->window = window;
	gravity = 25.0f;
	hitbox = new AABB(position.x, position.y, 16, 16);
}

void Player::update() {
	bool direction = false;
	if (window->isKeyPressed(GLFW_KEY_D) && !window->isKeyPressed(GLFW_KEY_A)) {
		if (grounded)
			velocity.x = SPEED;
		else if (velocity.x < SPEED) {
			velocity.x += SPEED * 0.1;
			if (velocity.x > SPEED)
				velocity.x = SPEED;
		}
		direction = true;
	}
	if (window->isKeyPressed(GLFW_KEY_A) && !window->isKeyPressed(GLFW_KEY_D)) {
		if (grounded)
			velocity.x = -SPEED;
		else if (velocity.x > -SPEED) {
			velocity.x -= SPEED * 0.1;
			if (velocity.x < -SPEED)
				velocity.x = -SPEED;
		}
		direction = true;
	}
	if (!direction && grounded)
		velocity.x = 0;
	if (window->isKeyPressed(GLFW_KEY_SPACE)) {
		if (grounded) {
			jump = true;
			velocity.y = -256;
			grounded = false;
			space = 1;
		}
		else if (space > 0 && space < SPACE_HELD && jump)
			velocity.y -= gravity * (SPACE_HELD - space + 1) / SPACE_HELD;
		++space;
	}
	else {
		space = 0;
		jump = false;
	}
	velocity.y += gravity;
	position += (velocity * (float)deltaTime);
	hitbox->setPosition(position);
	grounded = false;
}

AABB * Player::getHitbox() {
	return hitbox;
}

glm::vec3 Player::getVelocity() {
	return velocity;
}

void Player::alignHitbox() {
	hitbox->setPosition(position);
}

void Player::hitBottom() {
	velocity.y = 0;
	grounded = true;
}

void Player::hitLeft() {
	velocity.x = 0;
	//if (velocity.y > WALL_SLIDE)
	//	velocity.y = WALL_SLIDE;
	//if (!grounded && space == 1) {
		//jump = true;
		//velocity.x = 100;
		//velocity.y = -140;
	//}
}

void Player::hitRight() {
	velocity.x = 0;
	//if (velocity.y > WALL_SLIDE)
	//	velocity.y = WALL_SLIDE;
	//if (!grounded && space == 1) {
	//	jump = true;
	//	velocity.x = -100;
	//	velocity.y = -140;
//	}
}

void Player::hitTop() {
	velocity.y = 0;
}

void Player::setGravity(float gravity) {
	this->gravity = gravity;
}

Player::~Player() {
	delete hitbox;
}