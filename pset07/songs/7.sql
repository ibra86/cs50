-- In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.
select avg(energy)
from songs, artists
where songs.artist_id = artists.id
and artists.name = 'Drake'
;