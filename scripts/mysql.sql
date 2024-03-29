-- @copyright 2006-2009 City of Bloomington, Indiana
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
-- @author Cliff Ingham <inghamn@bloomington.in.gov>
create table races (
	id int unsigned not null primary key auto_increment,
	name varchar(50) not null unique
) engine=InnoDB;
insert races set name='Caucasion';
insert races set name='Hispanic';
insert races set name='African American';
insert races set name='Native American';
insert races set name='Asian';
insert races set name='Other';

create table people (
	id int unsigned not null primary key auto_increment,
	firstname varchar(128) not null,
	lastname varchar(128) not null,
	email varchar(128),
	address varchar(128),
	city varchar(128),
	zipcode varchar(15),
	about text,
	gender enum('male','female'),
	race_id int unsigned,
	birthdate date,
	unique (email),
	foreign key (race_id) references races(id)
) engine=InnoDB;
insert people set id=1,firstname='Administrator',lastname='';

create table phoneNumbers (
	id int unsigned not null primary key auto_increment,
	person_id int unsigned not null,
	ordering tinyint (1) unsigned not null default 1,
	type enum('home','work','cell','fax') not null default 'home',
	number varchar(15) not null,
	private boolean not null default 0,
	foreign key (person_id) references people(id)
) engine=InnoDB;

create table people_private_fields (
	person_id int unsigned not null,
	fieldname varchar(128) not null,
	primary key (person_id,fieldname),
	foreign key (person_id) references people(id)
) engine=InnoDB;

CREATE TABLE users (
	id int unsigned not null primary key auto_increment,
	person_id int unsigned not null unique,
	username varchar(30) not null unique,
	password varchar(32),
	authenticationMethod varchar(40) not null default 'LDAP',
	foreign key (person_id) references people(id)
) engine=InnoDB;
insert users values(1,1,'admin',md5('admin'),'local');

CREATE TABLE roles (
	id int unsigned not null primary key auto_increment,
	name varchar(30) not null unique
) engine=InnoDB;
insert roles values(1,'Administrator');
insert roles values(2,'Clerk');

CREATE TABLE user_roles (
	user_id int unsigned not null,
	role_id int unsigned not null,
	primary key (user_id,role_id),
	foreign key(user_id) references users (id),
	foreign key(role_id) references roles (id)
) engine=InnoDB;
insert user_roles values(1,1);

create table committees (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	statutoryName varchar(128),
	statuteReference varchar(128),
	dateFormed date,
	website varchar(128),
	description text
) engine=InnoDB;

create table appointers (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null unique
) engine=InnoDB;
insert appointers values(1,'Elected');

create table requirements (
	id int unsigned not null primary key auto_increment,
	text varchar(255) not null
) engine=InnoDB;

create table seats (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	committee_id int unsigned not null,
	appointer_id int unsigned not null default 1,
	maxCurrentTerms tinyint unsigned not null default 1,
	foreign key (appointer_id) references appointers(id),
	foreign key (committee_id) references committees(id)
) engine=InnoDB;

create table seat_requirements (
	seat_id int unsigned not null,
	requirement_id int unsigned not null,
	primary key (seat_id,requirement_id),
	foreign key (seat_id) references seats(id),
	foreign key (requirement_id) references requirements(id)
) engine=InnoDB;

create table terms (
	id int unsigned not null primary key auto_increment,
	seat_id int unsigned not null,
	person_id int unsigned not null,
	term_start date,
	term_end date,
	foreign key (seat_id) references seats(id),
	foreign key (person_id) references people(id)
) engine=InnoDB;

create table officers (
	id int unsigned not null primary key auto_increment,
	committee_id int unsigned not null,
	person_id int unsigned not null,
	title varchar(128) not null,
	startDate date not null,
	endDate date,
	foreign key (committee_id) references committees(id),
	foreign key (person_id) references people(id)
) engine=InnoDB;

create table topicTypes (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null
) engine=InnoDB;

create table topics (
	id int unsigned not null primary key auto_increment,
	topicType_id int unsigned not null,
	date date not null,
	number varchar(25) not null,
	description text not null,
	synopsis text not null,
	committee_id int unsigned not null,
	foreign key (topicType_id) references topicTypes(id),
	foreign key (committee_id) references committees(id)
) engine=InnoDB;

create table voteTypes (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	ordering tinyint unsigned not null,
	unique (ordering)
) engine=InnoDB;

create table votes (
	id int unsigned not null primary key auto_increment,
	date date not null,
	voteType_id int unsigned not null,
	topic_id int unsigned not null,
	outcome enum('pass','fail'),
	foreign key (voteType_id) references voteTypes(id),
	foreign key (topic_id) references topics(id)
) engine=InnoDB;

create table votingRecords (
	id int unsigned not null primary key auto_increment,
	term_id int unsigned not null,
	vote_id int unsigned not null,
	position enum('yes','no','abstain','absent') not null default 'absent',
	foreign key (term_id) references terms(id),
	foreign key (vote_id)  references votes(id)
) engine=InnoDB;

create table tags (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null
) engine=InnoDB;

create table topic_tags (
	topic_id int unsigned not null,
	tag_id int unsigned not null,
	foreign key (topic_id) references topics(id),
	foreign key (tag_id) references tags(id)
) engine=InnoDB;
