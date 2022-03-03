const {Client} = require('pg')
const client = new Client({host: 'localhost', port: 5433, user:'postgres', password:'postgres'});

//client.connect().then(() => console.log('Connected to database')).catch((err: { stack: any; }) => console.error('Database connection error', err.stack);

client.connect();

export {client};