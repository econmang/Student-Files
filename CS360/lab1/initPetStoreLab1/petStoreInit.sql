# Drop any existing tables
DROP table if exists SaleAnimal;
Drop table if exists SaleItem;
Drop table if exists OrderItem;
DROP table if exists MerchandiseOrder;
DROP table if exists Merchandise;
drop table if exists Sale;
drop table if exists Customer;
drop table if exists AnimalOrderItem;
drop table if exists AnimalOrder;
drop table if exists Supplier;
drop table if exists Employee;
drop table if exists City;
drop table if exists Animal;

# Animal table

CREATE  TABLE `Animal` (   
	`AnimalID` INT NOT NULL ,  
	`Name` VARCHAR(45) NULL ,  
	`Category` VARCHAR(45) NULL ,  
	`Breed` VARCHAR(45) NULL ,  
	`DateBorn` DATE NULL ,  
	`Gender` VARCHAR(45) NULL ,  
	`Registered` VARCHAR(45) NULL ,  
	`Color` VARCHAR(45) NULL ,  
	`ListPrice` DECIMAL(6,2) NULL,  
	PRIMARY KEY (`AnimalID`) )
	ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\l1\\Animal.csv'
	INTO TABLE Animal FIELDS TERMINATED BY ',';

# Customer table

CREATE  TABLE `Customer` (
	`idCustomer` INT NOT NULL ,
	`phone` VARCHAR(45) NULL ,
	`firstName` VARCHAR(45) NULL ,
	`lastName` VARCHAR(45) NULL ,
	`address` VARCHAR(45) NULL ,
	`zipCode` VARCHAR(45) NULL ,
	`idCity` INT NULL ,
	PRIMARY KEY (`idCustomer`) ) 
	ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\l1\\Customer.csv'
	INTO TABLE Customer FIELDS TERMINATED BY ',';

