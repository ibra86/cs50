-- In 8.sql, write a SQL query that lists the names of the songs that feature other artists.
-- Songs that feature other artists will include “feat.” in the name of the song.

select name
from songs
where name like '%feat%'
;
