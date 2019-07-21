use crate::graph_schema::GraphSchema;
use actix_web::{http, web, Error, HttpResponse};
use futures::Future;
use juniper::http::graphiql::graphiql_source;
use juniper::http::GraphQLRequest;
use std::sync::Arc;

pub fn graphiql() -> HttpResponse {
    let html = graphiql_source("http://127.0.0.1:8888/graphql");
    HttpResponse::Ok()
        .header(
            http::header::ACCESS_CONTROL_ALLOW_ORIGIN,
            "localhost, 127.0.0.1",
        )
        .content_type("text/html; charset=utf-8")
        .body(html)
}

pub fn graphql(
    st: web::Data<Arc<GraphSchema>>,
    data: web::Json<GraphQLRequest>,
) -> impl Future<Item = HttpResponse, Error = Error> {
    web::block(move || {
        let res = data.execute(&st, &());
        Ok::<_, serde_json::error::Error>(serde_json::to_string(&res)?)
    })
    .map_err(Error::from)
    .and_then(|user| {
        Ok(HttpResponse::Ok()
            .content_type("application/json")
            .body(user))
    })
}
