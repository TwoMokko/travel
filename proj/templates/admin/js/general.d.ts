declare namespace Admin {
    namespace General {
        type TypeField = {
            name: string;
            action: number;
            error: string;
            details: string;
        }[];
        type TypeTable = {
            name: string;
            action: number;
            error: string;
            fields?: TypeField;
        }[];
        export class Render {
            static ToMain(data: Object): void;
            static CheckDB(data: TypeTable): void;
            private static Form;
            private static Tables;
            private static Table;
            private static Fields;
            private static Field;
            private static Empty;
        }
        export {};
    }
}
