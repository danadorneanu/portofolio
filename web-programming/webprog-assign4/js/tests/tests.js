	function allTests(board) {

		// ================================================================ //
		module('DOM');
		
		test('Draw board', function () {
			board.drawBoard();
			
			// test if the nine squares were successfully created
			var noOfSquares = (board.find('div.square')).length;
			equals(noOfSquares, 9, 'There should be 9 squares');
			
			var noOfButtons = ($('.button-container').find('button')).length;
			equals(noOfButtons, 2, 'There should be two buttons');
			
			ok(($('button#reset-button').length > 0), 'Reset button ok');
			ok(($('button#start-button').length > 0), 'Start button ok');
			ok(($('button#start-button').length > 0), 'Start button ok');
		});
		
		
		test('Reset method and chainability', function () {
			board.initGame({gameType: 'double'}).placeMarker({position: 0}).resetBoard();
			
			var target = board.find('div.square').eq(0);
			ok(!target.hasClass('x'), 'Methods are chainable');
		});
		
		
		test('Each square is clickable when the game is started', function () {
			var squares = board.find('div.square');
			var clicks = [], hovers = [], blurs = [];
			
			board.initGame({gameType: 'double'});
			for (var i = 0; i < 9; i = i + 1) { 
				clicks[i] = $.data(squares[i], 'events') && $.data(squares[i], 'events').click;
				hovers[i] = $.data(squares[i], 'events') && $.data(squares[i], 'events').mouseenter;
				blurs[i] = $.data(squares[i], 'events') && $.data(squares[i], 'events').mouseleave;
				
				ok(clicks[i], 'Square ' + i + ' does have a click event attached');
				ok(hovers[i], 'Square ' + i + ' does have a mouseenter event attached');
				ok(blurs[i], 'Square ' + i + ' does have a mouseleave event attached');
			}
		});

		test('No events exist when the board is disabled', function () {
			var squares = board.find('div.square');
			var clicks = [], hovers = [], blurs = [];
			
			board.disableBoard();
			squares = board.find('div.square');
			for (var i = 0; i < 9; i = i + 1) { 
				clicks[i] = $.data(squares[i], 'events') && $.data(squares[i], 'events').click;
				hovers[i] = $.data(squares[i], 'events') && $.data(hovers[i], 'events').mouseenter;
				blurs[i] = $.data(squares[i], 'events') && $.data(squares[i], 'events').mouseleave;
				
				ok(!clicks[i], 'Square ' + i + ' does not have a click event attached');
				ok(!hovers[i], 'Square ' + i + ' does not have a hover event attached');
				ok(!blurs[i], 'Square ' + i + ' does not have a hover event attached');
			}
			
		});
		
		
		// ================================================================ //	
		module('Marking');
		test('Place a marker', function () {
			board.initGame({gameType: 'double'});
			board.placeMarker({ position : 0 });
			
			var target = board.find('div.square').eq(0);
			ok(target.hasClass('x'), 'The element has been marked');
			
			board.resetBoard();
		});
		
		test('Place two markers in sequence', function () {
			board.initGame({gameType: 'double'});
			board.placeMarker({ position : 0 });

			var target = board.find('div.square').eq(0);
			ok(target.hasClass('x'), 'First player moved');

			board.placeMarker({ position : 1 });
			target = board.find('div.square').eq(1);
			ok(target.hasClass('o'), 'Second player moved');

			board.resetBoard();
		});
		
		test('Place over the same square', function () {
			board.initGame({gameType: 'double'});
			board.placeMarker({ position : 0 });
			board.placeMarker({ position : 0 });
			
			var target = board.find('div.square').eq(0);
			ok(!target.hasClass('o'), 'Retained first move');
			
			board.placeMarker({ position : 1 });
			target = board.find('div.square').eq(1);
			ok(target.hasClass('o'), 'Redid second move ok');
			
			board.resetBoard();
		});
		
		test('Fill the board', function () {
			expect(4);
			board.initGame({gameType: 'double'});
			
			board	.placeMarker({ position : 1 })
					.placeMarker({ position : 0 })
					.placeMarker({ position : 2 })
					.placeMarker({ position : 4 })
					.placeMarker({ position : 3 })
					.placeMarker({ position : 5 })
					.placeMarker({ position : 7 })
					.placeMarker({ position : 6 })
					.placeMarker({ position : 8 });
			
			board.placeMarker({ position : 1 });
			var target = board.find('div.square').eq(1);
			ok(target.hasClass('x'), 'Board does not support any more clicks');
			
			board.placeMarker({ position : 2 });
			target = board.find('div.square').eq(2);
			ok(target.hasClass('x'), 'Board does not support any more clicks');
			
			equals($('.status-message').text(), 'Draw game!', 'Board filled with draw game');
			
			board.resetBoard();
			board.initGame({gameType: 'double'});
			
			board	.placeMarker({ position : 1 })
					.placeMarker({ position : 0 })
					.placeMarker({ position : 2 })
					.placeMarker({ position : 3 })
					.placeMarker({ position : 4 })
					.placeMarker({ position : 5 })
					.placeMarker({ position : 8 })
					.placeMarker({ position : 7 })
					.placeMarker({ position : 6 });
					
			equals($('.status-message').text(), 'X wins!', 'Board filled with winner');
			
			board.resetBoard();
		});
		
		module('Victory conditions');	
		test('Status updates', function () {
			board.initGame({gameType: 'double'});
			
			board	.placeMarker({ position : 0 })
					.placeMarker({ position : 3 })
					.placeMarker({ position : 1 })
					.placeMarker({ position : 4 })
					.placeMarker({ position : 2 });
					
			equals($('.status-message').text(), 'X wins!', 'Status updated correctly when X wins');
			
			board.resetBoard();
			board.initGame({gameType: 'double'});
			
			board	.placeMarker({ position : 1 })
					.placeMarker({ position : 6 })
					.placeMarker({ position : 0 })
					.placeMarker({ position : 7 })
					.placeMarker({ position : 3 })
					.placeMarker({ position : 8 });
			
			equals($('.status-message').text(), 'O wins!', 'Status updated correctly after O wins');
			
			board	.placeMarker({ position : 2 });
			var target = board.find('div.square').eq(2);
			ok(!target.hasClass('x'), 'No more moves can be made after after victory');
			board.resetBoard();	
		});
		
		test('Victory behavior', function () {
			// TODO: victory test cases
		});
		
		
		// ================================================================ //
		module('Computer');
		test('Move first', function () {
			board.initGame({gameType: 'single', goFirst: false});
			var target = board.find('div.x');
			
			ok(target.hasClass('x'), 'With X marker');
			board.resetBoard();
			
			board.initGame({gameType: 'single', goFirst: false, firstMarker: 'o', secondMarker: 'x'});
			target = board.find('div.o');
			
			ok(target.hasClass('o'), 'With O marker');
			board.resetBoard();
		});
		
		test('Full game', function () {
			var gameOverStatus = ['X wins!', 'O wins!', 'Draw game!'];
			board.resetBoard().initGame({gameType: 'single', goFirst: false});
			var squares, rand, prevLength;
			
			squares = board.find('div.clickable');
			prevLength = squares.length;
			
			while (squares.length) {
				rand = Math.floor(Math.random(squares.length));
				
				// if it has the click event attached (i.e. the board is not disabled)
				if ($.data(squares[rand], 'events') && $.data(squares[rand], 'events').click) {
					board.placeMarker({ position: squares.eq(rand).attr('id').replace('sq', '')});
					squares = board.find('div.clickable');
				
					if (squares.length === prevLength) {
						// going into an infinite loop
						break;
					}
					prevLength = squares.length;
				} else {
					break;
				}
			}
			
			ok(($.inArray($('.status-message').text(), gameOverStatus) !== -1), 'The game ended ok');
		});
		
		// ================================================================ //
		module('Logging');
		asyncTest('Reset scores', function () {
			board.resetScore();
			setTimeout(function () {
				ok(!($.cookie('human') || $.cookie('computer')), 'Reset scores');
				start();
			}, 500);
		});
		
		asyncTest('Log first', function () {	
			board.logWinner({winner : 'human'});
			
			setTimeout(function () {
				equals($.cookie('human'), 1, 'Win logged');
				ok(!($.cookie('computer')), 'Loss not logged');
				start();
			}, 300);
		});
			
		asyncTest('Log second', function () {
			board.logWinner({winner : 'computer'});
			
			setTimeout(function () {
				equals($.cookie('human'), 1, 'Value not changed');
				equals($.cookie('computer'), 1, 'Win logged');			
				start();
			}, 300);
		});
		
		asyncTest('Reset scores', function () {
			board.resetScore();
			setTimeout(function () {
				ok(!($.cookie('human') || $.cookie('computer')), 'Reset scores');
				start();
			}, 500);
		});
		
		asyncTest('After-game logging', function () {
			var gameOverStatus = ['X wins!', 'O wins!', 'Draw game!'];
			board.resetBoard().initGame({gameType: 'single', goFirst: false});
			var squares = board.find('div.clickable');
			var rand, prevLength;
			var toCheck;
			
			while (squares.length) {
				rand = Math.floor(Math.random(squares.length));
				
				// if it has the click event attached (i.e. the board is not disabled)
				if ($.data(squares[rand], 'events') && $.data(squares[rand], 'events').click) {
					board.placeMarker({ position: squares.eq(rand).attr('id').replace('sq', '')});
					squares = board.find('div.clickable');
				
					if (squares.length === prevLength) {
						// going into an infinite loop
						break;
					}
					prevLength = squares.length;
				} else {
					break;
				}
			}
			
			ok(($.inArray($('.status-message').text(), gameOverStatus) !== -1), 'The game ended ok');
			switch ($('.status-message').text()) {
				case 'O wins!':
					toCheck = $.cookie('human');
					break;
				case 'X wins!':
					toCheck = $.cookie('computer');
					break;
				default:
					// do nada;
					break;
			}
			
			start();
			ok(true, 'Winner logged after game complete');
		});
	}
