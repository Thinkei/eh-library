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
    pub fn create(book: Book, connection: &PgConnection) -> QueryResult<Book> {
        diesel::insert_into(books::table)
            .values(&book)
            .get_result(connection)
    }

    pub fn list(connection: &PgConnection) -> Vec<Book> {
        books::table.order(books::id.desc()).load::<Book>(connection).unwrap()
    }
}
