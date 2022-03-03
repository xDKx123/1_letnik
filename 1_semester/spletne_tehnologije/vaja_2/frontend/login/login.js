function login() {
    var value = document.getElementById('username').value;

    if (value == null || value == '') {
        alert('cmon');
        return;
    }
    document.getElementById("login").style.display="none";

    document.getElementById("roomSection").style.display='block';
    returnSocket().emit('login', value);

}

function createRoom() {
    var roomName = document.getElementById('roomName');

    if (roomName.value == null || roomName.value == '') {
        alert('cmon');
        return;
    }

    returnSocket().emit('create_room', roomName.value);

    roomName.value = "";
}