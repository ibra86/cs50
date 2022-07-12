-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.
select p.name
from people as p
join stars as s
on p.id = s.person_id
join movies as m
on s.movie_id = m.id
where m.title='Toy Story'
;