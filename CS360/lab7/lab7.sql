/*
 * CS360 Lab 7 sql file.
 * Modify this file to:
 * * Define the tables necessary for lab 7.
 * * Implement the stored procedures specified here.
 * * javadoc style markings mean the same thing they do in javadoc:
 * *    @param  -- an in parameter
 * *
 * * The data requirements given in lab 7 also apply to this lab.
 * * You may NOT change the headers for the stored procedures shown below.
 * *    The header is everything between keyword CREATE and keyword BEGIN 
 * *    for each procedure.
 * * You must remove all statements shown between BEGIN END keywords.  
 * *    The statements shown below give you an idea of how to cause a procedure
 * *    to pass a message back to the caller.
 * * When a procedure comment says return something, it means
 * *    use a select statement to pass data back to the caller.
 * *    When the comment says return an error message, the select statement
 * *    should indicate what error happened and what data caused this error.
 * * Procedures should never exit with an unhandled error code
 *
 * Procedures marked EXTRA CREDIT are not required and each procedure
 * so marked is worth the amount of extra credit specified.
*/

/*
Evan Conley
-- ERD GOES HERE:

	Team 1 1   ---------- has/play on ------------- 0 = Player
	Jersey = 0 ---------- is worn by/wears -------- 0 = Player
	Game 1 1   ---------- has/scored in ----------- 0 = Baskets
	Game 1 1   ---------- had/were made in -------- 0 = Fouls
	Basket = 0 ---------- has/is worth  ----------- 1 1 PointValue
	
	Team:
		TeamName

	Jersey:
		JerseyNo

	Player:
		PlayerName

	Roster:
		TeamName
		PlayerName
		JerseyNo

	Baskets:
		BasketID
		BasketPlayer
		PointValue

	Foul:
		FoulID
		FoulPlayer

	Game:
		Date
		Home
		Away
		BasketID
		FoulID
*/

-- TABLE DEFINITIONS GO HERE:
DROP TABLE IF EXISTS Game;
DROP TABLE IF EXISTS Foul;
DROP TABLE IF EXISTS Baskets;
DROP TABLE IF EXISTS Roster;
DROP TABLE IF EXISTS Team;
DROP TABLE IF EXISTS Player;
DROP TABLE IF EXISTS Jersey;

CREATE TABLE Jersey
(
JerseyNo INT NOT NULL,
CONSTRAINT pk1 PRIMARY KEY(JerseyNo)
);

CREATE TABLE Player
(
PlayerName VARCHAR(20) NOT NULL UNIQUE,
CONSTRAINT pk2 PRIMARY KEY(PlayerName)
);

CREATE TABLE Team
(
TeamName VARCHAR(45) NOT NULL,
CONSTRAINT pk3 PRIMARY KEY(TeamName)
);

CREATE TABLE Roster
(
TeamName VARCHAR(45),
PlayerName VARCHAR(20) UNIQUE,
JerseyNo INT,
CONSTRAINT fk1 FOREIGN KEY(TeamName) REFERENCES Team(TeamName),
CONSTRAINT fK2 FOREIGN KEY(PlayerName) REFERENCES Player(PlayerName),
CONSTRAINT fk3 FOREIGN KEY(JerseyNo) REFERENCES Jersey(JerseyNo),
CONSTRAINT pk4 PRIMARY KEY(TeamName,JerseyNo)
);

CREATE TABLE Baskets
(
BasketID INT,
BasketPlayer VARCHAR(20),
PointValue INT,
CONSTRAINT fk4 FOREIGN KEY(BasketPlayer) REFERENCES Player(PlayerName),
CONSTRAINT pk5 PRIMARY KEY(BasketID)
);

CREATE TABLE Foul
(

)
-- START OF STORED PROCEDURES:

delimiter ;
DROP PROCEDURE IF EXISTS addTeam;
delimiter //
/**
 * If teamName does not exist, creates a team having name teamName.
 * Takes no action if teamName already exists.
 * Hints: use an error handler
 * @param teamName name of team to find or create
 */

CREATE PROCEDURE addTeam(
	teamName VARCHAR(45))
BEGIN
	select concat( 'addTeam(', teamName, ') - Successful');
END
//

delimiter ;
DROP PROCEDURE IF EXISTS addPlayer;
delimiter //
/**
 * Add a player.
 * Takes no action if player pname already exists.
 * Returns an error message if unable to add player pnumb to teamName
 * @param teamName name of team to which to add player
 * @param pnumb player number
 * @param pname player name
 */
CREATE PROCEDURE addPlayer(
	teamName VARCHAR(45),
	pnumb INT UNSIGNED,
	pname VARCHAR(45))
BEGIN
	select concat( 'addPlayer(', 
		teamName, ', ', 
		cast(pnumb as char), ', ', 
		pname, ') - Successful');
END
//

delimiter ; 
DROP PROCEDURE IF EXISTS getRoster;
delimiter //
/**
 * Retrieve the roster for a team.
 * @param teamName name of team whose roster is to be retrieved
 * @return (Number, Name) of all players on team teamName
 * returns no records if teamName cannot be found or teamName has no players
 */
CREATE PROCEDURE getRoster( teamName VARCHAR(45))
BEGIN
	select concat( 'getRoster(', teamName, ') - Successful');
