import express from 'express';
import {login, register} from "../controller/user";

const routes = express();

routes.post('/login', login);
routes.post('/register', register)

export {routes};