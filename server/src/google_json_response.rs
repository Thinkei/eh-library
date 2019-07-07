use diesel;
use serde::ser::Serialize;
use rocket_contrib::json;
use rocket_contrib::json::{  JsonValue };

pub fn render_errors(err: diesel::result::Error, code: String) -> JsonValue {
    json!({
        "error": {
            "code": code,
            "message": err.to_string()
        }
    })
}

pub fn render_records<T: Serialize>(records: Vec<T>) -> JsonValue {
    json!({
        "data": {
            "items": records,
            "total_items": records.len()
        }
    })
}
