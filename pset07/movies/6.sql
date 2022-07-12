-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
-- Your query should output a table with a single column and a single row (not counting the header) containing the average rating.
select avg(rating)
from ratings
where movie_id in (select id from movies where year = 2012)
;