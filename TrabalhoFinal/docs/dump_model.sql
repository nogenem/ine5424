-- MySQL Script generated by MySQL Workbench
-- sáb 24 jun 2017 15:41:48 -03
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema sodb_novo
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema sodb_novo
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `sodb_novo` DEFAULT CHARACTER SET latin1 ;
USE `sodb_novo` ;

-- -----------------------------------------------------
-- Table `sodb_novo`.`smart_object`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`smart_object` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `device_id` INT NOT NULL,
  `name` VARCHAR(100) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`service`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`service` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `smart_object_id` INT(11) NOT NULL,
  `name` VARCHAR(100) NOT NULL,
  PRIMARY KEY (`id`, `smart_object_id`),
  INDEX `fk_service_smartobject1_idx` (`smart_object_id` ASC),
  UNIQUE INDEX `nome_unico` (`name` ASC, `smart_object_id` ASC),
  CONSTRAINT `fk_service_smartobject1`
    FOREIGN KEY (`smart_object_id`)
    REFERENCES `sodb_novo`.`smart_object` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`parameter_boolean`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`parameter_boolean` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `service_id` INT(11) NOT NULL,
  `name` VARCHAR(100) NULL DEFAULT NULL,
  `reg_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_parameter_service1_idx` (`service_id` ASC),
  CONSTRAINT `fk_parameter_service1`
    FOREIGN KEY (`service_id`)
    REFERENCES `sodb_novo`.`service` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`parameter_int`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`parameter_int` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `service_id` INT(11) NOT NULL,
  `name` VARCHAR(100) NULL DEFAULT NULL,
  `min_value` INT NULL DEFAULT NULL,
  `max_value` INT NULL DEFAULT NULL,
  `reg_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_parameter_service1_idx` (`service_id` ASC),
  CONSTRAINT `fk_parameter_service10`
    FOREIGN KEY (`service_id`)
    REFERENCES `sodb_novo`.`service` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`parameter_option`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`parameter_option` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `service_id` INT(11) NOT NULL,
  `name` VARCHAR(100) NULL DEFAULT NULL,
  `reg_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_parameter_service1_idx` (`service_id` ASC),
  CONSTRAINT `fk_parameter_service1000`
    FOREIGN KEY (`service_id`)
    REFERENCES `sodb_novo`.`service` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`parameter_float`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`parameter_float` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `service_id` INT(11) NOT NULL,
  `name` VARCHAR(100) NULL DEFAULT NULL,
  `min_value` FLOAT NULL DEFAULT NULL,
  `max_value` FLOAT NULL DEFAULT NULL,
  `reg_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_parameter_service1_idx` (`service_id` ASC),
  CONSTRAINT `fk_parameter_service100`
    FOREIGN KEY (`service_id`)
    REFERENCES `sodb_novo`.`service` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 12
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `sodb_novo`.`option`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`option` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `sodb_novo`.`options`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `sodb_novo`.`options` (
  `parameter_option_id` INT(11) NOT NULL,
  `option_id` INT NOT NULL,
  PRIMARY KEY (`parameter_option_id`, `option_id`),
  INDEX `fk_parameter_option_has_option_option1_idx` (`option_id` ASC),
  INDEX `fk_parameter_option_has_option_parameter_option1_idx` (`parameter_option_id` ASC),
  CONSTRAINT `fk_parameter_option_has_option_parameter_option1`
    FOREIGN KEY (`parameter_option_id`)
    REFERENCES `sodb_novo`.`parameter_option` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_parameter_option_has_option_option1`
    FOREIGN KEY (`option_id`)
    REFERENCES `sodb_novo`.`option` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = latin1;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
