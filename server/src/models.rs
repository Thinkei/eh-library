use crate::schema::*;
use diesel::{r2d2::ConnectionManager, PgConnection};

pub type Pool = diesel::r2d2::Pool<ConnectionManager<PgConnection>>;

#[table_name = "books"]
#[derive(Serialize, Deserialize, Queryable, AsChangeset)]
pub struct Book {
    pub id: i32,
    pub name: String,
}
