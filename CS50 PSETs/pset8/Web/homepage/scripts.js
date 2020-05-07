let body = document.querySelector('body');
            document.querySelector('#light').onclick = function() {
                body.style.backgroundColor = '#f1f1f1';
                document.getElementById("head").style.color = "#454545";
                document.getElementById("sub_head").style.color = "#454545";

            }
            document.querySelector('#dark').onclick = function() {
                body.style.backgroundColor = '#454545';
                document.getElementById("head").style.color = "#f1f1f1";
                document.getElementById("sub_head").style.color = "#f1f1f1";

            }
            
