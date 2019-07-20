use crate::errors::ServiceError;
use crate::models::{Book, Pool};
use crate::schema;
use actix_web::{web, HttpResponse};
use diesel::{self, prelude::*};
use futures::Future;

pub fn get_books(pool: web::Data<Pool>) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || query(pool)).then(|res| match res {
        Ok(books) => Ok(HttpResponse::Ok().json(books)),
        Err(_) => Err(ServiceError::InternalServerError),
    })
}

fn query(pool: web::Data<Pool>) -> Result<Vec<Book>, ServiceError> {
    let conn: &PgConnection = &pool.get().unwrap();

    schema::books::table
        .order(schema::books::id.desc())
        .load::<Book>(conn)
        .map_err(|_| ServiceError::InternalServerError)
}
