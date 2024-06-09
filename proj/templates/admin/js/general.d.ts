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
        type DisplayNames = 1;
        type DisplayDescriptions = 2;
        type DisplayMode = DisplayNames | DisplayDescriptions;
        type DataDB = {
            name: string;
            tables: DataTable[];
        };
        type DataTable = {
            name: string;
            description: string;
            params: DataTableParams;
            fields: DataField[];
            keys: DataKeys;
        };
        type DataField = {
            name: string;
            type: string;
            description: string;
        };
        type DataKeys = {
            primaries: DataKeyPrimary[];
            foreigners: DataKeyForeigner[];
        };
        type DataKeyPrimary = {
            type: 'primary';
            name: string;
            fields: string[];
        };
        type DataKeyForeigner = {
            type: 'foreign';
            name: string;
            fields: string[];
            references_table: string;
            references_fields: string[];
            relationship_from: number;
            relationship_to: number;
        };
        type DataTableParams = {
            encoding: string;
            engine: string;
        };
        export class Structure {
            static displayNames: DisplayNames;
            static displayDescriptions: DisplayDescriptions;
            db: DB;
            displayMode: DisplayMode;
            $topElement: HTMLElement;
            $structure: HTMLElement;
            $panel: HTMLDivElement;
            $display: HTMLAnchorElement;
            constructor(data: DataDB);
            private RenderPanel;
            private SwitchDisplayMode;
            HoverElement($elem: HTMLElement): void;
        }
        class DB {
            private readonly tables;
            private activeKey?;
            constructor(data: DataDB, $structure: HTMLElement, structure: Structure);
            private SetPrimaryKey;
            private SetForeignKey;
            SetActiveKey(key: Key): void;
            UnsetActiveKey(): void;
            GetActiveKey(): Key;
        }
        class Table {
            fields: {
                [key: string]: Field;
            };
            private $table;
            private $drag;
            private $header;
            private $title;
            private $name;
            private $description;
            private $menu;
            private $rows;
            private $keys;
            constructor(data: DataTable, $structure: HTMLElement, structure: Structure);
            private Render;
            AddKey(type: string, name: string, key: Key): HTMLDivElement;
        }
        class Field {
            private $wrap;
            private $type;
            private $name;
            private $description;
            private $key;
            static ER_RELATIONSHIP: {
                1: string;
                2: string;
                3: string;
                4: string;
                5: string;
                6: string;
            };
            constructor(data: DataField, $rows: HTMLDivElement);
            private Render;
            SetPrimaryKey(): void;
            UnsetPrimaryKey(): void;
            SetForeignKey(relationship: number): void;
            UnsetForeignKey(relationship: number): void;
            SetReferencesKey(relationship: number): void;
            UnsetReferencesKey(relationship: number): void;
        }
        class Key {
            name: string;
            db: DB;
            table: Table;
            fields: Field[];
            display: boolean;
            $key: HTMLDivElement;
            constructor(name: string, table: Table, fields: Field[], db: any);
            Display(): void;
            protected Show(): void;
            protected Hide(): void;
        }
        export {};
    }
}
