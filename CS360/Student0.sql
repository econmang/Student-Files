/*
CREATE TABLE Student0(
`id` int (),
`studname` varchar(255),
`sibling` varchar(255),
`major` varchar(255),
);*/
Drop table if exists Student0;
CREATE TABLE Student0
(
StudId int,
StudName varchar(255),
SibName varchar(255),
Major varchar(255)
);

INSERT INTO Student0(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kevin','Mathematics');

INSERT INTO Student0(StudId, StudName, SibName, Major)
VALUES (127,'Dave Masterson','Kerry','Mathematics');

INSERT INTO Student0(StudId, StudName, SibName, Major) 
VALUES (127,'Dave Masterson','Sarah','Mathematics');

INSERT INTO Student0(StudId, StudName, SibName, Major)
VALUES (221,'Stacey Turncoat','Kevin','Psychology');

INSERT INTO Student0(StudId, StudName, SibName, Major)
VALUES (221,'Stacey Turncoat','Thomas','Psychology');