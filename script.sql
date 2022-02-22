----- Scripts para criacao de BDs para a disciplina de BD UFPR CI1218
----- Autor: Eduardo Cunha de Almeida, eduardo@inf.ufpr.br
----- Esquema dos slides da aula de SQL
------
------
----- IMPORTANTE
----- Esquema utiliza tipos de dados compatíveis com os SGBDs PostgreSQL e SQLite

drop table autorlivros;
drop table autores;
drop table livros;


create table autores(
	autor VARCHAR(30),
	cpf BIGINT,
	email VARCHAR(20),
	idade INTEGER,
	primary key(autor, cpf)
);
insert into autores VALUES('JK. Rowling',12345678911,'jk@gmail',20);
insert into autores VALUES('H. Melville',22345678922,'m@yahoo',69);
insert into autores VALUES('F. Sabino',32345678933,'s@ig',21);
insert into autores VALUES('J. Widom',42345678944,'jw@ig',NULL);


create table livros(
	isbn INTEGER primary key,
	titulo VARCHAR(30),
	editora VARCHAR(30)
);
insert into livros VALUES(1234,'Harry Potter 1','Pottermore');
insert into livros VALUES(1121,'Mobi Dick','DCL');
insert into livros VALUES(2222,'Grande Mentecapto','Nordica');
insert into livros VALUES(2223,'Inglesa Deslumbrada','Nordica');
insert into livros VALUES(2224,'De Ponta Cabeça','Nordica');
insert into livros VALUES(2225,'Encontro Marcado','Nordica');


create table autorlivros(
	autor VARCHAR(30),
	cpf  BIGINT,
	isbn INTEGER,
	foreign key (autor,cpf) references autores(autor,cpf),
	foreign key (isbn) references livros(isbn)
);
insert into autorlivros VALUES('JK. Rowling',12345678911,1234);
insert into autorlivros VALUES('H. Melville',22345678922,1121);
insert into autorlivros VALUES('F. Sabino',32345678933,2222);
insert into autorlivros VALUES('F. Sabino',32345678933,2223);
insert into autorlivros VALUES('F. Sabino',32345678933,2224);
insert into autorlivros VALUES('F. Sabino',32345678933,2225);

----- Esquema dos slides da aula de modelagem de BD

drop table alunos;
create table alunos(
	grr INTEGER primary key,
	nome VARCHAR(20),
	idade INTEGER,
	ira DECIMAL
);
insert into alunos VALUES(111,'JOSE',20,0.7);
insert into alunos VALUES(112,'JOAO',69,0.35);
insert into alunos VALUES(113,'PEDRO',21,0.8);

drop table disciplinas;
create table disciplinas(
	disc VARCHAR(5) primary key,
	nome VARCHAR(20)
);
insert into disciplinas VALUES('CI068','Circuitos Digitais');
insert into disciplinas VALUES('CI057','Algoritmos III');
insert into disciplinas VALUES('CI218','Bancos de Dados');


drop table matriculas;
create table matriculas(
	grr INTEGER references alunos(grr),
	disc VARCHAR(5) references disciplinas(disc),
	nota INTEGER
);
insert into matriculas VALUES(111,'CI068',80);
insert into matriculas VALUES(112,'CI068',30);
insert into matriculas VALUES(112,'CI057',20);
insert into matriculas VALUES(111,'CI057',60);
insert into matriculas VALUES(113,'CI218',80);


drop table matr;
create table matr(
	numalu INTEGER references alunos(numalu),
	nomedisc VARCHAR(5),
	nota INTEGER,
	faltas INTEGER
);
insert into matr VALUES(111,'CI218',40,21);
insert into matr VALUES(111,'CI056',80,1);
insert into matr VALUES(111,'CI057',80,10);
insert into matr VALUES(115,'CI218',90,1);
insert into matr VALUES(115,'CI056',50,9);
insert into matr VALUES(114,'CI057',60,1);

----- Esquemas dos slides da aula de modelagem de BD com erros de definicao de chaves

----- Decomposicao incorreta (resultado NJ = 9 tuplas)
create table e1(aluno varchar(10),instrutor varchar(10));
create table e2(aluno varchar(10),disc varchar(10));
insert into e1 values('maria','eduardo');
insert into e1 values('maria','andre');
insert into e1 values('maria','didonet');
insert into e2 values('maria','ci218');
insert into e2 values('maria','ci056');
insert into e2 values('maria','ci057');
select * from e1 natural join e2;

----- Decomposicao incorreta (resultado NJ = 6 tuplas)
create table e1b(disc varchar(10),instrutor varchar(10));
create table e2b(disc varchar(10),aluno varchar(10));
insert into e1b values('ci218','eduardo');
insert into e1b values('ci218','sunye');
insert into e1b values('ci218','carmem');
insert into e1b values('ci056','andre');
insert into e1b values('ci056','david');
insert into e1b values('ci057','didonet');
insert into e2b values('ci057','maria');
insert into e2b values('ci056','maria');
insert into e2b values('ci218','maria');
select * from e1b natural join e2b;

----- Decomposicao correta (resultado NJ = 3 tuplas)
create table e1c(disc varchar(10),instrutor varchar(10));
create table e2c(instrutor varchar(10),aluno varchar(10));
insert into e1c values('ci218','eduardo');
insert into e1c values('ci218','sunye');
insert into e1c values('ci218','carmem');
insert into e1c values('ci056','andre');
insert into e1c values('ci056','david');
insert into e1c values('ci057','didonet');
insert into e2c values('didonet','maria');
insert into e2c values('andre','maria');
insert into e2c values('eduardo','maria');
select * from e1c natural join e2c;  