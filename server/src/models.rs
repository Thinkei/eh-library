use crate::schema::books;

#[table_name = "books"]
#[derive(Serialize, Deserialize, Queryable, AsChangeset)]
pub struct Book {
    pub id: i32,
    pub name: String,
}
