{"filter":false,"title":"9.sql","tooltip":"/pset7/movies/9.sql","undoManager":{"mark":3,"position":3,"stack":[[{"start":{"row":0,"column":0},"end":{"row":4,"column":21},"action":"insert","lines":["SELECT DISTINCT people.name","FROM people JOIN stars ON people.id = stars.person_id","JOIN movies on stars.movie_id = movies.id","WHERE movies.year = 2004","ORDER BY people.birth"],"id":1}],[{"start":{"row":0,"column":0},"end":{"row":4,"column":21},"action":"remove","lines":["SELECT DISTINCT people.name","FROM people JOIN stars ON people.id = stars.person_id","JOIN movies on stars.movie_id = movies.id","WHERE movies.year = 2004","ORDER BY people.birth"],"id":2},{"start":{"row":0,"column":0},"end":{"row":6,"column":26},"action":"insert","lines":["SELECT COUNT(name)","FROM people WHERE id IN (","SELECT person_id FROM stars WHERE movie_id IN","(SELECT stars.movie_id","FROM people JOIN stars ON people.id = stars.person_id","JOIN movies ON stars.movie_id = movies.id","WHERE movies.year = 2004))"]}],[{"start":{"row":0,"column":7},"end":{"row":0,"column":13},"action":"remove","lines":["COUNT("],"id":3}],[{"start":{"row":0,"column":11},"end":{"row":0,"column":12},"action":"remove","lines":[")"],"id":4}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":6,"column":26},"end":{"row":6,"column":26},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1586250247583,"hash":"9e2eee358fd3c16c4dd5fea85fdf46b58429ba17"}