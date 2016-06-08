SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `neatbin` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `neatbin` ;

-- -----------------------------------------------------
-- Table `neatbin`.`lixeiras`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `neatbin`.`lixeiras` ;

CREATE TABLE IF NOT EXISTS `neatbin`.`lixeiras` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `capacidade` DOUBLE NOT NULL,
  `altura` FLOAT NOT NULL,
  `largura` FLOAT NOT NULL,
  `profundidade` FLOAT NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `neatbin`.`medicoes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `neatbin`.`medicoes` ;

CREATE TABLE IF NOT EXISTS `neatbin`.`medicoes` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `lixeiraid` INT UNSIGNED NOT NULL,
  `dist` DOUBLE NOT NULL,
  `data` DATETIME NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_lixeira_idx` (`lixeiraid` ASC),
  CONSTRAINT `fk_lixeira`
    FOREIGN KEY (`lixeiraid`)
    REFERENCES `neatbin`.`lixeiras` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `neatbin`.`picos`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `neatbin`.`picos` ;

CREATE TABLE IF NOT EXISTS `neatbin`.`picos` (
  `id` INT UNSIGNED NOT NULL,
  `Id_lixeira` INT UNSIGNED NOT NULL,
  `Inicio` TIME NOT NULL,
  `Fim` TIME NOT NULL,
  `QntPorHora` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_idlixeira_idx` (`Id_lixeira` ASC),
  CONSTRAINT `fk_idlixeira`
    FOREIGN KEY (`Id_lixeira`)
    REFERENCES `neatbin`.`lixeiras` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;