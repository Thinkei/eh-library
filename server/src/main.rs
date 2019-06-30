#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate diesel;
extern crate r2d2;
extern crate r2d2_diesel;

#[macro_use] extern crate rocket;
#[macro_use] extern crate serde_derive;

use rocket_contrib::json::Json;

mod db;
mod schema;
mod book;
use book::Book;

#[post("/", data = "<book>")]
fn create(book: Json<Book>) -> Json<Book> {
    book
}

fn main() {
    rocket::ignite()
        .manage(db::connect())
        .mount("/books", routes![create]).launch();
}
