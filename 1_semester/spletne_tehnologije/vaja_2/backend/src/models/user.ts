class User{
    socket: any;
    name: string;

    constructor(socket: any, name: string) {
        this.socket = socket;
        this.name = name;
    }
}

export {User}