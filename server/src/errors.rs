use actix_web::{error::ResponseError, HttpResponse};
use derive_more::Display;
use diesel::result::{DatabaseErrorKind, Error};
use std::convert::From;

#[derive(Debug, Display)]
pub enum ServiceError {
    #[display(fmt = "Internal Server Error")]
    InternalServerError,

    #[display(fmt = "BadRequest: {}", _0)]
    BadRequest(String),

    #[display(fmt = "Unprocessable Entity")]
    UnprocessableEntity,

    #[display(fmt = "Record not found")]
    NotFound(String),

    #[display(fmt = "Unauthorized")]
    Unauthorized,

    #[display(fmt = "EmailExisted")]
    EmailExisted,
}

pub const EMAIL_EXISTED: &str = "Email is existed";

impl ResponseError for ServiceError {
    fn error_response(&self) -> HttpResponse {
        match self {
            ServiceError::InternalServerError => {
                HttpResponse::InternalServerError().json("Internal Server Error, Please try later")
            }
            ServiceError::BadRequest(ref message) => HttpResponse::BadRequest().json(message),
            ServiceError::EmailExisted => HttpResponse::BadRequest().json(EMAIL_EXISTED),
            ServiceError::UnprocessableEntity => {
                HttpResponse::UnprocessableEntity().json("Unprocessable Entity")
            }
            ServiceError::NotFound(ref message) => HttpResponse::NotFound().json(message),
            ServiceError::Unauthorized => HttpResponse::Unauthorized().json("Unauthorized"),
        }
    }
}

impl From<Error> for ServiceError {
    fn from(error: Error) -> ServiceError {
        match error {
            Error::DatabaseError(kind, info) => {
                if let DatabaseErrorKind::UniqueViolation = kind {
                    let message = info.details().unwrap_or_else(|| info.message()).to_string();
                    return ServiceError::BadRequest(message);
                }
                ServiceError::InternalServerError
            }
            _ => ServiceError::InternalServerError,
        }
    }
}
