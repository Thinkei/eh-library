#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate diesel;
extern crate r2d2;
extern crate r2d2_diesel;

#[macro_use] extern crate rocket;
#[macro_use] extern crate serde_derive;

use dotenv::dotenv;
use rocket_contrib::json;
use rocket_contrib::json::{ Json, JsonValue };

mod db;
mod schema;
mod book;
use book::Book;

#[post("/", data = "<book>")]
fn create(book: Json<Book>, connection: db::Connection) -> Json<Book> {
    let new_book = Book { id: None, ..book.into_inner()};
    Json(Book::create(new_book, &connection))
}

#[get("/")]
fn list(connection: db::Connection) -> Json<JsonValue> {
    Json(json!(Book::list(&connection)))
}

fn main() {
    dotenv().ok();

    rocket::ignite()
        .manage(db::connect())
        .mount("/books", routes![create, list]).launch();
}
