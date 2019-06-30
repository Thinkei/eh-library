use diesel;
use diesel::prelude::*;
use diesel::pg::PgConnection;
use super::schema::books;

#[table_name = "books"]
#[derive(Serialize, Deserialize, Queryable, Insertable)]
pub struct Book {
    pub id: Option<i32>,
    pub name: String,
}

impl Book {
    pub fn create(book: Book, connection: &PgConnection) -> Book {
        diesel::insert_into(books::table)
            .values(&book)
            .execute(connection)
            .expect("Error creating new book");

        books::table.order(books::id.desc()).first(connection).unwrap()
    }
}
