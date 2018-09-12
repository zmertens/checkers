// @author zmertens
// @brief A checkers game for HTML5, js13k game jam (13kb file size compressed)
// The paradigm or pattern we use in this game is
// about trying to come up with a sense of a 'finite search pattern',
// or total number of searches that will be needed to complete the game.
// We start by allocating bins where the search results should end up.

// Some drawing routines come from 'HTML5 Canvas Cookbook: RAW'

// Wrap game in anonymous inline function


// Configuration values
var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d'),
    xOffset = 0, yOffset = 0,
    // Canvas width and height = 800, and we want an 8x8 checkerboard
    CHECKER_WIDTH = 100, CHECKER_HEIGHT = 100;

// var p1 = new Player(), p2 = new Player();

// Game loop, ends when one team goes broke (loses all its players)

document.addEventListener( 'mousedown', onDocumentMouseDown, false );
// document.addEventListener( 'touchstart', onDocumentTouchStart, false );
// document.addEventListener( 'touchmove', onDocumentTouchMove, false );
// document.addEventListener( 'keypress', onDocumentKeyPress, false );
// document.addEventListener( 'keydown', onDocumentKeyDown, false );

// create the checkerboard
for(var i = 0; i < canvas.width; ++i, xOffset += CHECKER_WIDTH) {
    yOffset = 0;
    for(var j = 0; j < canvas.height; ++j, yOffset += CHECKER_HEIGHT) {

        if(j % 2 === 0 && i % 2 !== 0) {
            context.save();
            context.fillStyle = 'black';
            context.fillRect(xOffset, yOffset, CHECKER_WIDTH, CHECKER_HEIGHT);
            context.restore();

            if(j === 0 || j === 2) {
                context.save();
                // create the checkers
                context.beginPath();
                // centerX, centerY, radius, startAngle, endAngle, antiClockwise
                context.arc(xOffset + CHECKER_WIDTH / 2, yOffset + CHECKER_HEIGHT / 2, 45, 0, Math.PI * 2, false);
                context.closePath();
                context.lineWidth = 5;
                context.strokeStyle = 'yellow';
                context.stroke();
                context.fillStyle = 'orange';
                context.fill();
                context.restore();
            }
            else if(j === 6) {
                context.save();
                // create the checkers
                context.beginPath();
                // centerX, centerY, radius, startAngle, endAngle, antiClockwise
                context.arc(xOffset + CHECKER_WIDTH / 2, yOffset + CHECKER_HEIGHT / 2, 45, 0, Math.PI * 2, false);
                context.closePath();
                context.lineWidth = 5;
                context.strokeStyle = 'red';
                context.stroke();
                context.fillStyle = 'pink';
                context.fill();
                context.restore();
            }
        }
        else if(j % 2 !== 0 && i % 2 === 0){
            context.save();
            context.fillStyle = 'black';
            context.fillRect(xOffset, yOffset, CHECKER_WIDTH, CHECKER_HEIGHT);
            context.restore();

            if(j === 1) {
                context.save();
                // create the checkers
                context.beginPath();
                // centerX, centerY, radius, startAngle, endAngle, antiClockwise
                context.arc(xOffset + CHECKER_WIDTH / 2, yOffset + CHECKER_HEIGHT / 2, 45, 0, Math.PI * 2, false);
                context.closePath();
                context.lineWidth = 5;
                context.strokeStyle = 'yellow';
                context.stroke();
                context.fillStyle = 'orange';
                context.fill();
                context.restore();
            }
            else if(j === 5 || j === 7) {
                context.save();
                // create the checkers
                context.beginPath();
                // centerX, centerY, radius, startAngle, endAngle, antiClockwise
                context.arc(xOffset + CHECKER_WIDTH / 2, yOffset + CHECKER_HEIGHT / 2, 45, 0, Math.PI * 2, false);
                context.closePath();
                context.lineWidth = 5;
                context.strokeStyle = 'red';
                context.stroke();
                context.fillStyle = 'pink';
                context.fill();
                context.restore();
            }

        }
    }
} // create the checkerboard

function onDocumentMouseDown( event ) {

    event.preventDefault();

    // document.addEventListener( 'mousemove', onDocumentMouseMove, false );
    // document.addEventListener( 'mouseup', onDocumentMouseUp, false );
    // document.addEventListener( 'mouseout', onDocumentMouseOut, false );

    // mouseXOnMouseDown = event.clientX - windowHalfX;
    // targetRotationOnMouseDown = targetRotation;
    console.log(`mouse.x: ${event.clientX}, mouse.y: ${event.clientY}`);
}

// function onDocumentMouseMove( event ) {

//     mouseX = event.clientX - windowHalfX;

//     targetRotation = targetRotationOnMouseDown + ( mouseX - mouseXOnMouseDown ) * 0.02;

// }

// function onDocumentMouseUp( event ) {

//     document.removeEventListener( 'mousemove', onDocumentMouseMove, false );
//     document.removeEventListener( 'mouseup', onDocumentMouseUp, false );
//     document.removeEventListener( 'mouseout', onDocumentMouseOut, false );

// }

// function onDocumentMouseOut( event ) {

//     document.removeEventListener( 'mousemove', onDocumentMouseMove, false );
//     document.removeEventListener( 'mouseup', onDocumentMouseUp, false );
//     document.removeEventListener( 'mouseout', onDocumentMouseOut, false );

// }

// function onDocumentTouchStart( event ) {

//     if ( event.touches.length == 1 ) {

//         event.preventDefault();

//         mouseXOnMouseDown = event.touches[ 0 ].pageX - windowHalfX;
//         targetRotationOnMouseDown = targetRotation;

//     }

// }

// function onDocumentTouchMove( event ) {

//     if ( event.touches.length == 1 ) {

//         event.preventDefault();

//         mouseX = event.touches[ 0 ].pageX - windowHalfX;
//         targetRotation = targetRotationOnMouseDown + ( mouseX - mouseXOnMouseDown ) * 0.05;

//     }

// }