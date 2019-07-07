#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use] extern crate diesel;
extern crate r2d2;
extern crate r2d2_diesel;

#[macro_use] extern crate rocket;
#[macro_use] extern crate serde_derive;

use dotenv::dotenv;

pub mod db;
pub mod schema;
pub mod google_json_response;
mod models;
mod books;

fn main() {
    dotenv().ok();

    rocket::ignite()
        .manage(db::connect())
        .mount("/books", routes![
            books::handler::list,
            books::handler::create,
            books::handler::get,
            books::handler::update,
        ])
        .launch();
}
