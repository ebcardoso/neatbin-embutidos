drop database bd_lixeira;
create database bd_lixeira;
use bd_lixeira;

create table lixeira (
	id_lixeira int primary key auto_increment,
	codigo varchar(30) unique,
	altura int not null
);

create table medicao (
	id_medicao int primary key auto_increment,
	id_lixeira int not null,
	med float not null,
	hora datetime not null
);

insert into lixeira (codigo, altura) values ("lix001", 47);
