

$(document).ready(function() {
      
  	$("select[name='players']").change(function() {
		if ($("select[name='players']").val() == "single") {
			$("fieldset.extra").css("display", "inline");
		} else {
			$("fieldset.extra").css("display", "none");
		}
	});
                
   $("div.game-config").dialog({
      autoOpen: false,
      height: 400,
      width: 350,
      modal: true,
      buttons: {
         'Start Game': function() {
               //players = players.val();

            var players = $("select[name='players']"), starter = '', marker = '';
            //"#numeid", ".class"
               
               if (players.val().length > 1) 
               {
                 if (players.val() == "single")
                 {
                        /* do something here */ 
                       // $("fieldset.extra").css("display", "inline");
                        //$(this).reload();
                       // });
                  
                        starter = $("select[name=starter]");
                        marker = $("select[name=marker]");

                     if (starter.val().length > 1 && marker.val().length >= 1) 
                     {
                        var goFirst = false, firstMarker='x', secondMarker='o';

                        if (starter.val() == "human")
                           goFirst = true;
                        if (marker.val() == 'o')
                        {
                           firstMarker='o';
                           secondMarker='x';
                        }
                        
				            $('#board').initGame({ 'gameType': 'single', 'goFirst': goFirst, 'firstMarker': firstMarker, 'secondMarker': secondMarker })
                        $(this).dialog('close');
                     }
                 }
                 else 
                 {
				            $('#board').initGame({'gameType': 'double'})
                        $(this).dialog('close');
                 }

               }
               
         },
         'Cancel': function() {
            $(this).dialog('close');
         }
      },
   });
});
