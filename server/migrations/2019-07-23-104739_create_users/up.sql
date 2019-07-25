CREATE TABLE users(
    id serial PRIMARY KEY,
    email VARCHAR(100) NOT NULL UNIQUE,
    encrypted_password VARCHAR(122) NOT NULL,
    salt bytea NOT NULL,
    is_admin BOOLEAN NOT NULL DEFAULT FALSE,
    created_at TIMESTAMP NOT NULL
);
