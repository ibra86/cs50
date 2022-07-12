-- In 1.sql, write a SQL query to list the titles of all movies released in 2008.
-- Your query should output a table with a single column for the title of each movie.
select title
from movies
where year = 2008
;