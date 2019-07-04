# Book Tracking Backend

## Setup 

* Follow Rust installation [here](https://www.rust-lang.org/tools/install) 
* Install nightly version [here](https://github.com/rust-lang/rustup.rs/blob/master/README.md#working-with-nightly-rust)
* Install Diesel CLI
``` 
$ cargo install diesel_cli --no-default-features --features postgres 
``` 
* Migration 
``` 
$ diesel migration run 
``` 
* Start server 
``` 
$ cd server && cargo run 
```
