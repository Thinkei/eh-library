use diesel;
use serde::ser::Serialize;
use rocket_contrib::json;
use rocket_contrib::json::JsonValue;
use rocket::http::Status;
use rocket::response::status::Custom;

pub fn render_errors(err: diesel::result::Error, status: Status) -> Custom<JsonValue> {
    Custom(
        status,
        json!({
            "error": {
                "code": status.code,
                "message": err.to_string()
            }
        })
    )
}

pub fn render_records<T: Serialize>(records: Vec<T>) -> JsonValue {
    json!({
        "data": {
            "items": records,
            "total_items": records.len()
        }
    })
}
