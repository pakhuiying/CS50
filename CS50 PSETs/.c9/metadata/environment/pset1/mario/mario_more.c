{"filter":false,"title":"mario_more.c","tooltip":"/pset1/mario/mario_more.c","undoManager":{"mark":7,"position":7,"stack":[[{"start":{"row":0,"column":0},"end":{"row":40,"column":0},"action":"insert","lines":["#include <cs50.h>","#include <stdio.h>","","int main(void)","{"," int line;","    int n;","","    do","    {","        n = get_int(\"Height: \");","    }","    while (n < 1||n>8);","","for (line = 1; line <=n; line++)","{","    int column;","    int dots=n-line;  ","","          for (column = dots; column >0; column=column-1)","        {  ","            printf(\" \");","        }","","           for (column = 0; column < line; column++)","        {  ","            printf(\"#\");","        }"," ","            printf(\"..\");"," ","           for (column = 0; column < line; column++)","        {  ","            printf(\"#\");","        }","","            printf(\"\\n\"); ","","        }","}",""],"id":1}],[{"start":{"row":17,"column":20},"end":{"row":17,"column":22},"action":"remove","lines":["  "],"id":2},{"start":{"row":20,"column":9},"end":{"row":20,"column":11},"action":"remove","lines":["  "]},{"start":{"row":25,"column":9},"end":{"row":25,"column":11},"action":"remove","lines":["  "]},{"start":{"row":28,"column":0},"end":{"row":28,"column":1},"action":"remove","lines":[" "]},{"start":{"row":30,"column":0},"end":{"row":30,"column":1},"action":"remove","lines":[" "]},{"start":{"row":32,"column":9},"end":{"row":32,"column":11},"action":"remove","lines":["  "]},{"start":{"row":36,"column":25},"end":{"row":36,"column":26},"action":"remove","lines":[" "]}],[{"start":{"row":29,"column":21},"end":{"row":29,"column":22},"action":"remove","lines":["."],"id":3},{"start":{"row":29,"column":20},"end":{"row":29,"column":21},"action":"remove","lines":["."]}],[{"start":{"row":29,"column":20},"end":{"row":29,"column":21},"action":"insert","lines":[" "],"id":4}],[{"start":{"row":29,"column":20},"end":{"row":29,"column":21},"action":"remove","lines":[" "],"id":5},{"start":{"row":29,"column":20},"end":{"row":29,"column":22},"action":"insert","lines":[". "]}],[{"start":{"row":29,"column":21},"end":{"row":29,"column":22},"action":"remove","lines":[" "],"id":6},{"start":{"row":29,"column":20},"end":{"row":29,"column":21},"action":"remove","lines":["."]}],[{"start":{"row":29,"column":20},"end":{"row":29,"column":21},"action":"insert","lines":[" "],"id":7}],[{"start":{"row":29,"column":21},"end":{"row":29,"column":22},"action":"insert","lines":[" "],"id":8}]]},"ace":{"folds":[],"scrolltop":428,"scrollleft":0,"selection":{"start":{"row":29,"column":22},"end":{"row":29,"column":22},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":25,"state":"start","mode":"ace/mode/c_cpp"}},"timestamp":1588838526293,"hash":"929f71866f1234814d8a466f303a42b470085def"}