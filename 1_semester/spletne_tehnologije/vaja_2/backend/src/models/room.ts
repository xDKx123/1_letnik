import {User} from "./user";
import {Socket} from "socket.io";

class Room{
    id: string;
    name: string;
    users: User[];
    owner: Socket;

    constructor(id: string, name: string, owner: any) {
        this.id = id;
        this.name = name;
        this.owner = owner;
        this.users = [];
    }

    addUser(user: User) {
        this.users.push(user);
    }

    toJson(socket: any) {
        return {
            "id": this.id,
            "name": this.name,
            "joined": this.users.length.toString(),
            "owner": this.owner == socket
        }
    }
}

export {Room};