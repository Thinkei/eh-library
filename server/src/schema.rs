table! {
    books (id) {
        id -> Int4,
        name -> Varchar,
    }
}

table! {
    users (id) {
        id -> Int4,
        email -> Varchar,
        encrypted_password -> Varchar,
        salt -> Bytea,
        is_admin -> Bool,
        created_at -> Timestamp,
    }
}

allow_tables_to_appear_in_same_query!(
    books,
    users,
);
