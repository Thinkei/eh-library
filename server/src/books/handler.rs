use crate::db::Connection;
use crate::google_json_response::{ render_errors, render_records };
use crate::models::Book;
use rocket_contrib::json::{ Json, JsonValue };
use rocket::response::status;
use super::repository;
use super::repository::InsertableBook;

#[get("/")]
pub fn list(connection: Connection) -> JsonValue {
    render_records(repository::list(&connection))
}

#[post("/", data = "<book>")]
pub fn create(book: Json<InsertableBook>, connection: Connection) -> Result<status::Created<Json<Book>>, JsonValue> {
    repository::create(book.into_inner(), &connection)
        .map(|x| status::Created(String::from("/books"), Some(Json(x))) )
        .map_err(|e| render_errors(e, String::from("422")))
}
