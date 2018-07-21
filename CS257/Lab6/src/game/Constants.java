/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * */
package game;

public interface Constants 
{
	String[] LEVELS
	= {"Easy", "Moderate", "Normal", "Difficult", "Excruciating"};
	
	int[][] FIGURES =
	{ 
	{ 2, 1, 5, 1 }, // Easy: mines, shields, predators, avatars,
	{ 3, 2, 5, 1 }, // Moderate: mines, shields, predators, avatars,
	{ 4, 4, 5, 1 }, // Normal: mines, shields, predators, avatars,
	{ 5, 4, 5, 1 }, // Difficult: mines, shields, predators, avatars,
	{ 6, 5, 5, 1 }, // Excruciating: mines, shields, predators, avatars,
	};
	
	int MAX_AVATARS = 9;  // The maximum number of avatars waiting to play
	int SHIELDS_WIN = 5; //Max number of shields to win the game on any difficulty level
	
	AvatarPanel avatarPanel = new AvatarPanel();
	Background background   = new Background();
	SouthPanel southPanel   = new SouthPanel();
}
