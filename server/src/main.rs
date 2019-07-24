#[macro_use]
extern crate juniper;

extern crate actix_cors;
extern crate actix_web;
extern crate dotenv;
#[macro_use]
extern crate diesel;
#[macro_use]
extern crate serde_derive;
#[cfg(test)]
#[macro_use]
extern crate assert_matches;
#[macro_use]
extern crate lazy_static;

extern crate derive_more;
extern crate env_logger;
extern crate futures;

use actix_cors::Cors;
use actix_web::{http, middleware, web, App, HttpResponse, HttpServer, Responder};
use diesel::r2d2::{ConnectionManager, Pool};
use diesel::PgConnection;
use dotenv::dotenv;
use std::env;

mod auth_repository;
mod book_handler;
mod book_repository;
mod errors;
mod graph_handler;
mod graph_schema;
mod models;
mod schema;

#[cfg(test)]
mod test_helpers;

use graph_handler::AppState;
use graph_schema::create_graph_schema;

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

    let graph_schema = std::sync::Arc::new(create_graph_schema());
    let app_state = std::sync::Arc::new(AppState {
        graph_schema: graph_schema.clone(),
        db: pool.clone(),
    });

    HttpServer::new(move || {
        App::new()
            .wrap(middleware::Logger::default())
            .wrap(
                Cors::new() // <- Construct CORS middleware builder
                    .allowed_origin("http://127.0.0.1:8888")
                    .allowed_methods(vec!["GET", "POST", "OPTIONS"])
                    .allowed_headers(vec![
                        http::header::AUTHORIZATION,
                        http::header::ACCEPT,
                        http::header::ACCESS_CONTROL_REQUEST_HEADERS,
                        http::header::ACCESS_CONTROL_REQUEST_METHOD,
                        http::header::ACCESS_CONTROL_ALLOW_HEADERS,
                        http::header::ACCESS_CONTROL_ALLOW_METHODS,
                        http::header::CONTENT_TYPE,
                    ])
                    .max_age(3600),
            )
            .route("/ping", web::get().to(ping))
            .service(
                web::scope("/api")
                    .data(pool.clone())
                    .service(
                        web::resource("/books")
                            .route(web::get().to_async(book_handler::list))
                            .route(web::post().to_async(book_handler::create)),
                    )
                    .service(
                        web::resource("/books/{id}")
                            .route(web::get().to_async(book_handler::get))
                            .route(web::put().to_async(book_handler::update)),
                    ),
            )
            .service(
                web::resource("/graphql")
                    .data(app_state.clone())
                    .route(web::post().to_async(graph_handler::graphql))
                    .route(web::get().to_async(graph_handler::schema)),
            )
            .service(
                web::resource("/graphiql")
                    .data(graph_schema.clone())
                    .route(web::get().to_async(graph_handler::graphiql)),
            )
    })
    .bind("127.0.0.1:8888")
    .unwrap()
    .start();

    let _ = sys.run();
}
