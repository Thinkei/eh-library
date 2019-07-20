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

graphql_object!(QueryRoot: () |&self| {
    field book(&executor, id: i32) -> FieldResult<Book> {
        Ok(
            Book {
                id: id,
                name: "hehe".to_string()
            }
        )
    }
});

pub struct MutationRoot;

graphql_object!(MutationRoot: () |&self| {
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
