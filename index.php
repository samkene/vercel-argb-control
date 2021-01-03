<?php 
   // $effect = $_POST['efeito'];
   // $red = $_POST['r'];
   // $green = $_POST['g'];
   // $blue = $_POST['b'];

   $effect = "fade";
   $red = 0;
   $green = 255;
   $blue = 0;
?>

<!DOCTYPE html>
<html>
   <head>
       <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.2/css/materialize.min.css">
       <script src="https://cdn.rawgit.com/giobauermeister/836975dcbe2fd05a5a2a9dcee6bcec4d/raw/49db24b1ecb60d361f3119ba7e2519f9e2b39101/iro.min.js"></script>
       <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.100.2/js/materialize.min.js"></script>
       <meta name="viewport" content="width=device-width, initial-scale=1.0">
   </head>
   <body>
       <div class="container">
           <h2 id="title" class="light center">Wemos Color Picker</h2>
           <div class="centered">
               <div id="color-picker-container"></div>
           </div>
           <div class="centered">
               <input placeholder="IP Address" id="ipAddress" type="text" class="validate" value="192.168.5.125" style="text-align: center;">            
           </div>
       </div>
       <script>           
           var xhttp = new XMLHttpRequest();        
           var demoColorPicker = new iro.ColorPicker("#color-picker-container", {
               width: 300,
               height: 300,
               color: "#5b9aff"
           });
           demoColorPicker.on("color:change", function (color, changes) {
               console.log(color.rgb);
               var ipAddress = document.getElementById("ipAddress").value;
               var url = "http://" + ipAddress + "/colordata";
               document.getElementById('title').style.color = color.hexString;                               
               xhttp.open("POST", url);
            //    var color_set = `{ "r": ${r}, "g": ${g}, "b": ${b}}`;
               xhttp.send(JSON.stringify(color.rgb));
           });
       </script>
       <style>
           .centered {
               margin: 0 auto;
               max-width: 300px;
           }
       </style>
   </body>
</html>