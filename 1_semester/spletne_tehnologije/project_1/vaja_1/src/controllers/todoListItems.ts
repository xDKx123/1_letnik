import { Request, Response, NextFunction } from 'express';
import {client} from "../database/database";

const getTodoListItems = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.todoListId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'SELECT tli.id, tli.name, tli.end_date, tli.reminder_days, tli.created_at, tli.updated_at FROM todo_lists_items  tli inner join todo_lists tl on tli.fk_todo_list = tl.id WHERE 1=1 and tl.id = $1 order by id asc', values: [requestParams.todoListId]});

        let mapIds = result.rows.map((x: { id: any; }) => x.id);

        console.log(mapIds);

        //const tags = await client.query({rowMode: 'map', text: 'SELECT t.id, t.name, t.created_at, t.updated_at FROM tags t left join todo_lists_items tli on tli.id = t.fk_todo_lists_item WHERE 1=1 AND tli.id = ANY($1::int[])', values: [mapIds]})

        return res.status(200).json({
            message: result.rows,
            //tags: tags.rows
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

const updateTodoListItem = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.id || !requestParams.name || !requestParams.end_date) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'update todo_lists_items set name=$1, updated_at=now(), end_date=$2, reminder_days=$3 where id=$4', values: [requestParams.name, requestParams.end_date, Number(requestParams.reminder_days), Number(requestParams.id)]});

        return res.status(200).json({
            message: result.rowCount == 1,
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

const deleteTodoListItem = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.todoListItemId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({
            rowMode: 'array', text: 'DELETE FROM todo_lists_items WHERE id = $1', values: [requestParams.todoListItemId]});

        return res.status(200).json({
            message: result,
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

const addTodoListItem = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.name || !requestParams.end_date || !requestParams.todoListId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        console.log(requestParams.reminder_date);
        const result = await client.query({
            rowMode: 'array', text: 'insert into todo_lists_items (name, created_at, updated_at, fk_todo_list, end_date, reminder_days) values ($1, now(), null, $2, $3, $4)', values: [requestParams.name, Number(requestParams.todoListId), requestParams.end_date, Number(requestParams.reminder_date)]});

        return res.status(200).json({
            success: result.rowCount == 1,
        });

    }
    catch (e) {
        console.log(e)
        return res.status(500).json({
            message: e,
        });
    }
};

export {getTodoListItems, updateTodoListItem, deleteTodoListItem, addTodoListItem};