CREATE TABLE users(
    id serial PRIMARY KEY,
    email VARCHAR(100) NOT NULL UNIQUE,
    encrypted_password VARCHAR(122) NOT NULL,
    salt VARCHAR(64) NOT NULL,
    created_at TIMESTAMP NOT NULL
);
