import { Request, Response, NextFunction } from 'express';
import {client} from "../database/database";

const getTags = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.listItemId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'SELECT tags.id, tags.name, tags.created_at, tags.updated_at FROM tags inner join todo_lists_items tli on tags.fk_todo_lists_item = tli.id WHERE tli.id = $1 ORDER BY id asc', values: [Number(requestParams.listItemId)]});

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

const updateTag = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.name || !requestParams.id) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'update tags set name=$1, updated_at=now() where id = $2 and 1=1', values: [requestParams.name, Number(requestParams.id)]});

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

const deleteTag = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.id) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: 'delete from tags where id = $1', values: [requestParams.id]});

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

const addTag = async (req: Request, res: Response, next: NextFunction) => {
    const requestParams = req.body;

    if (!requestParams.name || !requestParams.todoListItemId) {
        return res.status(400).json({
            message: 'Not enough params',
        });
    }

    try {
        console.log("pre res");
        const result = await client.query({rowMode: 'map', text: 'insert into tags (name, created_at, updated_at, fk_todo_lists_item) values ($1, now(), null, $2)', values: [requestParams.name, requestParams.todoListItemId]});
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

export {addTag, deleteTag, getTags,updateTag}