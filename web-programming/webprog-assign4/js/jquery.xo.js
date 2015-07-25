(function($) {
var counter = 0;
var start_game = false;
var game_type = "";
var first_player = "human";
var who = '';
var secondMarker = 'o';

$.fn.drawBoard = function(options) {
   var square = ' ';
   var buttons = ' ', status_mes = ' ';
   var text = ' ';
   
   var settings = jQuery.extend({
         'boardCSS': { 'background-color': 'blue', width: '300px', height: '300px', margin: '20px auto' } 
   }, options);


   square +="<div id='board'><table border='1' align='center' width='270' height='270'>";
   for (var i = 0; i < 3; i++)
   {
      square += "<tr>";
      for (var j = 0; j < 3; j++)
      {
         square += "<td> <div class='square' id='sq" + (3*i + j) +"' >";
      }
      square += "</tr>";
   }
   square += "</table></div>";
   text += square;

   buttons += "<div class='button-container'>";
   buttons += "<button id='reset-button'>Reset Board</button>";
   buttons += "<button id='start-button'>Start Game</button>";
	buttons += "</div>";
   text += buttons;

   status_mes += "<p class='status-message' > Status Message </p>";
   text += status_mes;

   $(this).append(text);

   $(document).ready(function() {
   // use this to reset several forms at once
      $("div.square").each(function(i) {
         $(this).hover( function() {

            var square = "div.square#sq"+i;
            if ($(square).hasClass("clickable"))
            {
               $(square).addClass("hover");
            }
         },
         function() {
            var square = "div.square#sq"+i;
            if ($(square).hasClass("clickable"))
            {
               $(square).removeClass("hover");
            }
         });

         $(this).click(function() {
            if (game_type == "single")
            {
               $.fn.placeMarker({'position': i});
               $.fn.computerMove();
            }
            else {
               $.fn.placeMarker({'position': i});
            }
         });
      });
   });
   
   $('#start-button')
      .button()
      .click(function() {
         $('div.game-config').dialog('open');
      });
   $('#reset-button')
      .button()
      .click(function() {
            $.fn.resetBoard();
   });


   return this;
};

$.fn.gameFinish = function() {

	squares = $(document).find('div.square');
   for (var i = 0; i < 9; i++)
   {
      var img = jQuery(squares[i]);

      $(img).removeClass("clickable");
   }

   return this;
};


$.fn.resetBoard = function() {

	squares = $(document).find('div.square');
   for (var i = 0; i < 9; i++)
   {
      var img = jQuery(squares[i]);

      $(img).removeClass("clickable");
      $(img).removeClass("hover");

      if ($(img).hasClass("x"))
      {
         $(img).removeClass("x");
      }
      if ($(img).hasClass("o"))
      {
         $(img).removeClass("o");
      }
   }

   return this;
};

$.fn.disableBoard = function() {

	squares = $(document).find('div.square');

   for (var i = 0; i < 9; i++)
   {
      var img = jQuery(squares[i]);
      img.unbind('click');
      img.unbind("mouseenter");
      img.unbind("mouseleave");
   }

   return this;
};
$.fn.initGame = function(options) {

   var settings = jQuery.extend({
    'gameType': 'single', 'goFirst': true, 'firstMarker': 'x', 'secondMarker': 'o' 
   }, options);

   start_game = true;
   jQuery.fn.resetBoard();
   for (var i = 0; i < 9; i++)
   {
      var img = "div.square#sq"+i;
      $(img).addClass("clickable");
   }

   if (settings.firstMarker == 'o')
      counter++;

   if (settings.gameType == 'single')
   {
      game_type = "single";
      if (settings.goFirst == false)
      {
         first_player = "pc";
         $.fn.computerMove();
      }
   } else {
      game_type = "double";
   }

   return this;
};

$.fn.placeMarker = function(options) {

   var settings = jQuery.extend({
    'position': 0
    }, options);
   who = 'human';

   var img = "div.square#sq"+settings.position;
	var my_counter = 9 - $(document).find('div.clickable').length+counter;
   var result = false;

   if ($(img).hasClass("clickable") == true)
   {
      $(img).removeClass("clickable");
      if (!(my_counter % 2)) {
         $(img).addClass("x");
         $.fn.checkVictory({marker: "x"});
      }
      else {
         $(img).addClass("o");
         $.fn.checkVictory({marker: "o"});
      }
   }
   else {
   }

   return this;
};

$.fn.computerMove = function() {

	var my_counter = 9 - $(document).find('div.clickable').length+counter;
   var result = false;
   who = 'computer';

   for (var i = 0; i < 9; i++)
   {
      var img = "div.square#sq"+i;
      if ($(img).hasClass("clickable") === true)
      {
         $(img).removeClass("clickable");
         if (!(my_counter % 2))
         {
            $(img).addClass("x");
            result = $.fn.checkVictory({marker: "x"});
         }
         else {

            $(img).addClass("o");
            result = $.fn.checkVictory({marker: "o"});
         }
         break;
      }
   }

   return this;
};

$.fn.checkVictory = function(options) {

   var settings = jQuery.extend({
    marker: 'x'
   }, options);

   var loger = 'X';
   if (settings.marker == 'o') loger = 'O';

   // verify raw victory
   for(i = 0; i < 3; i++)
   {
      var nr = 0;
      for (j = 0; j < 3; j++)
      {
         
         var img = "div.square#sq" + (3*i + j);
         if ($(img).hasClass(settings.marker))
            nr++;
      }
      if (nr === 3)
      {
         if (game_type == 'single') $.fn.logWinner({winner: who});
         $('.status-message').text(loger + ' wins!');
         $.fn.gameFinish();
         return true;
      }
   }

   // verify column victory
   for(i = 0; i < 3; i++)
   {
      var nr = 0;
      for (j = 0; j < 3; j++)
      {
         
         var img = "div.square#sq" + (3*j + i);
         if ($(img).hasClass(settings.marker))
            nr++;
      }
      if (nr === 3)
      {
         if (game_type == 'single') $.fn.logWinner({winner: who});
         $('.status-message').text(loger + ' wins!');
         $.fn.gameFinish();
         return true;
      }
   }

   // verify diagonals victory
   var nr1 = 0, nr2 = 0;

   for(i = 0; i < 3; i++)
   {
         var img1 = "div.square#sq" + (4*i);
         var img2 = "div.square#sq" + (2*(i+1));
         if ($(img1).hasClass(settings.marker))
            nr1++;
         if ($(img2).hasClass(settings.marker))
            nr2++;
         if ((nr1 === 3) || (nr2 === 3))
         {
            
            if (game_type == 'single') $.fn.logWinner({winner: who});
            $('.status-message').text(loger + ' wins!');
            $.fn.gameFinish();
            return true;
         }
   }

   my_counter = 9 - $(document).find('div.clickable').length;
   if (my_counter == 9)
   {
      $('.status-message').text('Draw game!');
      return true;
   }

   return false;
};

$.fn.logWinner = function(options) {

   var settings = jQuery.extend({
    winner: 'human'
   }, options);

   var my_data = '{"winner" : "' + settings.winner + '"}';
   
   $.post(
    "ajax/log.php", //Ajax file
    {winner: settings.winner}, // create an object will all values
    //my_data,  // create an object will all values
    //function that is called when server returns a value.
    function(data){
      $.cookie(settings.winner,data.value);
    },
    //How you want the data formated when it is returned from the server.
    "json"
    );

   return this;
};

$.fn.resetScore = function() {

   $.post("ajax/log.php", {"reset": true} , function(data) { }, "text");
   $.cookie("human", null);
   $.cookie("computer", null);
   return this;
};

}) (jQuery);
