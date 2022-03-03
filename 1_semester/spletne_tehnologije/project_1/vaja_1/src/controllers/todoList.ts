import { Request, Response, NextFunction } from 'express';
import {client} from "../database/database";
import {TodoList} from "../models/todoList";

const getTodoLists = async (req: Request, res: Response, next: NextFunction) => {
    try {
        const result = await client.query({rowMode: 'map', text: 'SELECT * FROM todo_lists order by id asc'});

        return res.status(200).json({
            message: result.rows
        });

    }
    catch (e) {
        return res.status(200).json({
            message: e,
        });
    }
};

const updateTodoList = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.name || !requestParams.id) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'update todo_lists set name=$1, updated_at=now() where id = $2 and 1=1', values: [requestParams.name, Number(requestParams.id)]});

        return res.status(200).json({
            success: result.rowCount == 1,
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

const deleteTodoList = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.todoListId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'delete from todo_lists where id = $1', values: [requestParams.todoListId]});

        return res.status(200).json({
            message: result.rowCount,
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

const addTodoList = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.name) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        console.log("pre res");
        const result = await client.query({rowMode: 'map', text: 'insert into todo_lists (name, created_at, updated_at) values ($1, now(), null)', values: [requestParams.name]});
        //console.log(result);
        return res.status(200).json({
            success: result.rowCount == 1,
        });

    }
    catch (e) {
        console.log(e);
        return res.status(500).json({
            message: e,
        });
    }
};

export {getTodoLists, updateTodoList, deleteTodoList, addTodoList};