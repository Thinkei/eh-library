use crate::book_repository;
use crate::errors::ServiceError;
use crate::models::{Book, NewBook, Pool};
use crate::schema::*;
use actix_web::{error::BlockingError, web, HttpResponse};
use diesel::{self, prelude::*};
use futures::Future;

pub fn list(pool: web::Data<Pool>) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();

        books::table
            .order(books::id.desc())
            .load::<Book>(conn)
            .map_err(|_| ServiceError::InternalServerError)
    })
    .then(|res| match res {
        Ok(books) => Ok(HttpResponse::Ok().json(books)),
        Err(err) => match err {
            BlockingError::Error(service_error) => Err(service_error),
            BlockingError::Canceled => Err(ServiceError::InternalServerError),
        },
    })
}
pub fn create(
    new_book: web::Json<NewBook>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();
        book_repository::create(new_book.into_inner(), conn)
            .map_err(|_| ServiceError::UnprocessableEntity)
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Created().json(book)),
        Err(err) => match err {
            BlockingError::Error(service_error) => Err(service_error),
            BlockingError::Canceled => Err(ServiceError::InternalServerError),
        },
    })
}

pub fn get(
    id: web::Path<i32>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();
        book_repository::get(id.into_inner(), conn)
            .map_err(|_| ServiceError::NotFound("Book not found".to_string()))
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Ok().json(book)),
        Err(err) => match err {
            BlockingError::Error(service_error) => Err(service_error),
            BlockingError::Canceled => Err(ServiceError::InternalServerError),
        },
    })
}

pub fn update(
    id: web::Path<i32>,
    book_data: web::Json<NewBook>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();
        let book: Book = Book {
            id: id.into_inner(),
            name: book_data.into_inner().name,
        };

        diesel::update(books::table.find(book.id))
            .set(&book)
            .get_result(conn)
            .map_err(|_| ServiceError::UnprocessableEntity)
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Ok().json(book)),
        Err(err) => match err {
            BlockingError::Error(service_error) => Err(service_error),
            BlockingError::Canceled => Err(ServiceError::InternalServerError),
        },
    })
}
