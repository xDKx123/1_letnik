import { Request, Response, NextFunction } from 'express';
import {client} from "../database/database";

const getUser = async (req: Request, res: Response, next: NextFunction) => {
    console.log(req.body);
    const requestParams = req.body;

    if (!requestParams.email || !requestParams.password) {
        return res.status(200).json({
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'array', text: 'SELECT * FROM users WHERE email = $1 AND password = $2', values: [requestParams.email, requestParams.password]});

        if (result.rows.length > 0) {
            return res.status(200).json({
                message: result.rows[0],
            });
        }
        else {
            return res.status(200).json({
                message: 'User not found'
            });
        }

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

export {getUser};