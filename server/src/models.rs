use crate::schema::books;

#[table_name = "books"]
#[derive(Serialize, Deserialize, Queryable, Insertable)]
pub struct Book {
    pub id: i32,
    pub name: String,
}
