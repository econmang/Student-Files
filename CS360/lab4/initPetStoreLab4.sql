/*
Pete Nordquist  120611
You must replace all occurrences of P:\\cs360\\lab4\\
with the path to your local files.
Remember to use double backslashes \\ in this path.
*/

# Drop existing tables in order
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

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Animal.csv'
    INTO TABLE Animal FIELDS TERMINATED BY ',';

# City

CREATE  TABLE `City` (
  `CityID` INT NOT NULL ,
  `ZipCode` VARCHAR(45) NULL ,
  `City` VARCHAR(45) NULL ,
  `State` VARCHAR(45) NULL ,
  `AreaCode` VARCHAR(45) NULL ,
  `Population1980` INT NULL ,
  `Country` VARCHAR(45) NULL ,
  PRIMARY KEY (`CityID`) )
  ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\City.csv'
    INTO TABLE City FIELDS TERMINATED BY ',';

# Employee

CREATE  TABLE `Employee` (
  `EmployeeID` INT NOT NULL ,
  `LastName` VARCHAR(45) NULL ,
  `FirstName` VARCHAR(45) NULL ,
  `Phone` VARCHAR(45) NULL ,
  `Address` VARCHAR(45) NULL ,
  `ZipCode` VARCHAR(45) NULL ,
  `CityID` INT NULL ,
  `TaxPayerID` VARCHAR(45) NULL ,
  `DateHired` DATE NULL ,
  `DateReleased` DATE NULL ,
  `ManagerID` INT NULL ,
  `EmployeeLevel` INT NULL ,
  `Title` VARCHAR(45) NULL ,
  PRIMARY KEY (`EmployeeID`),
  CONSTRAINT `empCityFK` FOREIGN KEY (`CityID`) REFERENCES `City` (`CityID`) ON DELETE CASCADE ON UPDATE CASCADE
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Employee.csv'
    INTO TABLE Employee FIELDS TERMINATED BY ',';

# Supplier

CREATE  TABLE `Supplier` (
  `SupplierID` INT NOT NULL ,
  `Name` VARCHAR(45) NULL ,
  `ContactName` VARCHAR(45) NULL ,
  `Phone` VARCHAR(45) NULL ,
  `Address` VARCHAR(45) NULL ,
  `ZipCode` VARCHAR(45) NULL ,
  `CityID` INT NULL ,
  PRIMARY KEY (`SupplierID`),
  CONSTRAINT `supCityFK` FOREIGN KEY (`CityID`) REFERENCES `City` (`CityID`) ON DELETE CASCADE ON UPDATE CASCADE
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Supplier.csv'
    INTO TABLE Supplier FIELDS TERMINATED BY ',';

# AnimalOrder

CREATE  TABLE `AnimalOrder` (
  `OrderID` INT NOT NULL ,
  `OrderDate` DATE NULL ,
  `ReceiveDate` DATE NULL ,
  `SupplierID` INT NULL ,
  `ShippingCost` DECIMAL(6,2) NULL ,
  `EmployeeID` INT NULL ,
  PRIMARY KEY (`OrderID`),
  CONSTRAINT `aoSupplierFK` FOREIGN KEY (`SupplierID`) REFERENCES `Supplier` (`SupplierID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `aoEmployeeFK` FOREIGN KEY (`EmployeeID`) REFERENCES `Employee` (`EmployeeID`) ON DELETE CASCADE ON UPDATE CASCADE
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\AnimalOrder.csv'
    INTO TABLE AnimalOrder FIELDS TERMINATED BY ',';

# AnimalOrderItem

CREATE  TABLE `AnimalOrderItem` (
  `OrderID` INT NOT NULL ,
  `AnimalID` INT NOT NULL ,
  `Cost` DECIMAL(6,2) NULL ,
  PRIMARY KEY (`OrderID`,`AnimalID`),
  CONSTRAINT `aoiAnimalOrderFK` FOREIGN KEY (`OrderID`) REFERENCES `AnimalOrder` (`OrderID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `aoiAnimalFK` FOREIGN KEY (`AnimalID`) REFERENCES `Animal` (`AnimalID`) ON DELETE CASCADE ON UPDATE CASCADE
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\AnimalOrderItem.csv'
    INTO TABLE AnimalOrderItem FIELDS TERMINATED BY ',';

# Customer table

CREATE  TABLE `Customer` (
  `CustomerID` INT NOT NULL ,
  `Phone` VARCHAR(45) NULL ,
  `FirstName` VARCHAR(45) NULL ,
  `LastName` VARCHAR(45) NULL ,
  `Address` VARCHAR(45) NULL ,
  `ZipCode` VARCHAR(45) NULL ,
  `CityID` INT NULL ,
  PRIMARY KEY (`CustomerID`)
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Customer.csv'
    INTO TABLE Customer FIELDS TERMINATED BY ',';

# Sale

CREATE  TABLE `Sale` (
  `SaleID` INT NOT NULL ,
  `SaleDate` DATE NULL ,
  `EmployeeID` INT NULL ,
  `CustomerID` INT NULL ,
  `SalesTax` DECIMAL(6,2) NULL ,
  PRIMARY KEY (`SaleID`),
  CONSTRAINT `sEmployeeFK` FOREIGN KEY (`EmployeeID`) REFERENCES `Employee` (`EmployeeID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `sCustomerFK` FOREIGN KEY (`CustomerID`) REFERENCES `Customer` (`CustomerID`) ON DELETE CASCADE ON UPDATE CASCADE
  ) ENGINE = InnoDB;

LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Sale.csv'
    INTO TABLE Sale FIELDS TERMINATED BY ',';



# Create tables originally from lab 3
CREATE  TABLE `SaleAnimal` (
  `SaleID` INT NOT NULL ,
  `AnimalID` INT NOT NULL ,
  `SalePrice` DECIMAL(6,2) NULL ,
  PRIMARY KEY (`SaleID`, `AnimalID`),
  INDEX `SASaleID` (`SaleID` ASC) ,
  INDEX `SAAnimalID` (`AnimalID` ASC) ,
  CONSTRAINT `SASaleID`
    FOREIGN KEY (`SaleID` )
    REFERENCES `Sale` (`SaleID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `SAAnimalID`
    FOREIGN KEY (`AnimalID` )
    REFERENCES `Animal` (`AnimalID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE);
LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\SaleAnimal.csv'
    INTO TABLE SaleAnimal FIELDS TERMINATED BY ',';

CREATE  TABLE `Merchandise` (
  `ItemID` INT NOT NULL ,
  `Description` VARCHAR(45) NULL ,
  `QuantityOnHand` INT NULL ,
  `ListPrice` DECIMAL(6,2) NULL ,
  `Category` VARCHAR(45) NULL ,
  PRIMARY KEY (`ItemID`) );
LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\Merchandise.csv'
    INTO TABLE Merchandise FIELDS TERMINATED BY ',';

CREATE  TABLE `MerchandiseOrder` (
  `PONumber` INT NOT NULL ,
  `OrderDate` DATE NULL ,
  `ReceiveDate` DATE NULL ,
  `SupplierID` INT NULL ,
  `EmployeeID` INT NULL ,
  `ShippingCost` DECIMAL(6,2) NULL ,
  PRIMARY KEY (`PONumber`) ,
  CONSTRAINT `MOSupplierIDFK`
    FOREIGN KEY (SupplierID)
    REFERENCES `Supplier` (SupplierID)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `MOEmployeeIDFK`
    FOREIGN KEY (EmployeeID)
    REFERENCES `Employee` (EmployeeID)
    ON DELETE CASCADE
    ON UPDATE CASCADE);
LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\MerchandiseOrder.csv'
    INTO TABLE MerchandiseOrder FIELDS TERMINATED BY ',';

CREATE  TABLE `OrderItem` (
  `PONumber` INT NOT NULL ,
  `ItemID` INT NOT NULL ,
  `Quantity` INT NULL ,
  `Cost` DOUBLE(6,2) NULL ,
  PRIMARY KEY (`PONumber`, `ItemID`) ,
  CONSTRAINT `OIPONumberFK`
    FOREIGN KEY (`PONumber` )
    REFERENCES `MerchandiseOrder` (`PONumber` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `OIItemIDFK`
    FOREIGN KEY (`ItemID` )
    REFERENCES `Merchandise` (`ItemID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE);
LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\OrderItem.csv'
    INTO TABLE OrderItem FIELDS TERMINATED BY ',';

CREATE  TABLE `SaleItem` (
  `SaleID` INT NOT NULL ,
  `ItemID` INT NOT NULL ,
  `Quantity` INT NULL ,
  `SalePrice` DOUBLE(6,2) NULL ,
  PRIMARY KEY (`SaleID`, `ItemID`) ,
  INDEX `SISaleID` (`SaleID` ASC) ,
  INDEX `SIItemID` (`ItemID` ASC) ,
  CONSTRAINT `SISaleID`
    FOREIGN KEY (`SaleID` )
    REFERENCES `Sale` (`SaleID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `SIItemID`
    FOREIGN KEY (`ItemID` )
    REFERENCES `Merchandise` (`ItemID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE);
LOAD DATA LOCAL INFILE 'P:\\cs360\\lab4\\SaleItem.csv'
    INTO TABLE SaleItem FIELDS TERMINATED BY ',';
