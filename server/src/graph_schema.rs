use crate::models::{self, Pool};
use diesel::PgConnection;
use diesel::{self, prelude::*};
use juniper::FieldError;
use juniper::FieldResult;
use juniper::RootNode;

#[derive(GraphQLObject)]
#[graphql(description = "Book model")]
struct Book {
    id: i32,
    name: String,
}

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
        use crate::schema::books;
        books::table
            .find(id)
            .get_result(conn)
            .map (|x: models::Book| Book { id: x.id, name: x.name })
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
