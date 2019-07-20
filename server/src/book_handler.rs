use crate::errors::ServiceError;
use crate::models::{Book, Pool};
use crate::schema;
use actix_web::{web, HttpResponse};
use diesel::{self, prelude::*};
use futures::Future;

pub fn list(pool: web::Data<Pool>) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();

        schema::books::table
            .order(schema::books::id.desc())
            .load::<Book>(conn)
            .map_err(|_| ServiceError::InternalServerError)
    })
    .then(|res| match res {
        Ok(books) => Ok(HttpResponse::Ok().json(books)),
        Err(_) => Err(ServiceError::InternalServerError),
    })
}
