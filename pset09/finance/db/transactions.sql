create table transactions
( id integer primary key autoincrement ,
user_id integer not null,
symbol text not null,
name text not null,
shares integer default 0 not null,
price numeric not null,
effective_at DATETIME DEFAULT CURRENT_TIMESTAMP,
FOREIGN KEY(user_id) REFERENCES users(id)
)
;