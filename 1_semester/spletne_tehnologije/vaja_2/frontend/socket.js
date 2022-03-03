var socket = io('http://localhost:3000/');
socket.on('news', function (data) {
    console.log(data);
    socket.emit('my other event', { my: 'data' });
});

socket.on('rooms', function (data) {
    console.log(data);
    displayRooms(data);
});

socket.on('game_start', function () {
    console.log('game_start');

    var popup = '<h3>Waiting for host to start</h3>';

    document.getElementById('popdiv').innerHTML = popup;

    $('#fullscreen-container').fadeTo(200,1);
    showBoard();
});

socket.on('game_result', function () {
    $('#fullscreen-container').fadeOut(200);
    showBoard();
});

socket.on('time_remaining', function (data) {
    console.log('time_remaining');
});

socket.on('message', function(data) {
    console.log(data);
    addMessage(data);
});

socket.on('game_ended', function(data) {
    //console.log(data);
    gameEnd(data);
});

socket.on('draw', function(data) {
    drawToBoard(data);
});

function returnSocket() {
    return socket;
}