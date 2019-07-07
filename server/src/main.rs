#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate diesel;
#[macro_use] extern crate rocket;
#[macro_use] extern crate rocket_contrib;
#[macro_use] extern crate serde_derive;

use dotenv::dotenv;
use rocket::Rocket;

pub mod db;
pub mod schema;
pub mod google_json_response;
mod models;
mod books;

fn rocket() -> Rocket {
    rocket::ignite()
        .mount("/books", routes![
            books::handler::list,
            books::handler::create,
            books::handler::get,
            books::handler::update,
        ])
        .attach(db::Connection::fairing())
}

fn main() {
    dotenv().ok();

    rocket().launch();
}
