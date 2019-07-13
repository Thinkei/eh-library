#[macro_use] extern crate diesel;
#[macro_use] extern crate serde_derive;

use actix_web::{web, App, HttpResponse, HttpServer, Responder};
use dotenv::dotenv;

fn hello() -> impl Responder {
    HttpResponse::Ok().body("Hello World!")
}

fn main() {
    dotenv().ok();

    HttpServer::new(|| {
        App::new()
            .route("/hello", web::get().to(hello))
    })
        .bind("0.0.0.0:8888")
        .unwrap()
        .run()
        .unwrap();
}
