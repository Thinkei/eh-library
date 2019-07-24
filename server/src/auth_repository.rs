use crate::errors::{self, ServiceError};
use crate::models::{NewUser, User};
use argonautica::{Hasher, Verifier};
use diesel::{self, prelude::*};
#[derive(Deserialize)]
pub struct AuthData {
    email: String,
    password: String,
}

pub fn register(auth_data: AuthData, conn: &PgConnection) -> Result<User, ServiceError> {
    // check duplicate email

    use crate::schema::users::dsl::{email, users};

    let user: QueryResult<User> = users.filter(email.eq(auth_data.email)).first::<User>(conn);

    if let Ok(_) = user {
        return Err(ServiceError::EmailExisted);
    }

    // let salt: String = generate_salt();
    // let encrypted_password: String = encryt_password(password, salt);

    Err(ServiceError::Unauthorized)
}

// pub fn encrypt_password(password: &str) -> Result<String, ServiceError> {
//     Hasher::default()
//         .with_password(password)
//         .with_secret_key(SECRET_KEY)
//         .hash()
//         .map_err(|err| {
//             dbg!(err);
//             ServiceError::Unauthorized
//         })
// }

// pub fn verify(hash: &str, password: &str) -> Result<bool, ServiceError> {}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::test_helpers::*;

    use std::env;

    #[test]
    fn register_when_duplicate_email() {
        let _guard = this_test_modifies_env();

        let conn = connection();

        let auth_data = AuthData {
            email: "x@example.com".to_owned(),
            password: "123".to_owned(),
        };

        let actual = register(auth_data, &conn);
        assert_matches!(actual, Err(ServiceError::Unauthorized));
    }

    #[test]
    fn register_when_success() {
        let _guard = this_test_modifies_env();

        let conn = connection();

        let new_user = NewUser {
            email: "x@example.com".to_owned(),
            encrypted_password: "123".to_owned(),
            salt: "123".to_owned(),
            is_admin: false,
            created_at: chrono::Local::now().naive_local(),
        };

        use crate::schema::users;
        diesel::insert_into(users::table)
            .values(&new_user)
            .execute(&conn);

        let auth_data = AuthData {
            email: "x@example.com".to_owned(),
            password: "123".to_owned(),
        };

        let actual = register(auth_data, &conn);
        assert_matches!(actual, Err(ServiceError::EmailExisted));
    }
}
