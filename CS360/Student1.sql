Drop table if exists Student1;
CREATE TABLE Student1
(
StudId int,
StudName varchar(255),
SibName varchar(255),
Major varchar(255),
Primary Key(StudID,SibName,Major)
) Engine innodb;

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kevin','Mathematics');

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kevin','Psychology');


INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kerry','Mathematics');

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kerry','Psychology');

INSERT INTO Student1(StudId, StudName, SibName, Major) 
VALUES (127,'Dave Masterson','Sarah','Mathematics');

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Sarah','Psychology');

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (221,'Stacey Turncoat','Thomas','Psychology');

INSERT INTO Student1(StudId, StudName, SibName, Major)
VALUES (221,'Stacey Turncoat','Thomas','Mathematics')