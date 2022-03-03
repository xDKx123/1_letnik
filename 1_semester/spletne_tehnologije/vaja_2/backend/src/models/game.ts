import {Room} from "./room";

class Game {
    room: Room;
    gameResult: string | undefined;
    startDate: Date | undefined;

    constructor(room: Room) {
        this.room = room;
    }

    startGame(gameResult: string): void {
        this.gameResult = gameResult;
        this.startDate = new Date();
    }

    checkResult(result: string): boolean {
        return this.gameResult == result;
    }
}

export {Game}