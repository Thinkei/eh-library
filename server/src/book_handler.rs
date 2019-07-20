use crate::errors::ServiceError;
use crate::models::{Book, Pool};
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
        Err(_) => Err(ServiceError::InternalServerError),
    })
}
#[derive(Insertable, Serialize, Deserialize)]
#[table_name = "books"]
pub struct InsertableBook {
    name: String,
}

pub fn create(
    book: web::Json<InsertableBook>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let insertable_book = book.into_inner();

        let conn: &PgConnection = &pool.get().unwrap();
        diesel::insert_into(books::table)
            .values(&insertable_book)
            .get_result(conn)
            .map_err(|_| ServiceError::InternalServerError)
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Ok().json(book)),
        Err(_) => Err(ServiceError::InternalServerError),
    })
}

#[derive(Deserialize)]
pub struct GetParams {
    id: i32,
}

pub fn get(
    params: web::Path<GetParams>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();
        books::table
            .find(params.id)
            .get_result(conn)
            .map_err(|_| ServiceError::InternalServerError)
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Ok().json(book)),
        Err(_) => Err(ServiceError::InternalServerError),
    })
}

#[derive(Deserialize)]
pub struct UpdateParams {
    id: i32,
}

pub fn update(
    params: web::Path<UpdateParams>,
    book_data: web::Json<InsertableBook>,
    pool: web::Data<Pool>,
) -> impl Future<Item = HttpResponse, Error = ServiceError> {
    web::block(move || {
        let conn: &PgConnection = &pool.get().unwrap();
        let book: Book = Book {
            id: params.id,
            name: book_data.into_inner().name,
        };

        diesel::update(books::table.find(params.id))
            .set(&book)
            .get_result(conn)
            .map_err(|_| ServiceError::InternalServerError)
    })
    .then(|res: Result<Book, BlockingError<ServiceError>>| match res {
        Ok(book) => Ok(HttpResponse::Ok().json(book)),
        Err(_) => Err(ServiceError::InternalServerError),
    })
}
