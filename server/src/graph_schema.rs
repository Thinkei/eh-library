use crate::models::{Book, Pool};
use crate::schema::books;
use diesel::PgConnection;
use diesel::{self, prelude::*};
use juniper::FieldError;
use juniper::FieldResult;
use juniper::RootNode;

#[derive(GraphQLInputObject)]
#[graphql(description = "NewBook model")]
struct NewBook {
    name: String,
}

pub struct QueryRoot;

graphql_object!(QueryRoot: Pool |&self| {
    field book(&executor, id: i32) -> FieldResult<Book> {
        let conn: &PgConnection = &executor.context()
            .get()
            .unwrap() ;

        books::table
            .find(id)
            .get_result(conn)
            .map_err(|err| FieldError::new(err, juniper::Value::null()))
    }
});

pub struct MutationRoot;

graphql_object!(MutationRoot: Pool |&self| {
    field createBook(&executor, new_book: NewBook) -> FieldResult<Book> {
        Ok(
            Book {
                id: 0,
                name: new_book.name
            }
        )
    }
});

pub type GraphSchema = RootNode<'static, QueryRoot, MutationRoot>;

pub fn create_graph_schema() -> GraphSchema {
    GraphSchema::new(QueryRoot {}, MutationRoot {})
}
