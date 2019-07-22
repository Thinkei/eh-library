use crate::book_repository;
use crate::models::{Book, NewBook, Pool, UpdateBook};
use diesel::PgConnection;
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

    field books(&executor) -> FieldResult<Vec<Book>> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap();

        book_repository::list(conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }
});

pub struct MutationRoot;

graphql_object!(MutationRoot: Pool |&self| {
    field create_book(&executor, book: NewBook) -> FieldResult<Book> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap();

        book_repository::create(book, conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }

    field update_book(&executor, book: UpdateBook) -> FieldResult<Book> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap();

        book_repository::update(Book {
            id: book.id,
            name: book.name
        }, &conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }
});

pub type GraphSchema = RootNode<'static, QueryRoot, MutationRoot>;

pub fn create_graph_schema() -> GraphSchema {
    GraphSchema::new(QueryRoot {}, MutationRoot {})
}
