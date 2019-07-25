use crate::schema::*;
use diesel::{r2d2::ConnectionManager, PgConnection};

pub type Pool = diesel::r2d2::Pool<ConnectionManager<PgConnection>>;

#[table_name = "books"]
#[graphql(description = "Book model")]
#[derive(Serialize, Deserialize, Queryable, AsChangeset, GraphQLObject)]
pub struct Book {
    pub id: i32,
    #[graphql(description = "Name of the book")]
    pub name: String,
}

#[table_name = "books"]
#[derive(Insertable, Serialize, Deserialize, GraphQLInputObject)]
#[graphql(description = "New Book object")]
pub struct NewBook {
    #[graphql(description = "Name of the book")]
    pub name: String,
}

#[table_name = "books"]
#[derive(Serialize, Deserialize, AsChangeset, GraphQLInputObject)]
#[graphql(description = "Update Book object")]
pub struct UpdateBook {
    pub id: i32,
    #[graphql(description = "Name of the book")]
    pub name: String,
}

#[table_name = "users"]
#[derive(Debug, Serialize, Deserialize, Queryable, AsChangeset)]
pub struct User {
    pub id: i32,
    pub email: String,
    pub encrypted_password: String,
    pub salt: Vec<u8>,
    pub is_admin: bool,
    pub created_at: chrono::NaiveDateTime,
}

#[table_name = "users"]
#[derive(Insertable, Serialize, Deserialize, Clone, Debug)]
pub struct NewUser {
    pub email: String,
    pub encrypted_password: String,
    pub salt: Vec<u8>,
    pub is_admin: bool,
    pub created_at: chrono::NaiveDateTime,
}
