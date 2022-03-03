let rooms = [];

function getRooms() {
    return rooms;
}

function room(room) {
    let roomHtml='<div id="' + room.id + '" class="room">';

    roomHtml+= '<div><h3>' + room.name + '</h3></div>';
    roomHtml+= '<div><p>' + room.joined + '</p></div>'
    roomHtml+= '<div>' + '<button class="btn btn-primary" onclick="joinRoom(\'' + room.id + '\')">Join</button>' + '</div>';
    
    roomHtml+= '</div>';

    return roomHtml;
}

function joinRoom(id) {
    console.log(id);
    returnSocket().emit('join_room', id);
}

function displayRooms(roomss) {
    rooms = roomss;
    var personalRoomObject = document.getElementById("personalRoom");
    personalRoomObject.innerHTML = "";

    var roomsObject = document.getElementById("rooms");
    roomsObject.innerHTML = "";
    

    for (var x = 0; x < rooms.length; x++) {
        if (rooms[x].owner == true) {
            personalRoomObject.innerHTML += personalRoom(rooms[x]);
        }
        else {
            roomsObject.innerHTML += room(rooms[x]);
        }
        
    }
}

function personalRoom(room) {
    let roomHtml = '<div>'

    roomHtml += '<h2>' + room.name + '</h2>';
    roomHtml += '<p>' + room.joined + '</p>';
    roomHtml += '<button class="btn btn-danger" onclick="removeRoom(\'' + room.id + '\')">Remove room</button>';
    roomHtml += '<button class="btn btn-primary" onclick="startTheGame(\'' + room.id + '\')">Start game</button>';
    roomHtml += '</div>';

    return roomHtml;
}


function removeRoom(id) {
    returnSocket().emit('remove_room', id);
}

function startTheGame(id) {
    // var body = document.getElementsByTagName('body')[0];

    //var popup = '';

     var popup = '<h3>Enter result</h3>';
     popup += '<input id="gameResult" type="text">';
     popup += '<button class="btn btn-primary" onclick="gameResult();return false;">Submit</button>';

    // popup += '</div></div>';

    // body.innerHTML += popup;

    document.getElementById('popdiv').innerHTML = popup;

    $('#fullscreen-container').fadeTo(200,1);

    
    showBoard();

    returnSocket().emit('game_start', id);
}

function gameResult() {
    var result = document.getElementById('gameResult').value;

    if (result != null && result != '') {
        $('#fullscreen-container').fadeOut(200);
        returnSocket().emit('game_result', result);
    }


}