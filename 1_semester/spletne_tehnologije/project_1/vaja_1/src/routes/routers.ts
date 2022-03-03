import express from 'express';
import {getTodoLists, updateTodoList, deleteTodoList, addTodoList} from "../controllers/todoList";
import {getUser} from "../controllers/user";
import {getTodoListItems, updateTodoListItem, deleteTodoListItem, addTodoListItem} from "../controllers/todoListItems";
import {getTags, deleteTag, addTag, updateTag} from "../controllers/tag";

const routes = express.Router();

//USER ROUTES
routes.post('/getUser', getUser);

//TODOLIST ROUTES
routes.post('/getTodoLists', getTodoLists);
routes.post('/updateTodoList', updateTodoList);
routes.post('/deleteTodoList', deleteTodoList);
routes.post('/addTodoList', addTodoList);

//TODOLISTITEM ROUTES
routes.post('/getTodoListItems', getTodoListItems);
routes.post('/updateTodoListItem', updateTodoListItem);
routes.post('/deleteTodoListItem', deleteTodoListItem);
routes.post('/addTodoListItem', addTodoListItem);

//TAGS
routes.post('/getTags', getTags);
routes.post('/updateTag', updateTag);
routes.post('/deleteTag', deleteTag);
routes.post('/addTag', addTag);

export {routes};