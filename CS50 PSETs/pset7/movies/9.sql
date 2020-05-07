SELECT name
FROM people WHERE id IN (
SELECT person_id FROM stars WHERE movie_id IN
(SELECT stars.movie_id
FROM people JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004))