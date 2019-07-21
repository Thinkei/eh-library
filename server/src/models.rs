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