END
//

delimiter ;
DROP PROCEDURE IF EXISTS addGame;
delimiter //
/**
 * Add a game for this home, away, date combination.
 * Takes no action if this game already exists.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of the game
 */
CREATE PROCEDURE addGame(
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE)
BEGIN
	select concat( 'addGame(', homeTeam, ', ', awayTeam,
		', ', date_Format(gameDate, '%m-%d-%Y'), ') - Successful');
	 -- call addGame('home', 'away', '2014-03-08');

END
//

delimiter ;
DROP PROCEDURE IF EXISTS addBasket;
delimiter //
/**
 * Add a basket to a game.  Return a message if the number of points
 * is illegal.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param homeOrAway true if the home team scored, false if
 * the visiting team scored
 * @param pnumb player number
 * @param points number of points
 *
 * Hints: use an if statement to check the points.  
 * (Mysql ignores 'check' constraints in table definitions.)
 */
CREATE PROCEDURE addBasket(
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	homeOrAway BOOLEAN,
	pnumb INT,
	points INT)
BEGIN
	select concat( 'addBasket(', homeTeam, ', ', 
		awayTeam, ', ', 
		date_format(gameDate,'%Y-%m-%d'), ', ', 
		cast(homeOrAway as char), ', ', 
		cast(pnumb as char), ', ', 
		cast(points as char), ') - Successful');
	-- call addBasket('home','away','2014-03-08',false,55,3);
END
//

delimiter ;
DROP PROCEDURE IF EXISTS getPointsByPlayerForTeamForGame;
delimiter //
/**
 * Retrieve total points for each player on a single team in a single game.
 * The first three parameters identify the 
 * game.  The last parameter identifies the team making the points.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param teamName 
 * @return (Number, TotalPoints for player) for all players on team teamName
 * who made points
 */
CREATE PROCEDURE getPointsByPlayerForTeamForGame( 
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	teamName VARCHAR(45))
BEGIN
	select 'PLAYER #', 'POINTS';
END
//

delimiter ;
DROP PROCEDURE IF EXISTS getTotalPointsForTeamForGame;
delimiter //
/**
 * Get total points for a whole team for a single game.
 * The first three parameters identify the 
 * game.  The last parameter identifies the team making the points.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param teamName 
 * @return ('Total', TotalPoints) where TotalPoints is the sum of all points
 * made by all players who played for teamName in this game
 */
CREATE PROCEDURE getTotalPointsForTeamForGame( 
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	teamName VARCHAR(45))
BEGIN
	select 'Total', '55';
END
//

delimiter ;


-- START OF EXTRA CREDIT PROCEDURES:
DROP PROCEDURE IF EXISTS addFoul;
delimiter //
/**
 *
 * THIS PROCEDURE IS 2% EXTRA CREDIT.
 *
 * Add a foul to a game.
 * Return a message if either the fouler or foulee is not on
 * the appropriate team.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param homeOrAway true if the home team committed the foul, false if
 * the visiting team committed the foul
 * @param foulerNumber player number who committed the foul
 */
CREATE PROCEDURE addFoul(
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	homeOrAway BOOLEAN,
	foulerNumber INT UNSIGNED)
BEGIN
	select concat( 'addFoul(', homeTeam, ', ', 
		awayTeam, ', ', 
		date_format(gameDate,'%Y-%m-%d'), ', ', 
		cast(homeOrAway as char), ', ', 
		cast(foulerNumber as char), ') - Successful');
	-- call addFoul('home','away','2014-03-08',false,12);
END
//

delimiter ;
DROP PROCEDURE IF EXISTS getFoulsCommittedByPlayerForTeamForGame;
delimiter //
/**
 *
 * THIS PROCEDURE IS 2% EXTRA CREDIT.
 *
 * Get number of fouls committed by each player on a single team
 * in a single game.
 * The first three parameters identify the 
 * game.  The last parameter identifies the team committing the fouls.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param teamName 
 * @return (Player Number, TotalFoulsCommitted by this player) for all players
 * on team teamName who committed fouls in the game identified by the first
 * three parameters.
 */
CREATE PROCEDURE getFoulsCommittedByPlayerForTeamForGame( 
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	teamName VARCHAR(45))
BEGIN
	select 'COMMITTING', '# OF FOULS';
	select 'PLAYER #', 'COMMITTED';
END
//

delimiter ;
DROP PROCEDURE IF EXISTS getTotalFoulsCommittedForTeamForGame;
delimiter //
/**
 *
 * THIS PROCEDURE IS 2% EXTRA CREDIT.
 *
 * Get total number of fouls committed for a whole team for a single game.
 * The first three parameters identify the 
 * game.  The last parameter identifies the team committing the fouls.
 * @param homeTeam name of home team
 * @param awayTeam name of away team
 * @param gameDate date of game
 * @param teamName 
 * @return ('Total', TotalFoulsCommitted) where TotalFoulsCommitted is
 * the sum of all fouls committed by all players who played for
 * teamName in this game
 */
CREATE PROCEDURE getTotalFoulsCommittedForTeamForGame( 
	homeTeam VARCHAR(45),
	awayTeam VARCHAR(45),
	gameDate DATE,
	teamName VARCHAR(45))
BEGIN
	select 'Total', '7';
END
//
delimiter ;