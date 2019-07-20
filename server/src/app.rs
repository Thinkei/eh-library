use crate::db::DbExecutor;
use actix::prelude::*;

pub struct AppState {
    pub db: Addr<DbExecutor>,
}
