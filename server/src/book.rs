use diesel;
use diesel::prelude::*;
use super::schema::books;

#[table_name = "books"]
#[derive(Serialize, Deserialize, Queryable, Insertable)]
pub struct Book {
    pub id: Option<i32>,
    pub name: String,
}
