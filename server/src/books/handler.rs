use crate::db::Connection;
use crate::google_json_response::{ render_errors, render_records, render_record };
use crate::models::Book;
use rocket_contrib::json::{ Json, JsonValue };
use rocket::response::status;
use rocket::http::Status;
use super::repository;
use super::repository::InsertableBook;

#[get("/")]
pub fn list(connection: Connection) -> Result<JsonValue, Status> {
    repository::list(&connection)
        .map(|x| render_records(x))
        .map_err(|_e| Status::InternalServerError )
}

#[post("/", format = "application/json", data = "<book>")]
pub fn create(book: Json<InsertableBook>, connection: Connection) -> Result<status::Created<JsonValue>, status::Custom<JsonValue>> {
    repository::create(book.into_inner(), &connection)
        .map(|x| status::Created(String::from("/books"), Some(render_record(x))) )
        .map_err(|e| render_errors(e, Status::UnprocessableEntity))
}

#[get("/<id>")]
pub fn get(id: i32, connection: Connection) -> Result<JsonValue, status::Custom<JsonValue>> {
    repository::get(id, &connection)
        .map(|x| render_record(x))
        .map_err(|e| render_errors(e, Status::NotFound))
}

#[put("/<id>", format = "application/json", data = "<book>")]
pub fn update(id: i32, book: Json<Book>, connection: Connection) -> Result<JsonValue, status::Custom<JsonValue>> {
    repository::update(id, book.into_inner(), &connection)
        .map(|x| render_record(x))
        .map_err(|e| render_errors(e, Status::UnprocessableEntity))
}
