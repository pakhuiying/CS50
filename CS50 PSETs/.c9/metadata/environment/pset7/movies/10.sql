{"filter":false,"title":"10.sql","tooltip":"/pset7/movies/10.sql","undoManager":{"mark":0,"position":0,"stack":[[{"start":{"row":0,"column":0},"end":{"row":4,"column":26},"action":"insert","lines":["SELECT DISTINCT people.name","FROM people JOIN directors ON people.id = directors.person_id","JOIN movies ON directors.movie_id = movies.id","JOIN ratings ON movies.id = ratings.movie_id","WHERE ratings.rating >=9.0"],"id":1}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":0,"column":0},"end":{"row":4,"column":26},"isBackwards":true},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1586181128960,"hash":"9b7680ed95c03b916717e3c0ed4f377ae324ad91"}