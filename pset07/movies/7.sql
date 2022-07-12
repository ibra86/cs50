-- In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating.
-- For movies with the same rating, order them alphabetically by title.
-- Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- Movies that do not have ratings should not be included in the result.
select m.title, r.rating
from movies as m, ratings as r
where m.id = r.movie_id
and m.year = 2010
and r.rating is not null
order by 2 desc, 1
;