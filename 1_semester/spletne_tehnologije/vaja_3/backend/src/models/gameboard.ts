import {Gameboardfield} from "./gameboardfield";

//Defined game positions next move;
let gameboard: Gameboardfield[] = [
    //RED BOARD PART
    new Gameboardfield('red_start', 'red_field_0'),
    new Gameboardfield('red_field_0', 'red_field_1'),
    new Gameboardfield('red_field_1', 'red_field_2'),
    new Gameboardfield('red_field_2', 'red_field_3'),
    new Gameboardfield('red_field_3', 'red_field_4'),
    new Gameboardfield('red_field_4', 'red_field_5'),
    new Gameboardfield('red_field_5', 'red_field_6'),
    new Gameboardfield('red_field_6', 'red_field_7'),
    new Gameboardfield('red_field_7', 'red_field_8'),
    new Gameboardfield('red_field_9', 'green_house'),
    new Gameboardfield('green_house', 'red_field_10'),
    new Gameboardfield('red_field_10', 'green_start'),


    //GREEN BOARD PART
    new Gameboardfield('green_start', 'green_field_0'),
    new Gameboardfield('green_field_0', 'green_field_1'),
    new Gameboardfield('green_field_1', 'green_field_2'),
    new Gameboardfield('green_field_2', 'green_field_3'),
    new Gameboardfield('green_field_3', 'green_field_4'),
    new Gameboardfield('green_field_4', 'green_field_5'),
    new Gameboardfield('green_field_5', 'green_field_6'),
    new Gameboardfield('green_field_6', 'green_field_7'),
    new Gameboardfield('green_field_7', 'green_field_8'),
    new Gameboardfield('green_field_9', 'yellow_house'),
    new Gameboardfield('yellow_house', 'green_field_10'),
    new Gameboardfield('green_field_10', 'yellow_start'),


    //YELLOW BOARD PART
    new Gameboardfield('yellow_start', 'yellow_field_0'),
    new Gameboardfield('yellow_field_0', 'yellow_field_1'),
    new Gameboardfield('yellow_field_1', 'yellow_field_2'),
    new Gameboardfield('yellow_field_2', 'yellow_field_3'),
    new Gameboardfield('yellow_field_3', 'yellow_field_4'),
    new Gameboardfield('yellow_field_4', 'yellow_field_5'),
    new Gameboardfield('yellow_field_5', 'yellow_field_6'),
    new Gameboardfield('yellow_field_6', 'yellow_field_7'),
    new Gameboardfield('yellow_field_7', 'yellow_field_8'),
    new Gameboardfield('yellow_field_9', 'blue_house'),
    new Gameboardfield('blue_house', 'yellow_field_10'),
    new Gameboardfield('yellow_field_10', 'blue_start'),

    new Gameboardfield('blue_start', 'blue_field_0'),
    new Gameboardfield('blue_field_0', 'blue_field_1'),
    new Gameboardfield('blue_field_1', 'blue_field_2'),
    new Gameboardfield('blue_field_2', 'blue_field_3'),
    new Gameboardfield('blue_field_3', 'blue_field_4'),
    new Gameboardfield('blue_field_4', 'blue_field_5'),
    new Gameboardfield('blue_field_5', 'blue_field_6'),
    new Gameboardfield('blue_field_6', 'blue_field_7'),
    new Gameboardfield('blue_field_7', 'blue_field_8'),
    new Gameboardfield('blue_field_9', 'red_house'),
    new Gameboardfield('red_house', 'blue_field_10'),
    new Gameboardfield('blue_field_10', 'red_start'),

    //START POSITION RED
    new Gameboardfield('red_start_position_0', 'red_start'),
    new Gameboardfield('red_start_position_1', 'red_start'),
    new Gameboardfield('red_start_position_2', 'red_start'),
    new Gameboardfield('red_start_position_3', 'red_start'),

    //START POSITION GREEN
    new Gameboardfield('green_start_position_0', 'green_start'),
    new Gameboardfield('green_start_position_1', 'green_start'),
    new Gameboardfield('green_start_position_2', 'green_start'),
    new Gameboardfield('green_start_position_3', 'green_start'),

    //START POSITION YELLOW
    new Gameboardfield('yellow_start_position_0', 'yellow_start'),
    new Gameboardfield('yellow_start_position_1', 'yellow_start'),
    new Gameboardfield('yellow_start_position_2', 'yellow_start'),
    new Gameboardfield('yellow_start_position_3', 'yellow_start'),

    //START POSITION BLUE
    new Gameboardfield('blue_start_position_0', 'blue_start'),
    new Gameboardfield('blue_start_position_1', 'blue_start'),
    new Gameboardfield('blue_start_position_2', 'blue_start'),
    new Gameboardfield('blue_start_position_3', 'blue_start'),


    //RED HOUSE
    new Gameboardfield('red_house_0', 'red_house_1'),
    new Gameboardfield('red_house_1', 'red_house_2'),
    new Gameboardfield('red_house_2', 'red_house_3'),
    new Gameboardfield('red_house_3', 'finish'),

    //GREEN HOUSE
    new Gameboardfield('green_house_0', 'green_house_1'),
    new Gameboardfield('green_house_1', 'green_house_2'),
    new Gameboardfield('green_house_2', 'green_house_3'),
    new Gameboardfield('green_house_3', 'finish'),

    //YELLOW HOUSE
    new Gameboardfield('yellow_house_0', 'yellow_house_1'),
    new Gameboardfield('yellow_house_1', 'yellow_house_2'),
    new Gameboardfield('yellow_house_2', 'yellow_house_3'),
    new Gameboardfield('yellow_house_3', 'finish'),

    //BLUE HOUSE
    new Gameboardfield('blue_house_0', 'blue_house_1'),
    new Gameboardfield('blue_house_1', 'blue_house_2'),
    new Gameboardfield('blue_house_2', 'blue_house_3'),
    new Gameboardfield('blue_house_3', 'finish'),


    //FINISH
    new Gameboardfield('finish', ''),
];

export {gameboard};