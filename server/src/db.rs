use actix::{Actor, SyncContext};
use diesel::r2d2::{ConnectionManager, Pool};
use diesel::PgConnection;

pub struct DbExecutor(pub Pool<ConnectionManager<PgConnection>>);

impl Actor for DbExecutor {
    type Context = SyncContext<Self>;
}
