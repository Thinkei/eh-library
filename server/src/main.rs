extern crate actix;
extern crate actix_web;
extern crate dotenv;
#[macro_use]
extern crate diesel;
#[macro_use]
extern crate serde_derive;

use actix::Addr;
use actix_web::{middleware, web, App, HttpResponse, HttpServer, Responder};
use diesel::r2d2::{ConnectionManager, Pool};
use diesel::PgConnection;
use dotenv::dotenv;
use std::env;

mod app;
mod db;
mod schema;

use crate::db::DbExecutor;
use app::AppState;

fn hello() -> impl Responder {
    HttpResponse::Ok().body("Hello World!")
}

fn main() {
    dotenv().ok();
    let database_url = env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    let sys = actix::System::new("eh-library");

    // connection pool
    let manager = ConnectionManager::<PgConnection>::new(database_url);
    let pool = Pool::builder()
        .build(manager)
        .expect("Failed to create pool");

    let address: Addr<DbExecutor> = actix::SyncArbiter::start(4, move || DbExecutor(pool.clone()));

    HttpServer::new(move || {
        App::new()
            .data(AppState {
                db: address.clone(),
            })
            .wrap(middleware::Logger::new("\"%r\" %s %b %Dms"))
            .route("/hello", web::get().to(hello))
    })
    .bind("0.0.0.0:8888")
    .unwrap()
    .start();

    let _ = sys.run();
}
