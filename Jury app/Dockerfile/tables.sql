CREATE DATABASE MPS_PROJECT_1;

CREATE TABLE users (
    user_id SERIAL PRIMARY KEY,
    user_name VARCHAR(255) NOT NULL,
    user_password VARCHAR(255) NOT NULL,
	user_authority VARCHAR(255),
	user_keyword VARCHAR(255)
);

INSERT INTO users (user_name,user_password, user_authority, user_keyword)
	VALUES ('admin','admin', 'admin', 'admin');
INSERT INTO users (user_name,user_password, user_authority, user_keyword)
	VALUES ('org','org', 'org', 'admin');
INSERT INTO users (user_name,user_password, user_authority, user_keyword)
	VALUES ('jury','jury', 'jury', 'admin');
 
CREATE TABLE competitors (
    competitor_id SERIAL PRIMARY KEY,
    competitor_name VARCHAR(255),
	competitor_numb INT,`
	competitor_grade INT
);

INSERT INTO competitors(competitor_name, competitor_numb, competitor_grade)
	VALUES ('Mihai Petre',10, -1);
INSERT INTO competitors(competitor_name, competitor_numb, competitor_grade)
	VALUES ('Florin Salam',32, 10000);
INSERT INTO competitors(competitor_name, competitor_numb, competitor_grade)
	VALUES ('Klaus Iohannis',123, 10);
INSERT INTO competitors(competitor_name, competitor_numb, competitor_grade)
	VALUES ('Viorica Vasilica Dancila',0, 0);
INSERT INTO competitors(competitor_name, competitor_numb, competitor_grade)
	VALUES ('Adrian Surpateanu',-1, -1);
	
CREATE TABLE comp (
    comp_id SERIAL PRIMARY KEY,
    comp_name VARCHAR(255),
    comp_description VARCHAR(255),
	comp_type VARCHAR(255),
	comp_rounds INT,
	comp_keyword VARCHAR(255),
	comp_start_timestamp TIME (0),
	comp_stop_timestamp TIME (0),
	comp_status VARCHAR(255)
);

INSERT INTO comp(comp_name,comp_description, comp_type, comp_rounds, comp_keyword, comp_status)
	VALUES ('Streaptease', 'Received overcame oh sensible so at an. Formed do change merely to county it. Am separate contempt domestic to to oh.', 'sincron', 2, 'muiepsd', 'finished');

CREATE TABLE rounds (
	id SERIAL PRIMARY KEY,
    round_comp_id INT REFERENCES comp(comp_id),
	round_id INT,
    round_description VARCHAR(255),
	round_start_timestamp TIME (0),
	round_stop_timestamp TIME (0),
	round_status VARCHAR(255)
);
 
INSERT INTO rounds(round_comp_id, round_id, round_description, round_start_timestamp, round_stop_timestamp, round_status) 
	VALUES (1, 1, 'On relation my so addition branched. Put hearing cottage she norland letters equally prepare too.', '09:10:00', '09:15:00', 'finished');
INSERT INTO rounds(round_comp_id, round_id, round_description, round_start_timestamp, round_stop_timestamp, round_status) 
	VALUES (1, 2, 'Replied exposed savings he no viewing as up.', '10:10:00', '11:15:00', 'finished');

CREATE TABLE jury_comp (
	id SERIAL PRIMARY KEY,
	jury_comp_id INT,
	jury_jury_name VARCHAR(255),
	jury_competitor_name VARCHAR(255),
	jurt_grade INT
);

CREATE TABLE comments (
	id SERIAL PRIMARY KEY,
    comment_id INT REFERENCES comp(comp_id),
    comment_author VARCHAR(255),
	comment_timestamp TIME (0),
	comment_content VARCHAR(255)
);

INSERT INTO comments(comment_id, comment_author, comment_timestamp, comment_content)
	VALUES(1, 'Traian', '09:10:00', 'This sucks!');
INSERT INTO comments(comment_id, comment_author, comment_timestamp, comment_content)
	VALUES(1, 'Gigi', '09:30:00', 'Fuck this shit!');

COMMIT;

