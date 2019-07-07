#![allow(proc_macro_derive_resolution_fallback)]

use diesel;
use diesel::prelude::*;
use diesel::pg::PgConnection;
use crate::schema::books;
use crate::models::Book;

pub fn create(book: InsertableBook, connection: &PgConnection) -> QueryResult<Book> {
    diesel::insert_into(books::table)
        .values(&book)
        .get_result(connection)
}

pub fn list(connection: &PgConnection) -> Vec<Book> {
    books::table.order(books::id.desc()).load::<Book>(connection).unwrap()
}

#[derive(Insertable, Serialize, Deserialize)]
#[table_name="books"]
pub struct InsertableBook {
    name: String,
}
