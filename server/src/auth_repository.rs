use crate::errors::ServiceError;
use crate::models::{NewUser, User};
use argonautica::{input::Salt, Hasher, Verifier};
use diesel::{self, prelude::*};

#[derive(Debug, Clone, Deserialize)]
pub struct AuthData {
    pub email: String,
    pub password: String,
}

lazy_static! {
    pub static ref SECRET_KEY: String = std::env::var("SECRET_KEY").unwrap();
}

pub fn register(auth_data: AuthData, conn: &PgConnection) -> Result<User, ServiceError> {
    use crate::schema::users::dsl::{email, users};

    let user: QueryResult<User> = users
        .filter(email.eq(auth_data.email.clone()))
        .first::<User>(conn);

    if let Ok(_) = user {
        return Err(ServiceError::EmailExisted);
    }

    let mut hasher: Hasher = Hasher::default()
        .with_password(auth_data.password.as_str())
        .with_secret_key(SECRET_KEY.as_str())
        .to_owned();

    let encrypted_password = hasher
        .hash()
        .map_err(|err| {
            dbg!(err);
            ServiceError::Unauthorized
        })
        .unwrap();
    let salt: Vec<u8> = hasher.salt().as_bytes().to_vec();

    dbg!(encrypted_password.clone());
    dbg!(salt.clone());

    let new_user = NewUser {
        email: auth_data.email,
        encrypted_password: encrypted_password,
        salt: salt,
        is_admin: false,
        created_at: chrono::Local::now().naive_local(),
    };

    dbg!(new_user.clone());

    diesel::insert_into(users)
        .values(&new_user)
        .get_result(conn)
        .map_err(|err| {
            dbg!(err);
            ServiceError::UnprocessableEntity
        })
}

pub fn encrypt_password(password: &str, salt: Salt) -> Result<String, ServiceError> {
    Hasher::default()
        .with_password(password)
        .with_secret_key(SECRET_KEY.as_str())
        .with_salt(salt)
        .hash()
        .map_err(|err| {
            dbg!(err);
            ServiceError::Unauthorized
        })
}

// pub fn verify(hash: &str, password: &str) -> Result<bool, ServiceError> {}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::test_helpers::*;

    #[test]
    fn register_when_success() {
        let _guard = this_test_modifies_env();

        let conn = connection();

        let email: &str = "x@example.com";

        let auth_data = AuthData {
            email: email.to_owned(),
            password: "123".to_owned(),
        };

        let user = register(auth_data, &conn).unwrap();
        assert_eq!(user.email, email);
    }

    #[test]
    fn register_when_duplicate_email() {
        let _guard = this_test_modifies_env();

        let conn = connection();

        let new_user = NewUser {
            email: "x@example.com".to_owned(),
            encrypted_password: "123".to_owned(),
            salt: "123".as_bytes().to_owned(),
            is_admin: false,
            created_at: chrono::Local::now().naive_local(),
        };

        use crate::schema::users;
        diesel::insert_into(users::table)
            .values(&new_user)
            .execute(&conn)
            .unwrap();

        let auth_data = AuthData {
            email: "x@example.com".to_owned(),
            password: "123".to_owned(),
        };

        let actual = register(auth_data, &conn);
        assert_matches!(actual, Err(ServiceError::EmailExisted));
    }
}
