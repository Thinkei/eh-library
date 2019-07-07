use diesel;
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
