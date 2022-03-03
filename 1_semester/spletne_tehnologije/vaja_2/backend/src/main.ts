//import http from 'http';
import express, { Express } from 'express';
import {User} from "./models/user";
import {v4} from "uuid";
import morgan from 'morgan';
import {routes} from './routes/routers';
//import {client} from "./database/database";
import * as socketio from "socket.io";
import * as path from "path";
//import {login} from "./controller/user";
import {client} from "./database/database";
import {Room} from "./models/room";
import {x2} from "sha256";
import {Socket} from "socket.io";
import {Game} from "./models/game";

/** Logging */
//router.use(morgan('dev'));
/** Parse the request */
//router.use(express.urlencoded({ extended: false }));
/** Takes care of JSON data */
//router.use(express.json());

//router.use(routes);

const app: Express = express();
app.set("port", process.env.PORT || 3000);

let http = require("http").Server(app);
// set up socket.io and bind it to our
// http server.
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

//rooms.push(new Room('uuid4', 'testName'));

function sleep(num: number) {
    let now = new Date();
    let stop = now.getTime() + num;
    while(true) {
        now = new Date();
        if(now.getTime() > stop) return;
    }
}

async function gameTime(room: Room, time: number) {
    room.users.forEach(value => {value.socket.emit('game_start')});

    while (time >= 0) {
        console.log(time);
        //console.log(room.users.length);
        //console.log(room.owner);
        try {
            room.owner.emit('time_remaining', time);
        }
        catch (e) {
            console.log(e);
        }

        room.users.forEach(value => {value.socket.emit('game_start')});
        time--;
        if (time == 0) {
            return;
        }
        sleep(1000);
    }
}

async function runGame(room: Room, result: string) {
    let isRunning: boolean = true;

    console.log('runGame');

    while (isRunning) {
        room.owner.on('drawing', (arg: string) => {
            room.users.forEach(value => {
                value.socket.emit('has_draw', arg);
            })
        });

        room.users.forEach(value => {value.socket.on('message', (arg: string) => {
            if (arg == result) {
                room.users.forEach(value1 => {value1.socket.emit('game_end')});

                room.owner.emit('game_end');
            }
        })});
    }
}

async function game(room: Room) {
}

// whenever a user connects on port 3000 via
// a websocket, log that a user has connected
io.on("connection", async function(socket: Socket) {
    console.log("a user connected");
    //users.push(socket);
    //console.log(io.sockets.sockets);

    //console.log(socket.id);

    socket.on('login', (arg: string) => {
        users.push(new User(socket, arg));
        //console.log(users);
        socket.emit('rooms', rooms.map(value => value.toJson(socket) ));
    });

    socket.on('rooms', () => {
        socket.emit('rooms', rooms.map(value => value.toJson(socket) ));
    });

    socket.on('test', (arg: any) => {
        //arr.push('test');
        //console.log(arr.length);
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
        rooms.push(new Room(v4(), arg, socket));

        users.forEach(user => {user.socket.emit('rooms', rooms.map(room => room.toJson(user.socket) ))});
    });

    /*socket.on('start_game', (arg: string) => {
        console.log('game start');
        let room = rooms.find(value => value.owner == socket);

        if (room != undefined) {
            game(room);
        }
    })*/

    socket.on('remove_room', (arg: string) => {
        rooms.forEach((value, index) => {if (value.owner == socket) {rooms.splice(index)}});

        users.forEach(user => {user.socket.emit('rooms', rooms.map(room => room.toJson(user.socket) ))});
    });


    //GAME
    socket.on('game_start', () => {
        rooms.forEach(value => {
            if (value.owner == socket) {
                value.users.forEach(value1 => {value1.socket.emit('game_start')});

                games.push(new Game(value));
            }
        });
    });

    socket.on('game_result', (arg: string) => {
        games.forEach(value => {
           if (value.room.owner == socket) {
               value.room.users.forEach(value1 => {
                  value1.socket.emit('game_result');
               });
               value.startGame(arg);
           }
        });
    });

    socket.on('draw', (arg: any) => {
        games.forEach(value => {
            if (value.room.owner == socket) {
                console.log('draw');
                value.room.users.forEach(value1 => {
                    value1.socket.emit('draw', arg);
                })
            }
        })
    });

    socket.on('message', (arg: string) => {
       games.forEach((value, index) => {
           if (value.room.owner == socket) {
               users.forEach(value1 => {
                   if (value1.socket == socket) {
                       value.room.owner.emit('message', {
                           'name': value1.name,
                           'message': arg});
                       value.room.users.forEach(value2 => {
                           value2.socket.emit('message', {
                               'name': value1.name,
                               'message': arg});
                       });
                   }
               });
               return;
           }
           value.room.users.forEach((value1, index1) => {
               if (value1.socket == socket) {
                   if (value.gameResult === arg) {
                       value.room.owner.emit('game_ended', {
                           'elapsed_time': (new Date().getTime() - value.startDate!.getTime()) / 1000,
                           'winner': value1.name
                       });
                       value.room.users.forEach(value2 => {
                           value2.socket.emit('game_ended', {
                               'elapsed_time': (new Date().getTime() - value.startDate!.getTime()) / 1000,
                               'winner': value1.name
                           });

                           games.splice(index);
                           rooms.splice(index1);
                       });
                   }
                   else {


                       value.room.owner.emit('message', {
                           'name': value1.name,
                           'message': arg
                       });
                       value.room.users.forEach(value2 => {
                           value2.socket.emit('message', {
                               'name': value1.name,
                               'message': arg
                           });
                       });

                   }
               }
           })
       })
    });


    socket.on('disconnect', () => {
        console.log('disconnect');
        //client.indexOf(socket);
        //users.splice(users.findIndex((value, index) => value.socket = socket), 1);
        rooms.forEach((value, index) => {value.users.forEach((value1, index1) => {
            if (value1.socket == socket){
                value.users.forEach(value2 => {
                    value2.socket.emit('message', {
                        'name': value1.name,
                        'message': 'left the game'
                    })
                })
                value.users.splice(index1)
            }

        })});

        rooms.forEach((value, index) => {if (value.owner == socket) {rooms.splice(index)}});

        users.forEach((value, index) => { if (value.socket == socket) {users.splice(index);} });
    });
});

const server = http.listen(3000, function() {
    console.log("listening on *:3000");
});