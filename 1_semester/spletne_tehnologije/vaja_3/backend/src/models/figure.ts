class Figure {
    id: string;
    position: string;

    constructor(id: string, position: string) {
        this.id = id;
        this.position = position;
    }


    toJson(): any {
        return {
            'id': this.id,
            'position': this.position,
        }
    }
}

export {Figure};