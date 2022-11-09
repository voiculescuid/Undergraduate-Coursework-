CREATE TABLE IF NOT EXISTS roles (
    id serial PRIMARY KEY,
    value varchar NOT NULL UNIQUE
);

INSERT INTO roles (value) VALUES ('Administrator');
INSERT INTO roles (value) VALUES ('User');

CREATE TABLE IF NOT EXISTS users (
    id serial PRIMARY KEY,
	name varchar NOT NULL,
    username varchar NOT NULL UNIQUE,
	email varchar NOT NULL,
    password varchar NOT NULL,
    role_id integer REFERENCES roles(id)
);

INSERT INTO users (name, username, email, password, role_id) VALUES ('Voiculescu Ion-Daniel', 'admin', 'voiculescuid@gmail.com', 'admin', 1);
INSERT INTO users (name, username, email, password, role_id) VALUES ('Voiculescu Ion-Daniel', 'user', 'voiculescuid@gmail.com', 'user', 2);