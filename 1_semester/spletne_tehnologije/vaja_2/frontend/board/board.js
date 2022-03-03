let strokeStyle = 'black';
let lineJoin = 'round';
let lineWidth = 5;

var clickX = new Array();
var clickY = new Array();
var clickDrag = new Array();
var paint;

const server="http://127.0.0.1:6060";

const addMessageRoute="/addMessage";
const getDrawingDataRoute="/getDrawingData";
const setDrawingDataRoute='/setDrawingData';

$('document').ready(function() {

    document.getElementById('upperSide').style.height = screen.height * 0.15;

    var canvas = document.getElementById('drawingBoard');

    if (canvas.getContext) {
        var context = canvas.getContext('2d');

        $('#drawingBoard').mousedown(function(e){
            var mouseX = (e.clientX - this.offsetLeft)*this.width/this.clientWidth;
            var mouseY = (e.clientY - this.offsetTop)*this.height/this.clientHeight;

            paint = true;
            addClick(mouseX, mouseY, false);
            redraw();
        });


        $('#drawingBoard').mousemove(function(e){
            if(paint){
                addClick((e.clientX - this.offsetLeft)*this.width/this.clientWidth ,(e.clientY - this.offsetTop)*this.height/this.clientHeight, true);
                redraw();
            }
        });

        $('#drawingBoard').mouseup(function(e){
            paint = false;
        });

        $('#drawingBoard').mouseleave(function(e){
            paint = false;

            //TODO: call REST api to send to everyone else;

            clickX = new Array();
            clickY = new Array();
            clickDrag = new Array();
        });

        function addClick(x, y, dragging)
        {
            console.log('draw');
            returnSocket().emit('draw', {
                'x': x,
                'y': y,
                'style': strokeStyle,
            });

            clickX.push(x);
            clickY.push(y);
            clickDrag.push(dragging);
        }

        function redraw(){
            console.log('redraw');
            //canvas.width = canvas.width; // Clears the canvas
          
            context.strokeStyle = strokeStyle;
            context.lineJoin = lineJoin;
            context.lineWidth = lineWidth;
          
            for(var i=0; i < clickX.length; i++)
            {		
              context.beginPath();
              if(clickDrag[i] && i){
                context.moveTo(clickX[i-1], clickY[i-1]);
               }else{
                 context.moveTo(clickX[i]-1, clickY[i]);
               }
               context.lineTo(clickX[i], clickY[i]);
               context.closePath();
               context.stroke();
            }
          }

          let colorCells = document.querySelectorAll('.colorCell');

          for (let i = 0; i < colorCells.length; i++) {
              colorCells[i].onclick = function() {
                  console.log(colorCells[i].style.backgroundColor);
                  strokeStyle = colorCells[i].style.backgroundColor;
              }
              colorCells[i].style.cursor = 'pointer';
          }

    } else {
        // canvas-unsupported code here
        alert('cannot use drawing');
    }
});

function showBoard() {
    document.getElementById('roomSection').style.display = 'none';
    document.getElementById('gameSection').style.display = 'block';
}

function sendText() {
    var message = document.getElementById('messageInput');

    if (message.value != null && message.value != '') {
        returnSocket().emit('message', message.value);
    }


    message.value = '';
};

function addMessage(message) {
    var textHtml = '<div>';
    textHtml += '<strong>' + message.name +': </strong>';
    textHtml += '<p>' + message.message + '</p>'
    textHtml += '</div>';

    var messagesList = document.getElementById('messagesList');

    messagesList.innerHTML += textHtml;

    messagesList.scrollTop = messagesList.scrollHeight;
}

function drawToBoard(data) {
    console.log(data);
    var canvas = document.getElementById('drawingBoard');

    var context = canvas.getContext('2d');

        
    if (data.style != strokeStyle) {
        context.strokeStyle = data.style;
        clickX = new Array();
        clickY = new Array();
    }

    clickX.push(data.x);
    clickY.push(data.y);


    
    context.lineJoin = lineJoin;
    context.lineWidth = lineWidth;
  
    for(var i=0; i < clickX.length; i++)
    {		
      context.beginPath();
      if(clickDrag[i] && i){
        context.moveTo(clickX[i-1], clickY[i-1]);
       }else{
         context.moveTo(clickX[i]-1, clickY[i]);
       }
       context.lineTo(clickX[i], clickY[i]);
       context.closePath();
       context.stroke();
    }
}

function gameEnd(data) {
    var popup = '<h3>Winner: ' + data.winner +'</h3>';
    popup += '<p>time to complete: ' + data.elapsed_time + ' secconds  </p>';

    popup += '<button class="btn btn-error" onclick="closeGame();return danger;">Return to rooms</button>'

    document.getElementById('popdiv').innerHTML = popup;

    $('#fullscreen-container').fadeTo(200,1);
}

function closeGame() {
    document.getElementById('messagesList').innerHTML = '';
    
    var canvas = document.getElementById('drawingBoard');

    const context = canvas.getContext('2d');

context.clearRect(0, 0, canvas.width, canvas.height);

    $('#fullscreen-container').fadeOut(1);

    document.getElementById('gameSection').style.display = 'none';

    document.getElementById('roomSection').style.display = 'block';

    returnSocket().emit('rooms');
}