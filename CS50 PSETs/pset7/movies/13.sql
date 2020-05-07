SELECT name
FROM people WHERE NOT name = "Kevin Bacon" AND id IN (
SELECT person_id FROM stars WHERE movie_id IN
(SELECT stars.movie_id
FROM people JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958))