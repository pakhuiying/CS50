{"filter":false,"title":"collapsible.js","tooltip":"/pset8/homepage/collapsible.js","ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":13,"column":13},"end":{"row":13,"column":13},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":31,"mode":"ace/mode/javascript"}},"hash":"9da3935e3bac4f00a2d8575333538a96802e7b3a","undoManager":{"mark":0,"position":0,"stack":[[{"start":{"row":0,"column":0},"end":{"row":13,"column":13},"action":"insert","lines":["var coll = document.getElementsByClassName(\"collapsible\");","            var i;","","            for (i = 0; i < coll.length; i++) {","              coll[i].addEventListener(\"click\", function() {","                this.classList.toggle(\"active\");","                var content = this.nextElementSibling;","                if (content.style.maxHeight){","                  content.style.maxHeight = null;","                } else {","                  content.style.maxHeight = content.scrollHeight + \"px\";","                }","              });","            }"],"id":1}]]},"timestamp":1588602928460}