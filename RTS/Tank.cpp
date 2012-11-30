/////////////////////////////////
//Tank.cpp Tank Class Method File
/////////////////////////////////

#include "Tank.h"

void Tank::start(sf::Vector2f input_position, int team)
{
	//SUPER TEMP: REMOVE ME//
	//image loading function
	//turret image: 40x40 px
	//body image: 48x48 px
	tex_turret.loadFromFile("tank_turret.png");
	tex_body.loadFromFile("tank_body.png");

	spt_turret.setTexture(tex_turret);
	spt_turret.setOrigin(20, 20);
	spt_body.setTexture(tex_body);
	spt_body.setOrigin(24, 24);

	//set stats(position, health)

	team_num = team;
	position.x = input_position.x;
	position.y = input_position.y;
	velocity.x = 0;
	velocity.y = 0;
	speed_max = 15;
	speed_curr = 0;
	speed_acceleration = 3;
	stat_HPmax = 50;
	stat_HPcurr = stat_HPmax;
	stat_attack = 10;
	stat_armour = 5;
	stat_LOS = 6;
	isActive = true;
	isSelected = false;
	
	//temp
	destination.x = 5;
	destination.y = 5;
}

void Tank::update(sf::Time frame_time, std::vector<BaseEntity*> entityList, int** map, sf::Vector2f destinationVector, BaseEntity* targetEntity)
{
	//check for updates (upgrades, buffs,etc)
	
	//movement
	setDestination(destinationVector);
	//get relative heading to dest
	float loc_des_length = sqrt(pow((destination.x - position.x), 2) + pow((destination.y - position.y), 2));

	//movement
	if (loc_des_length >= 0.5)
	{
		sf::Vector2f heading_vector;
		heading_vector.x = (destination.x - position.x)/loc_des_length;
		heading_vector.y = (destination.y - position.y)/loc_des_length;

		float angle;
		angle = atan2(heading_vector.y, heading_vector.x);
		body_facing = returnHeadingSection(angle);
	
		//update volocity and position
		if ((speed_curr < speed_max) && loc_des_length > (speed_curr*speed_curr)/(2*speed_acceleration))
			speed_curr += speed_acceleration;
		else
			speed_curr -= speed_acceleration;

		if (speed_curr >= speed_max)
			speed_curr = speed_max;

		if (speed_curr <= 0.5)
			speed_curr = 0;

		position.x += frame_time.asSeconds()*heading_vector.x*speed_curr;
		position.y += frame_time.asSeconds()*heading_vector.y*speed_curr;
	}

	//check target
	
	sf::Vector2f targetPos = targetEntity->returnPosition();

	float loc_tgt_length = sqrt(pow((targetPos.x - position.x), 2) + pow((targetPos.y - position.y), 2));
	
	if (loc_tgt_length <= stat_LOS)
	{
		sf::Vector2f target_heading;
		target_heading.x = (targetPos.x - position.x)/loc_tgt_length;
		target_heading.y = (targetPos.y - position.y)/loc_tgt_length;

		float targetAngle;
		targetAngle = atan2(target_heading.x, target_heading.y);
		turret_facing = returnHeadingSection(targetAngle);
	}
	else
		turret_facing = body_facing;

	//attack if possible
}

void Tank::draw(sf::RenderWindow& renderwindow)
{
	
	//draw image
	body_facing = (body_facing % 8);
	turret_facing = (turret_facing % 8);

	//body
	sf::Rect<int> subrect_body((body_facing * 48), (team_num * 48), 48, 48); 
	//sprite dimensions, try to replace this with a function
	int spriteWidth = 100;
	int spriteHeight = 64;
	float XPos = (spriteWidth/2)*(position.x - position.y) - 16;
	float YPos = (spriteHeight/2)*(position.y + position.x) - 32;
	sf::Vector2f position_final(XPos, YPos);

	spt_body.setPosition(position_final);
	spt_body.setTextureRect(subrect_body);
	renderwindow.draw(spt_body);
	
	//turret
	sf::Rect<int> subrect_turret((turret_facing * 40), (team_num * 40), 40, 40); //these are wrong, different dimensions
	spt_turret.setPosition(position_final.x, position_final.y-12);
	spt_turret.setTextureRect(subrect_turret);
	renderwindow.draw(spt_turret);
}

void Tank::destroy()
{
	//delete object
}

void Tank::setDestination(sf::Vector2f destinationIN)
{
	//used by player to set tank's destination
	if (destinationIN != sf::Vector2f(-1, -1))
	{
		destination = destinationIN;
	}
}

void Tank::setTarget(int targetID)
{
	target_ID = targetID;
}

void Tank::attack(int targetID)
{
	//attack in direction of tank's current target
}