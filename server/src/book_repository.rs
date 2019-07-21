use crate::models::{Book, NewBook};
use crate::schema::books;
use diesel::{self, prelude::*};

pub fn get(id: i32, conn: &PgConnection) -> QueryResult<Book> {
    books::table.find(id).get_result(conn)
}

pub fn create(new_book: NewBook, conn: &PgConnection) -> QueryResult<Book> {
    diesel::insert_into(books::table)
        .values(&new_book)
        .get_result(conn)
}

pub fn list(conn: &PgConnection) -> QueryResult<Vec<Book>> {
    books::table.order(books::id.desc()).load::<Book>(conn)
}

pub fn update(book: Book, conn: &PgConnection) -> QueryResult<Book> {
    diesel::update(books::table.find(book.id))
        .set(&book)
        .get_result(conn)
}
