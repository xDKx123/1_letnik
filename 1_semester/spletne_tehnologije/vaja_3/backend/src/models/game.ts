import {Room} from "./room";
import {Socket} from "socket.io";
import {Figure} from "./figure";
import {gameboard} from "./gameboard";
import { UserColor } from "./user";
import { Gameboardfield } from "./gameboardfield";

class Game {
    id: string;
    room: Room;
    startDate: Date;
    currentPlayer: Socket;

    constructor(id: string, room: Room) {
        this.id = id;
        this.room = room;
        this.startDate = new Date();
        this.currentPlayer= room.owner;
    }

    startGame() {
        this.room.users.forEach((value, index) => {
            if (index == 0) {
                value.color = UserColor.red;
            }
            else if (index == 1) {
                value.color = UserColor.green;
            }
            else if (index == 2) {
                value.color = UserColor.yellow;
            }
            else if (index == 3) {
                value.color = UserColor.blue;
            }
        });

        //this.room.owner.emit('start_game', {'starts': true});
        this.room.users.forEach(value => {
            value.figures.forEach((value1, index1) => {
               value1.position = value.color.toString() + '_start_position_' + index1.toString();
            });

           value.socket.emit('start_game', {'starts': value.socket == this.currentPlayer, 'figures': value.figures.map(value => value.toJson())});
        });
        //this.room.owner.emit('start_game', {'starts: '})
    }

    move(player: Socket, positions: number, figureId: string) {
        if (this.currentPlayer == player) {
            this.room.users.forEach(value => {
                if (player = value.socket) {
                    value.figures.forEach(value1 => {
                        if (value1.id == figureId) {
                            for (let x = 0; x < positions - 1 || value1.position == 'finish'; x++) {
                                var position = gameboard.find(value2 => value2.id == value1.position);

                                //before we make the move we check if next position is possible;
                                var isAvaliable: boolean = this.room.users.some(value3 => {
                                    return value3.figures.some(value4 => value4.position == position!.next);
                                });

                                //we check if the available position has enemy and is last position of figure, we send the enemy to starting position;
                                if (!isAvaliable && x == positions -2) {
                                    this.room.users.forEach(value2 => {
                                        value2.figures.forEach((value3, index) => {
                                            if (value3.position == position!.next) {
                                                value3.position = value2.color.toString() + '_start_position_' + index.toString();
                                            }
                                        })
                                    })
                                }

                                //move the figure;
                                value1.position = position!.next;

                                //check if position is available for end game;
                                if (position!.next == 'finish') {
                                    //If all figures are in 'finish' field, the player has ended the game;
                                    value.figures.every(value2 => value2.position == 'finish');

                                    this.gameOver(value.socket);
                                }
                            }
                        }
                    });
                }
            });
        }


        if (positions != 6) {
            this.nextMove(player);
        }

        this.room.users.forEach(value => {
            value.socket.emit('figure_positions', 
                {
                    'positions': value.figures.map(value2 => value2.toJson()),
                    'hasMove': value.socket == this.currentPlayer,
            });
        });
    }

    

    nextMove(player: Socket) {
        this.room.users.forEach((value, index) => {
            if (value.socket == player) {
                if (index == 3) {
                    this.currentPlayer = this.room.owner;
                }
                else {
                    this.currentPlayer = this.room.users[index + 1].socket;
                }
            }
        });
    }
    
    availableMoves(player: Socket, positions:number) {
        var figuersIds: string[] = [];
        this.room.users.forEach(value => {
           value.figures.forEach((value2, index2) => {
               let tmpPosition: String = value2.position;
               
               if (tmpPosition == value.color.toString() + '_start_position_' + index2.toString() && positions == 6) {
                   let isAvailable = this.room.users.some(value3 => {
                       return value3.figures.some(value4 => value4.position = value.color.toString() + '_start');
                   });
                   
                   if (!isAvailable) {
                       this.room.users.forEach(value3 => {
                           if (value3.socket == player) {
                               let isNotOur: boolean = value3.figures.some(value4 => value4.position == tmpPosition);

                               //the last position to move is enemy, so the position is valid;
                               if (!isNotOur) {
                                   isAvaliable = true;
                               }
                           }

                       });
                   }
                   
                   if (isAvailable) {
                       figuersIds.push(value2.id);
                   }
               }
               else {


                   var isAvaliable = true;
                   for (let x = 0; x < positions - 1 || value2.position == 'finish'; x++) {
                       var position: Gameboardfield = gameboard.find(value2 => value2.id == tmpPosition)!;
                       tmpPosition = position.next;

                       var isAvaliable: boolean = this.room.users.some(value3 => {
                           return value3.figures.some(value4 => value4.position == tmpPosition);
                       });


                       if (!isAvaliable) {
                           //if next position == positions to move than the position is avaliable if figure is enemy
                           if (x == positions - 2) {
                               this.room.users.forEach(value3 => {
                                   if (value3.socket == player) {
                                       let isNotOur: boolean = value3.figures.some(value4 => value4.position == tmpPosition);

                                       //the last position to move is enemy, so the position is valid;
                                       if (!isNotOur) {
                                           isAvaliable = true;
                                       }
                                   }

                               });
                           }
                           break;
                       }
                   }

                   if (isAvaliable) {
                       figuersIds.push(value2.id);
                   }
               }
           });               
        });
        
        //player has no moves so we switch to next player
        if (figuersIds.length == 0) {
            this.nextMove(player);
        }
        //player has one move, so we make it
        else if (figuersIds.length == 1) {
            this.move(player, positions, figuersIds[0]);
        }
        //player has multiple moves available, so we make it for him,
        else {
            player.emit('avalibale_moves', figuersIds);
        }
    }

    gameOver(winner: Socket) {
        this.room.users.forEach(value => {
           value.socket.emit('game_over', {'winner': winner == value.socket});
        });
    }
}

export {Game};