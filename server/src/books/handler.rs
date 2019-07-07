use crate::db::Connection;
use rocket_contrib::json;
use rocket_contrib::json::{ Json, JsonValue };
use super::repository;

#[get("/")]
pub fn list(connection: Connection) -> Json<JsonValue> {
    Json(json!(repository::list(&connection)))
}
