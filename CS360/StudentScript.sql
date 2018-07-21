# Student table
Drop table if exists Schedule;

Drop table if exists Student;
CREATE TABLE `Student` (
  `id` int(11) NOT NULL,
  `name` varchar(50) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB;

# Course table
Drop table if exists Course;
CREATE TABLE `Course` (
  `crn` int(11) NOT NULL,
  `name` varchar(50) default NULL,
  `credits` int(2) default NULL,
  PRIMARY KEY  (`crn`)
) ENGINE=InnoDB;

# Schedule table

CREATE TABLE `Schedule` (
  `id` int(11) NOT NULL default '0',
  `crn` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`,`crn`),    # composite key
  # Foreign key constraint for Student id with referential integrity checks
  CONSTRAINT `studentFK` FOREIGN KEY (`id`) REFERENCES `Student` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  # Foreign key constraint for crn with referential integrity checks
  CONSTRAINT `courseFK` FOREIGN KEY (`crn`) REFERENCES `Course` (`crn`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;