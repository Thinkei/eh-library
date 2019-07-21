use crate::book_repository;
use crate::models::{Book, NewBook, Pool};
use crate::schema::books;
use diesel::PgConnection;
use diesel::{self, prelude::*};
use juniper::FieldError;
use juniper::FieldResult;
use juniper::RootNode;

pub struct QueryRoot;

graphql_object!(QueryRoot: Pool |&self| {
    field book(&executor, id: i32) -> FieldResult<Book> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap();

        book_repository::get(id, conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }
});

pub struct MutationRoot;

graphql_object!(MutationRoot: Pool |&self| {
    field createBook(&executor, new_book: NewBook) -> FieldResult<Book> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap();

        book_repository::create(new_book, conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }
});

pub type GraphSchema = RootNode<'static, QueryRoot, MutationRoot>;

pub fn create_graph_schema() -> GraphSchema {
    GraphSchema::new(QueryRoot {}, MutationRoot {})
}
