import { Request, Response, NextFunction } from 'express';
import {client} from "../database/database";
import { v4 as uuidv4 } from 'uuid';
import sha256 from "sha256";


const login = async (req: Request, res: Response, next: NextFunction) => {
    //console.log(req.body);
    const requestParams = req.body;

    console.log(requestParams);

    if (!requestParams.email || !requestParams.password) {
        return res.status(200).json({
            success: false,
            message: 'Not enough params',
        });
    }

    try {
        const result = await client.query({rowMode: 'map', text: "SELECT * FROM users WHERE users.email = $1::text AND users.password = encode(sha256(concat($2::text, users.salt::text)::bytea), 'hex')", values: [String(requestParams.email), String(requestParams.password)]});

        res.send(result);

    }
    catch (e) {
        return res.status(500).json({
            success: false,
            message: e,
        });
    }
};

const register = async (req: Request, res: Response, next: NextFunction) => {
    console.log(req.body);
    const requestParams = req.body;

    if (!requestParams.email || !requestParams.password) {
        return res.status(200).json({
            message: 'Not enough params',
        });
    }

    let salt = uuidv4();

    try {
        const result = await client.query({rowMode: 'map', text: 'insert into users (email, password, salt, created_at) values ($1, $2, $3, now())', values: [requestParams.email, sha256(requestParams.password + salt), salt]});

        return res.status(200).json({
            success: result.rowCount = 1,
        });

    }
    catch (e) {
        return res.status(500).json({
            message: e,
        });
    }
};

export {login, register};