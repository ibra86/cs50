-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.
-- If a person directed more than one movie that received a rating of at least 9.0, they should only appear in your results once.
select distinct p.name
from people as p
join directors as d
on p.id = d.person_id
join ratings as r
on d.movie_id = r.movie_id
where r.rating >= 9
;
