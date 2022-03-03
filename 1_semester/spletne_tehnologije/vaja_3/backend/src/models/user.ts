import {Figure} from "./figure";

class User{
    socket: any;
    name: string;
    figures: Figure[];
    color: UserColor;

    constructor(socket: any, name: string) {
        this.socket = socket;
        this.name = name;
        this.figures = [];
        this.color = UserColor.unknown;

        for (let x = 0; x < 4; x++) {
            this.figures.push(new Figure('', ''));
        }
    }
}

enum UserColor {
    green,
    yellow,
    blue,
    red,
    unknown,
}

export {User, UserColor}