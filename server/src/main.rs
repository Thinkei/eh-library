#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate rocket;
#[macro_use] extern crate serde_derive;

use rocket_contrib::json::Json;

mod book;
use book::Book;

#[post("/", data = "<book>")]
fn create(book: Json<Book>) -> Json<Book> {
    book
}

fn main() {
    rocket::ignite().mount("/books", routes![create]).launch();
}
