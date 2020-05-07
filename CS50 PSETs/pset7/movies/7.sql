SELECT movies.title, ratings.rating
FROM movies JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010 and rating IS NOT NULL
ORDER BY ratings.rating DESC, movies.title ASC