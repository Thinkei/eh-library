extern crate actix_web;
extern crate dotenv;
#[macro_use]
extern crate diesel;
#[macro_use]
extern crate serde_derive;
extern crate derive_more;
extern crate env_logger;
extern crate futures;

use actix_web::{middleware, web, App, HttpResponse, HttpServer, Responder};
use diesel::r2d2::{ConnectionManager, Pool};
use diesel::PgConnection;
use dotenv::dotenv;
use std::env;

mod book_handler;
mod errors;
mod models;
mod schema;

fn ping() -> impl Responder {
    HttpResponse::Ok().body("pong")
}

fn main() {
    dotenv().ok();
    env_logger::init();

    let database_url = env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    let sys = actix::System::new("eh-library");

    // connection pool
    let manager = ConnectionManager::<PgConnection>::new(database_url);
    let pool = Pool::builder()
        .build(manager)
        .expect("Failed to create pool");

    HttpServer::new(move || {
        App::new()
            .wrap(middleware::Logger::default())
            .route("/ping", web::get().to(ping))
            .service(
                web::scope("/api").data(pool.clone()).service(
                    web::resource("/books").route(web::get().to_async(book_handler::list)),
                ),
            )
    })
    .bind("0.0.0.0:8888")
    .unwrap()
    .start();

    let _ = sys.run();
}
