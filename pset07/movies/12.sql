-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.
with t1 as (
select * from stars where person_id in ( select id from people where name  = 'Johnny Depp')
),
t2 as (
select * from stars where person_id in ( select id from people where name  =  'Helena Bonham Carter')),
t12 as (
select distinct t1.movie_id
from t1,t2
where t1.movie_id = t2.movie_id
)
select title
from movies
where id in (select movie_id from t12)
;