//import http from "http";
import express, { Express } from 'express';
import {User} from "./models/user";
import {v4} from "uuid";
import {Room} from "./models/room";
import {Game} from "./models/game";
import {Socket} from "socket.io";


const app: Express = express();
app.set("port", process.env.PORT || 3000);

let http = require("http").Server(app);

let io = require("socket.io")(http, {
    cors: {
        origin: "*",
        methods: ["GET", "POST"]
    }
});

app.get("/", (req: any, res: any) => {
    res.send('test');
});

var users: User[] = [];
var rooms: Room[] = [];
var games: Game[] = [];

io.on("connection", async function (socket: Socket) {
    socket.on('login', (arg: string) => {
        users.push(new User(socket, arg));
        //console.log(users);
        socket.emit('rooms', rooms.map(value => value.toJson(socket) ));
    });

    socket.on('rooms', () => {
        socket.emit('rooms', rooms.map(value => value.toJson(socket) ));
    });

    socket.on('join_room', (arg: string) => {
        console.log(arg);
        let user = users.find(value => value.socket == socket);
        rooms.forEach((value, index) => {if (value.id == arg) {
            if (user instanceof User) {
                value.addUser(user);
            }}})

        users.forEach(user => {user.socket.emit('rooms', rooms.map(room => room.toJson(user.socket) ))});
    });

    socket.on('create_room', (arg: string) => {
        var room : Room = new Room(v4(), arg, socket);
        room.users.push(users.find(value => value.socket == socket)!);
        
        rooms.push(room);

        users.forEach(user => {user.socket.emit('rooms', rooms.map(room => room.toJson(user.socket) ))});
    });

    socket.on('game_start', () => {
        rooms.forEach(value => {
            if (value.owner == socket) {
                value.users.forEach(value1 => {value1.socket.emit('game_start')});

                games.push(new Game(v4(), value));
            }
        });
    });
    
    socket.on('move', (arg: any) => {
        games.forEach(value => {
            value.room.users.forEach(value2 => {
                if (value2.socket == socket) {
                    value.move(socket, arg['positions'], arg['figureId']);
                    return;
                } 
            });
        });
    })
    
    socket.on('availableMoves', (arg: any) => {
       games.forEach(value => {
          value.room.users.forEach(value2 => {
              if (value2.socket == socket) {
                  value.availableMoves(socket, arg['positions']);
              }
          }) ;
       });
    });

    socket.on('disconnect', () => {
        rooms.forEach((value, index) => {value.users.forEach((value1, index1) => {
            if (value1.socket == socket){
                value.users.forEach(value2 => {
                    value2.socket.emit('message', {
                        'name': value1.name,
                        'message': 'left the game'
                    })
                })
                value.users.splice(index1);
            }

        })});


        rooms.forEach((value, index) => {if (value.owner == socket) {rooms.splice(index);}});

        users.forEach((value, index) => { if (value.socket == socket) {users.splice(index);} });
    });
})


const server = http.listen(3000, function() {
    console.log("listening on *:3000");
});