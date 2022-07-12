-- In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
select name
from songs
where artist_id = (select id from artists where name = 'Post Malone')
;